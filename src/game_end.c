#include "blackjack.h"

void	give_result(t_player *player, t_player *dealer)
{
	int	earnings;
	int	total_earnings = 0;

	//takes the highest value under 21 (ace value is either 1 or 11 but counted as 1 in total_value)
	int	dealer_res = dealer->hands[0].total_value;
	if (dealer->hands[0].has_ace && dealer_res + 10 <= 21)
		dealer_res += 10;

	//total_value > 21 == lose in all cases == -1
	if (dealer_res > 21)
		dealer_res = -1;
	//earnings are different depending on blackjack and blackjack beats a normal 21 so blackjack == 22
	else if (dealer_res == 21 && dealer->hands[0].n_cards == 2)
		dealer_res = 22;
	
	int	player_res[4];

	printf("\n");
	//does the same for all hands in play
	for (int i = 0; i < player->n_hands; i++)
	{
		earnings = 0;
		//takes the highest value under 21 (ace value is either 1 or 11 but counted as 1 in total_value)
		player_res[i] = player->hands[i].total_value;
		if (player->hands[i].has_ace && player_res[i] + 10 <= 21)
			player_res[i] += 10;
		
		//total_value > 21 == lose in all cases == -1
		if (player_res[i] > 21)
			player_res[i] = -1;
		//earnings are different depending on blackjack and blackjack beats a normal 21 so blackjack == 22
		else if (player_res[i] == 21 && player->hands[i].n_cards == 2 && player->n_hands == 1)
			player_res[i] = 22;

		//highest res wins
		if (player_res[i] > dealer_res)
		{
			//normal win -> bet refund + bet_amount
			earnings += player->hands[i].bet_amount * 2;
			//blackjack win -> bet refund + bet_amount * 1.5 (3:2)
			if (player_res[i] == 22)
				earnings += player->hands[i].bet_amount / 2;
			printf("HAND %d : WIN = +%d\n", i + 1, earnings - player->hands[i].bet_amount);
		}
		else if (player_res[i] == dealer_res && player_res[i] != -1)
		{
			//draw -> bet refund
			earnings += player->hands[i].bet_amount;
			printf("HAND %d : PUSH\n", i + 1);
		}
		else
			//lose -> bet lost
			printf("HAND %d : LOSE = -%d\n", i + 1, player->hands[i].bet_amount);
		player->money += earnings;
		total_earnings += earnings - player->hands[i].bet_amount;
	}
	printf("-------------------------------\n");
	if (total_earnings < 0)
		printf("TOTAL = %d\n", total_earnings);
	else
		printf("TOTAL = +%d\n", total_earnings);
}

void	free_cards(t_card *(*deck)[DECK_CARDS * N_DECKS], t_player *player, t_player *dealer)
{
	for (int i = 0 ; i < DECK_CARDS * N_DECKS; i++ )
	{
		if (i < 16)
		{
			//checks for a card to free at index = i for all hands
			for (int curr_hand = 0; curr_hand < player->n_hands; curr_hand++)
			{
				if (player->hands[curr_hand].cards[i])
					free(player->hands[curr_hand].cards[i]);
			}
			if (dealer->hands[0].cards[i])
				free(dealer->hands[0].cards[i]);
		}
		//checks for a card to free at index = i in deck
		if (deck[0][i])
			free(deck[0][i]);
	}
}
