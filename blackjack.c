#include <blackjack.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

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

int	main()
{
	t_card		*deck[52];
	char		seed[1];
	t_player	dealer, player;

	int fd = open("/dev/random", O_RDONLY);			//SEED GEN (for shuffling)
	read(fd, seed, 1);
	close(fd);
	srand(seed[0]);

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
