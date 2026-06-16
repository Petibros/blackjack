#include "blackjack.h"

void	give_result(t_player *player, t_player *dealer)
{
	int	gain;
	int	player_res[4];
	int	dealer_res = dealer->hands[0].total_value;
	if (dealer->hands[0].has_ace && dealer_res + 10 <= 21)
		dealer_res += 10;

	if (dealer_res > 21)
		dealer_res = -1;
	else if (dealer_res == 21 && dealer->hands[0].n_cards == 2)
		dealer_res = 22;

	for (int i = 0; i < player->n_hands; i++)
	{
		gain = 0;
		player_res[i] = player->hands[i].total_value;
		if (player->hands[i].has_ace && player_res[i] + 10 <= 21)
			player_res[i] += 10;
		if (player_res[i] > 21)
			player_res[i] = -1;
		else if (player_res[i] == 21 && player->hands[i].n_cards == 2 && player->n_hands == 1)
			player_res[i] = 22;

		if (player_res[i] > dealer_res)
		{
			gain += player->hands[i].bet_amount * 2;
			if (player_res[i] == 22)
				gain += player->hands[i].bet_amount / 2;
			printf("HAND %d : WIN = +%d\n", i + 1, gain - player->hands[i].bet_amount);
		}
		else if (player_res[i] == dealer_res && player_res[i] != -1)
		{
			player->money += player->hands[i].bet_amount;
			printf("HAND %d : PUSH\n", i + 1);
		}
		else
			printf("HAND %d : LOSE\n", i + 1);
		player->money += gain;
	}
}

void	free_cards(t_card *(*deck)[DECK_CARDS * N_DECKS], t_player *player, t_player *dealer)
{
	for (int i = 0 ; i < DECK_CARDS * N_DECKS; i++ )
	{
		if (i < 16)
		{
			for (int curr_hand = 0; curr_hand < player->n_hands; curr_hand++)
			{
				if (player->hands[curr_hand].cards[i])
					free(player->hands[curr_hand].cards[i]);
			}
			if (dealer->hands[0].cards[i])
				free(dealer->hands[0].cards[i]);
		}
		if (deck[i])
			free(deck[i]);
	}
}
