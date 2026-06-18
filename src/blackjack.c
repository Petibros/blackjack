#include "blackjack.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

int	main()
{
	t_card		*deck[DECK_CARDS * N_DECKS];
	t_player	dealer, player;
	t_bindings	bindings;
	char		buf[3];
	
	player.money = 500;
	
	if  (gen_seed() == 1)
		return (1);
	else if (get_bindings(&bindings) == 1)
	{
		perror("problem while attempting to read 'bindings.txt'");
		return (1);
	}

	do
	{
		reset_player(&player);
		reset_player(&dealer);
		
		//deck creation and shuffle
		if (new_deck(&deck) == 1)
		{
			free_cards(&deck, &player, &dealer);
			return (1);
		}
		shuffle_deck(&deck);
		
		show_rules();
		//asks for wanted bet amount
		bet(&player);

		//deals 2 cards to the player and 1 to the dealer (NO HOLE CARD RULE)
		deal_card(&deck, &player.hands[0], 2);					
		deal_card(&deck, &dealer.hands[0], 1);
		display_cards(&player, &dealer);

		//player draws until STAND or 21
		if (player_turn(&player, &deck, &dealer, &bindings) != 1)
			sleep(1);

		//second dealer card
		deal_card(&deck, &dealer.hands[0], 1);
		display_cards(&player, &dealer);
		sleep(1);
	
		//dealer draws until 17
		dealer_turn(&dealer, &deck, &player);

		//gives earnings for the turn
		give_result(&player, &dealer);

		//frees cards for this turn
		free_cards(&deck, &player, &dealer);

		printf("\nContinue ? : [Y/n]\n");
		read(0, buf, 2);
		buf[2] = 0;
	} while ((strncmp(buf, "y\n", 2) == 0 || strncmp(buf, "Y\n", 2) == 0 || strncmp(buf, "\n", 1) == 0) && player.money > 0);	
}
