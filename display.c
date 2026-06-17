#include "blackjack.h"

static char*	get_type(int type)
{
	switch (type)
	{
		case (1) :
			return ("♠️ ");
		case (2) :
			return ("♥️ ");
		case (3) :
			return ("♦️ ");
		case (4) :
			return ("♣️ ");
	}
	return ("0");
}

static char*	get_rank(int rank, int pos)
{
	switch (rank)
	{
		case (ACE) :
			if (pos == 1)
				return ("A ");
			return (" A");
		case (2) :
			if (pos == 1)
				return ("2 ");
			return (" 2");
		case (3) :
			if (pos == 1)
				return ("3 ");
			return (" 3");
		case (4) :
			if (pos == 1)
				return ("4 ");
			return (" 4");
		case (5) :
			if (pos == 1)
				return ("5 ");
			return (" 5");
		case (6) :
			if (pos == 1)
				return ("6 ");
			return (" 6");
		case (7) :									//6-7 AHHHHHHHHHHHHHHHHHHHH
			if (pos == 1)
				return ("7 ");
			return (" 7");
		case (8) :
			if (pos == 1)
				return ("8 ");
			return (" 8");
		case (9) :
			if (pos == 1)
				return ("9 ");
			return (" 9");
		case (10) :
			return ("10");
		case (JACK) :
			if (pos == 1)
				return ("J ");
			return (" J");
		case (QUEEN) :
			if (pos == 1)
				return ("Q ");
			return (" Q");
		case (KING) :
			if (pos == 1)
				return ("K ");
			return (" K");
		}

	return ("0");
}

static void	print_hand(t_hand *hand)
{
	for (int i = 0; i < hand->n_cards; i++)
		printf("\033[30;47m┌──────────────────┐\033[0m  ");
	printf("\n");
	for (int i = 0; i < hand->n_cards; i++)
		printf("\033[30;47m│ %s               │\033[0m  ", get_rank(hand->cards[i]->rank, 1));
	printf("\n");
	for (int i = 0; i < hand->n_cards; i++)
		printf("\033[30;47m│                  │\033[0m  ");
	printf("\n");
	for (int i = 0; i < hand->n_cards; i++)
		printf("\033[30;47m│                  │\033[0m  ");
	printf("\n");
	for (int i = 0; i < hand->n_cards; i++)
		printf("\033[30;47m│                  │\033[0m  ");
	printf("\n");
	for (int i = 0; i < hand->n_cards; i++)
		printf("\033[30;47m│                  │\033[0m  ");
	printf("\n");
	for (int i = 0; i < hand->n_cards; i++)
		printf("\033[30;47m│        %s        │\033[0m  ", get_type(hand->cards[i]->type));
	printf("\n");
	for (int i = 0; i < hand->n_cards; i++)
		printf("\033[30;47m│                  │\033[0m  ");
	printf("\n");
	for (int i = 0; i < hand->n_cards; i++)
		printf("\033[30;47m│                  │\033[0m  ");
	printf("\n");
	for (int i = 0; i < hand->n_cards; i++)
		printf("\033[30;47m│                  │\033[0m  ");
	printf("\n");
	for (int i = 0; i < hand->n_cards; i++)
		printf("\033[30;47m│                  │\033[0m  ");
	printf("\n");
	for (int i = 0; i < hand->n_cards; i++)
		printf("\033[30;47m│               %s │\033[0m  ", get_rank(hand->cards[i]->rank, 2));
	printf("\n");
	for (int i = 0; i < hand->n_cards; i++)
		printf("\033[30;47m└──────────────────┘\033[0m  ");
	printf("\n");
}

void	display_cards(t_player *player, t_player *dealer)
{
	printf("\n\n\n\n\n\n\n\n\n\n\nDEALER = %d", dealer->hands[0].total_value);
	
	//chooses the displayed total value depending on the aces
	if (dealer->hands[0].has_ace > 0 && dealer->hands[0].total_value + 10 <= 21)
		printf("/%d", dealer->hands[0].total_value + 10);
	printf("\n");

	print_hand(&dealer->hands[0]);
	

	printf("\nPLAYER : \n");
	for (int curr_hand = 0; curr_hand < player->n_hands; curr_hand++)
	{
		printf("HAND %d = %d", curr_hand + 1, player->hands[curr_hand].total_value);
		
		//chooses the displayed total value depending on the aces
		if (player->hands[curr_hand].has_ace > 0 && player->hands[curr_hand].total_value + 10 <= 21)
			printf("/%d", player->hands[curr_hand].total_value + 10);
		printf("\n");

		print_hand(&player->hands[curr_hand]);
		printf("\n");
	}	
}

void	show_rules(void)
{
	printf(" ____________________________        ______________________\n");
	printf("/                            \\      /                      \\\n");
	printf("|  DEALER stands on soft 17  |      |  BLACKJACK pays 3:2  |\n");
	printf("\\____________________________/      \\______________________/\n\n");
}
