#include "blackjack.h"
#include <string.h>
#include <stdbool.h>

/*static bool	is_stand(char buf[16])
static bool	is_split(char buf[16])
static bool	is_double(char buf[16])
static bool	is_hit(char buf[16])*/

//takes the max value or max soft value under 21 for aces cases, if under max continue, if over max stop
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
	//takes second card of original hand to and gives it to the new one
	dest->cards[0] = src->cards[1];
	src->cards[1] = NULL;
	if (dest->cards[0]->rank == ACE)
	{
		dest->has_ace++;
		src->has_ace--;
	}

	dest->n_cards++;
	src->n_cards--;
	//substracts bet_amount from player->money, when split bet amount is the same for the two hands
	player->money -= src->bet_amount;
	dest->bet_amount = src->bet_amount;
}

int	player_turn(t_player *player, t_card *(*deck)[DECK_CARDS * N_DECKS], t_player *dealer, int curr_hand)
{
	char	buf[16];
	static int		last_move = 2;
	bool	can_double = false;
	bool	can_split = false;

	//while under 21 or until stand
	while (is_under(&player->hands[curr_hand], 21) == true)
	{
		printf("STAND, HIT");
		//can double only if 2 cards in the hand and enough money
		if (player->hands[curr_hand].bet_amount <= player->money && player->hands[curr_hand].n_cards == 2)
		{
			can_double = true;
			printf(", DOUBLE");
			//same as for double + can split max 3 times for 4 hands total
			if (player->hands[curr_hand].cards[0]->value == player->hands[curr_hand].cards[1]->value && player->n_hands <= 3)
			{
				can_split = true;
				printf(", SPLIT");
			}
		}
		printf(" : \n");
		read(0, buf, 15);
		buf[15] = 0;

		if (strncmp("STAND\n", buf, 6) == 0 || strncmp("stand\n", buf, 6) == 0)
		{
			//stand ends the player's turn
			last_move = 1;
			break ;
		}
		else if (strncmp("HIT\n", buf, 4) == 0 || strncmp("hit\n", buf, 4) == 0)
		{
			//hit draws one card
			last_move = 2;
			deal_card(deck, &player->hands[curr_hand], 1);
			display_cards(player, dealer);
		}
		else if (can_double && (strncmp("DOUBLE\n", buf, 7) == 0 || strncmp("double\n", buf, 7) == 0))
		{
			//double doubles the bet_amount and draws one card then player's turn ends
			last_move = 3;
			deal_card(deck, &player->hands[curr_hand], 1);
			player->money -= player->hands[curr_hand].bet_amount;
			player->hands[curr_hand].bet_amount *= 2;
			display_cards(player, dealer);
			break ;
		}
		else if (can_split && (strncmp("SPLIT\n", buf, 6) == 0 || strncmp("split\n", buf, 6) == 0))
		{
			//splits the hand in two and duplicates the bet_amount to both hands
			split_hand(player, &player->hands[curr_hand], &player->hands[player->n_hands]);
			player->n_hands++;
			display_cards(player, dealer);
			sleep(1);
			//a card is automatically dealt to current hand after a split	
			deal_card(deck, &player->hands[curr_hand], 1);
			display_cards(player, dealer);
			//on an aces split the player's turn ends after both hands have received 1 more card
			if (player->hands[curr_hand].cards[0]->rank == ACE)
				break ;

			last_move = 4;
		}
	}
	//checks if there are still hands to play
	if (curr_hand < player->n_hands - 1)
	{
		if (last_move != 1)
			sleep(1);
		//at the end of the current hand, if a split has occured, the second card is dealt to the new hand
		deal_card(deck, &player->hands[curr_hand + 1], 1);
		display_cards(player, dealer);
		//checks for an aces split
		if (player->hands[curr_hand + 1].cards[0]->rank != ACE)
			player_turn(player, deck, dealer, curr_hand + 1);
	}

	return (last_move);
}

void	dealer_turn(t_player *dealer, t_card *(*deck)[DECK_CARDS * N_DECKS], t_player *player)
{
	//draws until soft 17
	while (is_under(&dealer->hands[0], 17) == true)
	{
		deal_card(deck, &dealer->hands[0], 1);
		display_cards(player, dealer);
		sleep(1);
	}
}

void	deal_card(t_card *(*deck)[DECK_CARDS * N_DECKS], t_hand *hand, int amount)
{
	//i begins at the last cards took each call
	static int	i = 0;

	while (amount > 0)
	{
		//until valid card
		while (deck[0][i] == NULL) { ++i; }

		//takes card from deck to give it to the hand
		hand->cards[hand->n_cards] = deck[0][i];
		deck[0][i] = NULL;

		hand->total_value += hand->cards[hand->n_cards]->value;
		if (hand->cards[hand->n_cards]->rank == ACE)
			hand->has_ace += 1;

		hand->n_cards++;
		amount--;
	}
}

