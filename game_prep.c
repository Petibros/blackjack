#include "blackjack.h"
#include <strings.h>

void	shuffle_deck(t_card *(*new_deck)[52])	//takes a deck of 52 cards and swaps its content 52 times in ascending order with a random card
{
	int	i_swap;
	t_card *tmp;

	for (int i = 0 ; i < 52 ; i++)
	{
		i_swap = rand() % 52;
	//	printf("%d\n", i_swap);

		tmp = new_deck[0][i];
		new_deck[0][i] = new_deck[0][i_swap];
		new_deck[0][i_swap] = tmp;
	}
}

t_card *new_card( int value, int type )			//self-explanatory
{
	t_card *new = malloc(sizeof(t_card));

	new->type = type;
	new->value = value;
	return (new);
}

void	new_deck(t_card *(*new_deck)[52])		//creates a deck of 52 cards, computes the true value and type of each card
{
	for (int n = 0 ; n < 52 ; n += 4)
	{
		for (int type = 0 ; type < 4 ; type++)
		{
			new_deck[0][n + type] = new_card(n / 4 + 1, type + 1);
		}
	}
}

void	reset_player(t_player *player)
{
	bzero(player->cards, sizeof(t_card *) * 16);
	player->money = 500;
	player->total_value = 0;
	player->bet_amount = 0;
	player->n_cards = 0;
	player->has_ace = 0;
}

void	bet(t_player *player)		//ASKS the user for a bet amount, 0 < bet <= player.money
{
	char	buf[16];
	int		bet;

	while (1)
	{
		printf("MONEY : %d, your BET ?\n", player->money);
		read(0, buf, 16);
		bet = atoi(buf);
		if (bet > 0 && bet <= player->money)
		{
			player->money -= bet;
			player->bet_amount = bet;
			break ;
		}
	}
}

