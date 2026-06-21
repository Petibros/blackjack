#include "blackjack.h"
#include <string.h>
#include <stdbool.h>

static bool	is_switch(char buf[16], char binding)
{
	if (strncmp("SWITCH\n", buf, 7) == 0 || strncmp("switch\n", buf, 7) == 0 || (buf[0] == binding && buf[1] == '\n'))
		return (true);
	return (false);
}

static bool	is_stand(char buf[16], char binding)
{
	if (strncmp("STAND\n", buf, 6) == 0 || strncmp("stand\n", buf, 6) == 0 || (buf[0] == binding && buf[1] == '\n'))
		return (true);
	return (false);
}

static bool	is_split(char buf[16], char binding)
{
	if (strncmp("SPLIT\n", buf, 6) == 0 || strncmp("split\n", buf, 6) == 0 || (buf[0] == binding && buf[1] == '\n'))
		return (true);
	return (false);
}

static bool	is_double(char buf[16], char binding)
{
	if (strncmp("DOUBLE\n", buf, 7) == 0 || strncmp("double\n", buf, 7) == 0 || (buf[0] == binding && buf[1] == '\n'))
		return (true);
	return (false);
}

static bool	is_hit(char buf[16], char binding)
{
	if (strncmp("HIT\n", buf, 4) == 0 || strncmp("hit\n", buf, 4) == 0 || (buf[0] == binding && buf[1] == '\n'))
		return (true);
	return (false);
}

//takes the max value or max soft value under 21 for aces cases, if under max continue, if over max stop
static bool	is_under(t_hand *hand, int max)
{
	if ((hand->has_ace > 0 && hand->total_value + 10 <= 21 && hand->total_value + 10 < max)
			|| (((hand->has_ace > 0 && hand->total_value + 10 > 21) || !hand->has_ace) && hand->total_value < max))
		return (true);
	return (false);
}

//at the end of the turn lets the player choose which hand to play
static void	choose_hand(t_player *player, t_bindings *bindings)
{
	char	buf[16];


	printf("CHOOSE HAND TO PLAY     ");
	if (player->hands[0].in_play == true)
		printf("  1 : '%c'", bindings->HAND_1);
	if (player->hands[1].in_play == true)
		printf("  2 : '%c'", bindings->HAND_2);
	if (player->hands[2].in_play == true)
		printf("  3 : '%c'", bindings->HAND_3);
	if (player->hands[3].in_play == true)
		printf("  4 : '%c'", bindings->HAND_4);
	printf("\n");

	read(0, buf, 15);
	buf[15] = 0;

	//hand must be under 21 and existing
	if (buf[0] == bindings->HAND_1 && buf[1] == '\n' && 1 <= player->n_hands && player->hands[0].in_play == true)
		player->curr_hand = 0;
	else if (buf[0] == bindings->HAND_2 && buf[1] == '\n' && 2 <= player->n_hands && player->hands[1].in_play == true)
		player->curr_hand = 1;
	else if (buf[0] == bindings->HAND_3 && buf[1] == '\n' && 3 <= player->n_hands && player->hands[2].in_play == true)
		player->curr_hand = 2;
	else if (buf[0] == bindings->HAND_4 && buf[1] == '\n' && 4 <= player->n_hands && player->hands[3].in_play == true)
		player->curr_hand = 3;
	else
		printf("Can't switch, hand total over or egal to 21 or non existant\n");
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

int	player_turn(t_player *player, t_card *(*deck)[DECK_CARDS * N_DECKS], t_player *dealer, t_bindings *bindings)
{
	char	buf[16];
	static int		last_move = 2;
	bool	can_double = false;
	bool	can_split = false;

	//while under 21 or until stand
	while (is_under(&player->hands[player->curr_hand], 21) == true)
	{
		printf("STAND (end turn) : %c, HIT : %c", bindings->STAND, bindings->HIT);
		//can double only if 2 cards in the hand and enough money
		if (player->hands[player->curr_hand].bet_amount <= player->money && player->hands[player->curr_hand].n_cards == 2)
		{
			can_double = true;
			printf(", DOUBLE : %c", bindings->DOUBLE);
			//same as for double + can split max 3 times for 4 hands total
			if (player->hands[player->curr_hand].cards[0]->value == player->hands[player->curr_hand].cards[1]->value && player->n_hands <= 3)
			{
				can_split = true;
				printf(", SPLIT : %c", bindings->SPLIT);
			}
		}
		if (player->n_hands > 1 && (player->hands[0].in_play == true || player->hands[1].in_play == true || player->hands[2].in_play == true || player->hands[3].in_play == true))
			printf(", SWITCH HAND : %c", bindings->SWITCH);
		printf("\n");
		read(0, buf, 15);
		buf[15] = 0;

		if (is_stand(buf, bindings->STAND))
		{
			//stand ends the player's turn
			last_move = 1;
			player->hands[0].in_play = false;
			player->hands[1].in_play = false;
			player->hands[2].in_play = false;
			player->hands[3].in_play = false;
			break ;
		}
		else if (is_hit(buf, bindings->HIT))
		{
			//hit draws one card
			last_move = 2;
			deal_card(deck, &player->hands[player->curr_hand], 1);
			display_cards(player, dealer);
		}
		else if (can_double && is_double(buf, bindings->DOUBLE))
		{
			//double doubles the bet_amount and draws one card then player's turn ends
			last_move = 3;
			deal_card(deck, &player->hands[player->curr_hand], 1);
			player->money -= player->hands[player->curr_hand].bet_amount;
			player->hands[player->curr_hand].bet_amount *= 2;
			display_cards(player, dealer);
			break ;
		}
		else if (can_split && is_split(buf, bindings->SPLIT))
		{
			//splits the hand in two and duplicates the bet_amount to both hands
			split_hand(player, &player->hands[player->curr_hand], &player->hands[player->n_hands]);
			player->hands[player->n_hands].in_play = true;
			player->n_hands++;
			display_cards(player, dealer);
			sleep(1);
			//a card is automatically dealt to both hands after a split	
			deal_card(deck, &player->hands[player->curr_hand], 1);
			display_cards(player, dealer);
			sleep(1);
			deal_card(deck, &player->hands[player->n_hands - 1], 1);
			display_cards(player, dealer);

			//on an aces split the player's turn ends after both hands have received 1 more card
			if (player->hands[player->curr_hand].cards[0]->rank == ACE)
			{
				player->hands[player->n_hands - 1].in_play = false;
				break ;
			}

			last_move = 4;
		}
		else if (player->n_hands > 1 && is_switch(buf, bindings->SWITCH))
		{
			choose_hand(player, bindings);
			last_move = 5;
		}
	}
	player->hands[player->curr_hand].in_play = false;

	//checks if there are still hands to play
	if (player->n_hands > 1) 
	{
		if (player->hands[0].in_play == true)
			player->curr_hand = 0;
		else if (player->hands[1].in_play == true)
			player->curr_hand = 1;
		else if (player->hands[2].in_play == true)
			player->curr_hand = 2;
		else if (player->hands[3].in_play == true)
			player->curr_hand = 3;
		else
			return (last_move);
		sleep(1);
		display_cards(player, dealer);
		player_turn(player, deck, dealer, bindings);
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

