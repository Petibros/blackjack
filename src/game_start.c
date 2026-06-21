
#include "blackjack.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void	shuffle_deck(t_card *(*new_deck)[DECK_CARDS * N_DECKS])
{
	long	i_swap;
	t_card *tmp;

	for (int i = 0 ; i < DECK_CARDS * N_DECKS; i++)
	{
		//okay this one is a bit tricky				//By performing a % operation on an integer I essentially divide this integer into equal parts, the thing
		i_swap = random();							//is that random_max isn't divisible by every number.
		while (i_swap >= LIMIT_RAND)				//For example : random_MAX = 18, divide by 7 and take the rest -> 2 chances to get 6 -> i_swap = (6, 13)
			i_swap = random();						//and 3 chances to get 2 -> i_swap = (2, 9, 16). So to get equal chances for every number i have to crop
													//the max -> if I redraw for every number number bigger than 13 then I have equal chances for every number
		i_swap = i_swap % (DECK_CARDS * N_DECKS);	//including 0. That's the exact same for RANDOM_MAX. 
													//so LIMIT_RAND = the max number in RANDOM_MAX divisible by DECK_CARDS * N_DECKS.
		tmp = new_deck[0][i];
		new_deck[0][i] = new_deck[0][i_swap];
		new_deck[0][i_swap] = tmp;
	}
}

t_card *new_card( int rank, int type )
{
	t_card *new = malloc(sizeof(t_card));
	if (!new)
		return (NULL);

	new->type = type;
	new->rank = rank;
	//rank decides value -> a queen's rank is 12 but its value 10
	switch (rank)
	{
		case (ACE) :
			new->value = ACE_VAL;
			break ;
		case (JACK) :
			new->value = JACK_VAL;
			break ;
		case (QUEEN) :
			new->value = QUEEN_VAL;
			break ;
		case (KING) :
			new->value = KING_VAL;
			break ;
		default :
			new->value = rank;
	}
	return (new);
}

int	new_deck(t_card *(*new_deck)[DECK_CARDS * N_DECKS])
{
	bzero(new_deck, sizeof(t_card *) * DECK_CARDS * N_DECKS);

	//loops for each deck (N_DECKS times)
	for (int n_deck = 0; n_deck < DECK_CARDS * N_DECKS; n_deck += 52)
	{
		//loops for each rank (13 times)
		for (int n = 0 ; n < DECK_CARDS; n += 4)
		{
			//loops for each type (4 times)
			for (int type = 0 ; type < 4 ; type++)
			{
				//rank starts at 1 so n / n_types(4) + 1, type also starts at 1
				new_deck[0][n_deck + n + type] = new_card(n / 4 + 1, type + 1);
				if (new_deck[0][n_deck + n + type] == NULL)
					return (1);
			}
		}
	}
	return (0);
}

void	reset_player(t_player *player)
{
	//do I really have to explain something here ?
	player->n_hands = 1;
	player->curr_hand = 0;	

	for (int i = 0; i < 4; i++)
	{
		bzero(player->hands[i].cards, sizeof(t_card *) * 16);
		player->hands[i].total_value = 0;
		player->hands[i].bet_amount = 0;
		player->hands[i].n_cards = 0;
		player->hands[i].has_ace = 0;
		player->hands[i].in_play = false;
	}
}

int	bet(t_player *player)
{
	char	buf[16];
	int		bet;

	//asks wanted bet_amount until user's input is valid or 'q' to quit
	while (1)
	{
		if (player->last_bet > player->money || player->last_bet <= 0)
			printf("MONEY : %d, your BET ?     ALL-IN : 'a' QUIT : 'q'\n", player->money);
		else
			printf("MONEY : %d, your BET ?     ALL-IN : 'a' LAST BET (%d) : 'l' QUIT : 'q'\n", player->money, player->last_bet);
		
		read(0, buf, 16);
		
		if (strncmp(buf, "q\n", 2) == 0)
			return (-1);
		else if (strncmp(buf, "a\n", 2) == 0)
			bet = player->money;
		else if (strncmp(buf, "l\n", 2) == 0)
			bet = player->last_bet;
		else
			bet = atoi(buf);
		
		if (bet > 0 && bet <= player->money)
		{
			player->money -= bet;
			player->hands[0].bet_amount = bet;
			player->last_bet = bet;
			break ;
		}
	}
	return (0);
}
