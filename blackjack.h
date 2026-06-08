#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef	struct s_card
{
	int	value;
	int	type;
}	t_card;

typedef struct s_player
{
	int				has_ace;
	int				bet_amount;
	int				money;
	struct s_card	*cards[16];
	int				n_cards;
	int				total_value;
}	t_player;

//display.c
void	deal_card(t_card *(*deck)[52], t_player *player, int amount);
void	display_cards(t_player *player, t_player *dealer, int dealer_reveal);//DISPLAYS CARDS and total for dealer and player(usually called each turn)

//game_prep.c
void	reset_player(t_player *player);
void	new_deck(t_card *(*new_deck)[52]);		//creates a deck of 52 cards, computes the true value and type of each card
t_card	*new_card( int value, int type );			//self-explanatory
void	shuffle_deck(t_card *(*new_deck)[52]);	//takes a deck of 52 cards and swaps its content 52 times in ascending order with a random card
void	bet(t_player *player);	//ASKS the user for a bet amount, 0 < bet <= player.money
