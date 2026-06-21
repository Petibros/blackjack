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

	player.last_bet = -1;
	player.money = 500;
	
	if  (gen_seed() == 1)
		return (1);
	else if (get_bindings(&bindings) == 1)
	{
		perror("problem while attempting to read 'bindings.txt'");
		return (1);
	}

	while (1)
	{
		reset_player(&player);
		reset_player(&dealer);
		
		show_rules();
		//asks for wanted bet amount or quit
		if (bet(&player) == -1)
			break ;
		
		//deck creation and shuffle
		if (new_deck(&deck) == 1)
		{
			free_cards(&deck, &player, &dealer);
			return (1);
		}
		shuffle_deck(&deck);		

		//deals 2 cards to the player and 1 to the dealer (NO HOLE CARD RULE)
		deal_card(&deck, &player.hands[0], 2);
		player.hands[0].in_play = true;
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
	}
	return (0);
}
