#include "blackjack.h"
#include <string.h>
#include <stdbool.h>

static bool	is_under(t_hand *hand, int max)
{
	if ((hand->has_ace > 0 && hand->total_value + 10 <= 21 && hand->total_value + 10 < max)
			|| (((hand->has_ace > 0 && hand->total_value + 10 > 21) || !hand->has_ace) && hand->total_value < max))
		return (true);
	return (false);
}

static void	split_hand(t_player *player, t_hand *src, t_hand *dest)
{
	src->total_value -= src->cards[1]->value;
	dest->total_value = src->total_value;
	dest->cards[0] = src->cards[1];
	src->cards[1] = NULL;
	if (dest->cards[0]->rank == ACE)
	{
		dest->has_ace++;
		src->has_ace--;
	}
	dest->n_cards++;
	src->n_cards--;
	player->money -= src->bet_amount;
	dest->bet_amount = src->bet_amount;
}

int	player_turn(t_player *player, t_card *(*deck)[DECK_CARDS * N_DECKS], t_player *dealer, int curr_hand)
{
	char	buf[16];
	static int		last_move = 2;
	bool	can_double = false;
	bool	can_split = false;

	while (is_under(&player->hands[curr_hand], 21) == true)
	{
		printf("STAND, HIT");
		if (player->hands[curr_hand].bet_amount <= player->money && player->hands[curr_hand].n_cards == 2)
		{
			can_double = true;
			printf(", DOUBLE");
			if (player->hands[curr_hand].cards[0]->value == player->hands[curr_hand].cards[1]->value && player->n_hands <= 3)
			{
				can_split = true;
				printf(", SPLIT");
			}
		}
		printf(" : \n");
		read(0, buf, 15);
		buf[15] = 0;

		if (strncmp("STAND\n", buf, 6) == 0)
		{
			last_move = 1;
			break ;
		}
		else if (strncmp("HIT\n", buf, 4) == 0)
		{
			last_move = 2;
			deal_card(deck, &player->hands[curr_hand], 1);
			display_cards(player, dealer);
		}
		else if (can_double && strncmp("DOUBLE\n", buf, 7) == 0)
		{
			last_move = 3;
			deal_card(deck, &player->hands[curr_hand], 1);
			player->money -= player->hands[curr_hand].bet_amount;
			player->hands[curr_hand].bet_amount *= 2;
			display_cards(player, dealer);
			break ;
		}
		else if (can_split && strncmp("SPLIT\n", buf, 6) == 0)
		{
			split_hand(player, &player->hands[curr_hand], &player->hands[player->n_hands]);
			player->n_hands++;
			display_cards(player, dealer);
			
			deal_card(deck, &player->hands[curr_hand], 1);
			display_cards(player, dealer);

			if (player->hands[curr_hand].cards[0]->rank == ACE)
				break ;

			last_move = 4;
		}
	}
	//checks if there are still hands to play
	if (curr_hand < player->n_hands - 1)
	{
		deal_card(deck, &player->hands[curr_hand + 1], 1);
		display_cards(player, dealer);
	
		if (player->hands[curr_hand + 1].cards[0]->rank != ACE)
			player_turn(player, deck, dealer, curr_hand + 1);
	}

	return (last_move);
}

void	dealer_turn(t_player *dealer, t_card *(*deck)[DECK_CARDS * N_DECKS], t_player *player)
{
	while (is_under(&dealer->hands[0], 17) == true)
	{
		deal_card(deck, &dealer->hands[0], 1);
		display_cards(player, dealer);
		sleep(1);
	}
}

void	deal_card(t_card *(*deck)[DECK_CARDS * N_DECKS], t_hand *hand, int amount)
{
	static int	i = 0;

	while (amount > 0)
	{
		while (deck[0][i] == NULL) { ++i; }

		hand->cards[hand->n_cards] = deck[0][i];
		deck[0][i] = NULL;
		hand->total_value += hand->cards[hand->n_cards]->value;
		if (hand->cards[hand->n_cards]->rank == ACE)
			hand->has_ace += 1;

		hand->n_cards++;
		amount--;
	}
}

