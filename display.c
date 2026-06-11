#include "blackjack.h"

static void	display_card_design(t_card *card)		//CARD DESIGN DEPENDING ON VALUE AND TYPE
{
	switch (card->rank)
	{
		case (ACE) :
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
		case (JACK) :
			printf("JACK ");
			break ;
		case (QUEEN) :
			printf("QUEEN ");
			break ;
		case (KING) :
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
		printf("= %d", dealer->hands[0].total_value);

		//chooses the displayed total value depending on the aces
		if (dealer->hands[0].has_ace > 0 && dealer->hands[0].total_value + 10 <= 21)
			printf("/%d", dealer->hands[0].total_value + 10);
		printf("\n");
	}
	else			//only displays dealer's first card
	{
		display_card_design(dealer->hands[0].cards[0]);
		printf("= ");
		switch (dealer->hands[0].cards[0]->rank)
		{
			case (ACE) :
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
		printf("= %d", player->hands[curr_hand].total_value);

		//chooses the displayed total value depending on the aces
		if (player->hands[curr_hand].has_ace > 0 && player->hands[curr_hand].total_value + 10 <= 21)
			printf("/%d", player->hands[curr_hand].total_value + 10);
		printf("\n");
	}
}
