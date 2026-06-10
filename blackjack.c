#include "blackjack.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

int	main()
{
	t_card		*deck[52];
	char		seed[1];
	t_player	dealer, player;

	int fd = open("/dev/random", O_RDONLY);			//SEED GEN (for shuffling)
	read(fd, seed, 1);
	close(fd);
	srand(seed[0]);

	new_deck(&deck);									//DECK CREATION
	shuffle_deck(&deck);								//SHUFFLE

	reset_player(&player);
	reset_player(&dealer);

	bet(&player);									//ASK FOR BET
	deal_card(&deck, &player.hands[0], 2);					//DEALS 2 CARDS TO PLAYER AND DEAELR
	deal_card(&deck, &dealer.hands[0], 2);
	display_cards(&player, &dealer, 0);

	player_turn(&player, &deck, &dealer, 0);
	display_cards(&player, &dealer, 1);
	dealer_turn(&dealer, &deck, &player);

	printf("FINAL :\n");
	display_cards(&player, &dealer, 1);
/*		
	for (int i = 0 ; i < 52 ; i++)
	{
		if (deck[i])
			printf("value : %d, type : %d  CARD %d\n", deck[i]->value, deck[i]->type, i + 1);
		if (i < 16)
		{
			if (player.cards[i])
				printf("value : %d, type : %d  CARD %d\n", player.cards[i]->value, player.cards[i]->type, i + 1);
			if (dealer.cards[i])
				printf("value : %d, type : %d  CARD %d\n", dealer.cards[i]->value, dealer.cards[i]->type, i + 1);
		}
*/
	for (int i = 0 ; i < 52 ; i++ )
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
}
