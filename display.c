#include "blackjack.h"

static void	display_card_design(t_card *card)		//CARD DESIGN DEPENDING ON VALUE AND TYPE
{
	switch (card->rank)
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
		for (int i = 0 ; i < dealer->hands[0].n_cards ; i++)
			display_card_design(dealer->hands[0].cards[i]);
		printf("= ");
		if (dealer->hands[0].has_ace > 0)			//chooses the displayed total value depending on the aces (1 or 11 for each ace)
		{
			printf("%d", dealer->hands[0].total_value - 10 * dealer->hands[0].has_ace);
			if (dealer->hands[0].total_value - 10 * dealer->hands[0].has_ace + 10 <= 21)
				printf("/%d", dealer->hands[0].total_value - 10 * dealer->hands[0].has_ace + 10);
		}
		else
			printf("%d", dealer->hands[0].total_value);
		printf("\n");
	}
	else			//only displays dealer's first card
	{
		display_card_design(dealer->hands[0].cards[0]);
		printf("= ");
		switch (dealer->hands[0].cards[0]->rank)
		{
			case (1) :
				printf("1/11\n");
				break ;
			default :
				printf("%d\n", dealer->hands[0].cards[0]->value);
		}
	}
	
	printf("PLAYER : ");
	for (int curr_hand = 0; curr_hand < player->n_hands; curr_hand++)
	{
		printf("HAND %d : ", curr_hand + 1);
		for (int i = 0 ; i < player->hands[curr_hand].n_cards ; i++)
			display_card_design(player->hands[curr_hand].cards[i]);
		printf("= ");
	
		if (player->hands[curr_hand].has_ace > 0)			//same as for the dealer
		{
			printf("%d", player->hands[curr_hand].total_value - 10 * player->hands[curr_hand].has_ace);
			if (player->hands[curr_hand].total_value - 10 * player->hands[curr_hand].has_ace + 10 <= 21)
				printf("/%d", player->hands[curr_hand].total_value - 10 * player->hands[curr_hand].has_ace + 10);
		}
		else
			printf("%d", player->hands[curr_hand].total_value);
		printf("\n");
	}
}
