#include "blackjack.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

int	main()
{
	t_card		*deck[DECK_CARDS * N_DECKS];
	char		seed[1];
	t_player	dealer, player;
	char		buf[3];

	player.money = 500;
	int fd = open("/dev/random", O_RDONLY);			//SEED GEN (for shuffling)
	read(fd, seed, 1);
	close(fd);
	srandom(seed[0]);

	do
	{
		new_deck(&deck);									//DECK CREATION
		shuffle_deck(&deck);								//SHUFFLE
	
		reset_player(&player);
		reset_player(&dealer);

		bet(&player);									//ASK FOR BET
		deal_card(&deck, &player.hands[0], 2);					//DEALS 2 CARDS TO PLAYER AND DEAELR
		deal_card(&deck, &dealer.hands[0], 1);
		display_cards(&player, &dealer);

		player_turn(&player, &deck, &dealer, 0);
		deal_card(&deck, &dealer.hands[0], 1);
		display_cards(&player, &dealer);
		dealer_turn(&dealer, &deck, &player);

		give_result(&player, &dealer);
/*		
		for (int i = 0 ; i < DECK_CARDS * N_DECKS; i++)
		{
			if (deck[i])
				printf("value : %d, type : %d  CARD %d\n", deck[i]->value, deck[i]->type, i + 1);
			if (i < 16)
			{
				if (player.hands[0].cards[i])
					printf("value : %d, type : %d  CARD %d\n", player.hands[0].cards[i]->value, player.hands[0].cards[i]->type, i + 1);
				if (dealer.hands[0].cards[i])
					printf("value : %d, type : %d  CARD %d\n", dealer.hands[0].cards[i]->value, dealer.hands[0].cards[i]->type, i + 1);
			}
		}*/

		for (int i = 0 ; i < DECK_CARDS * N_DECKS; i++ )
		{
			if (i < 16)
			{
				for (int curr_hand = 0; curr_hand < player.n_hands; curr_hand++)
				{
					if (player.hands[curr_hand].cards[i])
						free(player.hands[curr_hand].cards[i]);
				}
				if (dealer.hands[0].cards[i])
					free(dealer.hands[0].cards[i]);
			}
			if (deck[i])
				free(deck[i]);
		}

		printf("Continue ? : [Y/n]\n");
		read(0, buf, 2);
		buf[2] = 0;
	} while (strncmp(buf, "y\n", 2) == 0 || strncmp(buf, "Y\n", 2) == 0 || strncmp(buf, "\n", 1) == 0);	
}
