#include "blackjack.h"
#include <stdio.h>

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

static void	add_padding(int n_spaces)
{	
	for (int n = 0 ; n < n_spaces; n++)
		printf(" ");
}

static void	print_split_hands(t_hand *first, t_hand *second, int pair, int current)
{
	int	padding_text = 88;

	if (!first)
		return ;

	//displays total_value and padding for the text
	if (current == 1 + pair * 2)
	{
		printf("CURRENT : ");
		padding_text -= 10;
	}
	printf("HAND %d = %d", 1 + pair * 2, first->total_value);
	if (first->total_value / 10 >= 1)
		padding_text--;
	if (first->has_ace > 0 && first->total_value + 10 <= 21)
	{
		printf("/%d", first->total_value + 10);
		padding_text -= 3;
	}
	if (second != NULL)
	{
		add_padding(padding_text);
		if (current == 2 + pair * 2)
			printf("CURRENT : ");
		printf("HAND %d = %d", 2 + pair * 2, second->total_value);
		if (second->has_ace > 0 && second->total_value + 10 <= 21)
			printf("/%d", second->total_value + 10);
	}
	printf("\n");

	//displays by pair of two hands so -> all first then padding then all second
	for (int i = 0; i < first->n_cards; i++)
		printf("\033[30;47m┌────────┐\033[0m  ");
	if (second != NULL)
	{
		add_padding(100 - first->n_cards * 12 - 2);
		for (int i = 0; i < second->n_cards; i++)
			printf("\033[30;47m┌────────┐\033[0m  ");
	}
	printf("\n");
	for (int i = 0; i < first->n_cards; i++)
		printf("\033[30;47m│%s      │\033[0m  ", get_rank(first->cards[i]->rank, 1));
	if (second != NULL)
	{
		add_padding(100 - first->n_cards * 12 - 2);
		for (int i = 0; i < second->n_cards; i++)
			printf("\033[30;47m│%s      │\033[0m  ", get_rank(second->cards[i]->rank, 1));
	}
	printf("\n");
	for (int i = 0; i < first->n_cards; i++)
		printf("\033[30;47m│        │\033[0m  ");
	if (second != NULL)
	{
		add_padding(100 - first->n_cards * 12 - 2);
		for (int i = 0; i < second->n_cards; i++)
			printf("\033[30;47m│        │\033[0m  ");
	}
	printf("\n");
	for (int i = 0; i < first->n_cards; i++)
		printf("\033[30;47m│   %s   │\033[0m  ", get_type(first->cards[i]->type));
	if (second != NULL)
	{
		add_padding(100 - first->n_cards * 12 - 2);
		for (int i = 0; i < second->n_cards; i++)
			printf("\033[30;47m│   %s   │\033[0m  ", get_type(second->cards[i]->type));
	}
	printf("\n");
	for (int i = 0; i < first->n_cards; i++)
		printf("\033[30;47m│        │\033[0m  ");
	if (second != NULL)
	{
		add_padding(100 - first->n_cards * 12 - 2);
		for (int i = 0; i < second->n_cards; i++)
			printf("\033[30;47m│        │\033[0m  ");
	}
	printf("\n");
	for (int i = 0; i < first->n_cards; i++)
		printf("\033[30;47m│      %s│\033[0m  ", get_rank(first->cards[i]->rank, 2));
	if (second != NULL)
	{
		add_padding(100 - first->n_cards * 12 - 2);
		for (int i = 0; i < second->n_cards; i++)
			printf("\033[30;47m│      %s│\033[0m  ", get_rank(second->cards[i]->rank, 2));
	}
	printf("\n");
	for (int i = 0; i < first->n_cards; i++)
		printf("\033[30;47m└────────┘\033[0m  ");
	if (second != NULL)
	{
		add_padding(100 - first->n_cards * 12 - 2);
		for (int i = 0; i < second->n_cards; i++)
			printf("\033[30;47m└────────┘\033[0m  ");
	}
	printf("\n");

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
	
	//if player has only one hand, displays in the normal size, else tinier format
	if (player->n_hands == 1)
	{
		printf("\nPLAYER = %d", player->hands[0].total_value);
		//chooses the displayed total value depending on the aces
		if (player->hands[0].has_ace > 0 && player->hands[0].total_value + 10 <= 21)
			printf("/%d", player->hands[0].total_value + 10);
		printf("\n");
		print_hand(&player->hands[0]);
	}
	else
	{
		printf("\nPLAYER : \n");
		for (int curr_hand = 0; curr_hand < player->n_hands; curr_hand += 2)
		{
			if (player->hands[curr_hand + 1].n_cards != 0)
				print_split_hands(&player->hands[curr_hand], &player->hands[curr_hand + 1], curr_hand / 2, player->curr_hand + 1);
			else
				print_split_hands(&player->hands[curr_hand], NULL, curr_hand / 2, player->curr_hand + 1);
		}
	}
	printf("\n");
}

void	show_rules(void)
{
	printf("								\033[97;42m┌────────────────────────────┐\033[0m      \033[97;42m┌──────────────────────┐\033[0m\n");
	printf("								\033[97;42m│  DEALER stands on soft 17  │\033[0m      \033[97;42m│  BLACKJACK pays 3:2  │\033[0m\n");
	printf("								\033[97;42m└────────────────────────────┘\033[0m      \033[97;42m└──────────────────────┘\033[0m\n\n");
}
