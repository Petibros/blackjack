#include "blackjack.h"

static void	display_card_design(t_card *card)		//CARD DESIGN DEPENDING ON VALUE AND TYPE
{
	switch (card->value)
	{
		case (1) :
			printf("ACE ");
			break ;
		case (2) :
			printf("TWO ");
			break ;
		case (3) :
			printf("THREE ");
			break ;
		case (4) :
			printf("FOUR ");
			break ;
		case (5) :
			printf("FIVE ");
			break ;
		case (6) :
			printf("SIX ");
			break ;									//MDR 6-7		ahhhhhhhhh
		case (7) :
			printf("SEVEN ");
			break ;
		case (8) :
			printf("EIGHT ");
			break ;
		case (9) :
			printf("NINE ");
			break ;
		case (10) :
			printf("TEN ");
			break ;
		case (11) :
			printf("JACK ");
			break ;
		case (12) :
			printf("QUEEN ");
			break ;
		case (13) :
			printf("KING ");
			break ;
	}
}

void	display_cards(t_player *player, t_player *dealer, int dealer_reveal)//DISPLAYS CARDS and total for dealer and player(usually called each turn)
{
	printf("DEALER : ");

	if (dealer_reveal)		//if true reveals dealer's second card (player only sees the first card on his turn)
	{
		for (int i = 0 ; i < dealer->n_cards ; i++)
			display_card_design(dealer->cards[i]);
		printf("= ");
		if (dealer->has_ace > 0)			//chooses the displayed total value depending on the aces (1 or 11 for each ace)
		{
			printf("%d", dealer->total_value - 10 * dealer->has_ace);
			if (dealer->total_value - 10 * dealer->has_ace + 10 <= 21)
				printf("/%d", dealer->total_value - 10 * dealer->has_ace + 10);
		}
		else
			printf("%d", dealer->total_value);
		printf("\n");
	}
	else			//only displays dealer's first card
	{
		display_card_design(dealer->cards[0]);
		printf("= ");
		switch (dealer->cards[0]->value)
		{
			case (1) :
				printf("1/11\n");
				break ;
			case (11) :
				printf("10\n");
				break ;
			case (12) :
				printf("10\n");
				break ;
			case (13) :
				printf("10\n");
				break ;
			default :
				printf("%d\n", dealer->cards[0]->value);
		}
	}
	
	printf("PLAYER : ");
	
	for (int i = 0 ; i < player->n_cards ; i++)
		display_card_design(player->cards[i]);
	printf("= ");

	if (player->has_ace > 0)			//same as for the dealer
	{
		printf("%d", player->total_value - 10 * player->has_ace);
		if (player->total_value - 10 * player->has_ace + 10 <= 21)
			printf("/%d", player->total_value - 10 * player->has_ace + 10);
	}
	else
		printf("%d", player->total_value);
	printf("\n");
}
