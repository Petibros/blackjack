#include <blackjack.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

static void	display_card_design(t_card *card)
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
			break ;
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

static void	display_cards(t_player *player, t_player *dealer, int dealer_reveal)
{
	printf("DEALER : ");

	if (dealer_reveal)
	{
		for (int i = 0 ; i < dealer->n_cards ; i++)
			display_card_design(dealer->cards[i]);
		printf("= ");
		if (dealer->has_ace > 0)
		{
			printf("%d", dealer->total_value - 10 * dealer->has_ace);
			if (dealer->total_value - 10 * dealer->has_ace + 10 <= 21)
				printf("/%d", dealer->total_value - 10 * dealer->has_ace + 10);
		}
		else
			printf("%d", dealer->total_value);
		printf("\n");
	}
	else
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

	if (player->has_ace > 0)
	{
		printf("%d", player->total_value - 10 * player->has_ace);
		if (player->total_value - 10 * player->has_ace + 10 <= 21)
			printf("/%d", player->total_value - 10 * player->has_ace + 10);
	}
	else
		printf("%d", player->total_value);
	printf("\n");
}

static void	player_turn(t_player *player, t_card *(*deck)[52], t_player *dealer)
{
	char	buf[16];

	while (player->total_value <= 21)
	{
		printf("STAND, HIT : \n");
		read(0, buf, 15);
		buf[15] = 0;

		if (strncmp("STAND\n", buf, 6) == 0)
			break ;
		else if (strncmp("HIT\n", buf, 4) == 0)
		{
			deal_card(deck, player, 1);
			display_cards(player, dealer, 0);
		}
	}
	
	if (player->total_value > 21 && player->has_ace > 0)
	{
		player->has_ace--;
		player->total_value -= 10;
		player_turn(player, deck, dealer);
	}
}

static void	dealer_turn(t_player *dealer, t_card *(*deck)[52], t_player *player)
{
	while (dealer->total_value < 17)
	{
		deal_card(deck, dealer, 1);
		display_cards(player, dealer, 1);
		sleep(1);
	}

	if (dealer->total_value > 21 && dealer->has_ace > 0)
	{
		dealer->has_ace--;
		dealer->total_value -= 10;
		dealer_turn(dealer, deck, player);
	}
}

static void	bet(t_player *player)
{
	char	buf[16];
	int		bet;

	while (1)
	{
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

void	deal_card(t_card *(*deck)[52], t_player *player, int amount)
{
	static int	i = 0;

	while (amount > 0)
	{
		while (deck[0][i] == NULL) { ++i; }

		player->cards[player->n_cards] = deck[0][i];
		deck[0][i] = NULL;

		switch (player->cards[player->n_cards]->value)
		{
			case (11) :
				player->total_value += 10;
				break ;
			case (12) :
				player->total_value += 10;
				break ;
			case (13) :
				player->total_value += 10;
				break ;
			case (1) :
				player->has_ace += 1;
				player->total_value += 11;
				break ;
			default :
				player->total_value += player->cards[player->n_cards]->value;
		}
		player->n_cards++;
		amount--;
	}
}

static void	shuffle_deck(t_card *(*new_deck)[52])
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

static t_card *new_card( int value, int type )
{
	t_card *new = malloc(sizeof(t_card));

	new->type = type;
	new->value = value;
	return (new);
}

static void	new_deck(t_card *(*new_deck)[52])
{
	for (int n = 0 ; n < 52 ; n += 4)
	{
		for (int type = 0 ; type < 4 ; type++)
		{
			new_deck[0][n + type] = new_card(n / 4 + 1, type + 1);
		}
	}
}

int	main()
{
	t_card		*deck[52];
	char		seed[1];
	t_player	dealer, player;

	int fd = open("/dev/random", O_RDONLY);			//SEED GEN (for shuffling)
	read(fd, seed, 1);
	close(fd);
	srand(seed[0]);

	bzero(player.cards, sizeof(t_card *) * 16);
	bzero(dealer.cards, sizeof(t_card *) * 16);
	player.money = 500;
	player.total_value = 0;
	player.n_cards = 0;
	player.has_ace = 0;
	dealer.total_value = 0;
	dealer.n_cards = 0;
	dealer.has_ace = 0;

	new_deck(&deck);									//DECK CREATION
	shuffle_deck(&deck);								//SHUFFLE

	bet(&player);
	deal_card(&deck, &player, 2);
	deal_card(&deck, &dealer, 2);
	display_cards(&player, &dealer, 0);

	player_turn(&player, &deck, &dealer);
	display_cards(&player, &dealer, 1);
	dealer_turn(&dealer, &deck, &player);

	printf("FINAL :\n");
	display_cards(&player, &dealer, 1);
/*		
	for (int i = 0 ; i < 52 ; i++)
	{
		if (deck[i])
			printf("value : %d, type : %d  CARD %d\n", deck[i]->value, deck[i]->type, i + 1);
		if (i < 16)
		{
			if (player.cards[i])
				printf("value : %d, type : %d  CARD %d\n", player.cards[i]->value, player.cards[i]->type, i + 1);
			if (dealer.cards[i])
				printf("value : %d, type : %d  CARD %d\n", dealer.cards[i]->value, dealer.cards[i]->type, i + 1);
		}
*/
	for (int i = 0 ; i < 52 ; i++ )
	{
		if (i < 16)
		{
			if (player.cards[i])
				free(player.cards[i]);
			if (dealer.cards[i])
				free(dealer.cards[i]);
		}
		if (deck[i])
			free(deck[i]);
	}
}
