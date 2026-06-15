#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define ACE		1
#define JACK	11
#define QUEEN	12
#define KING	13

#define ACE_VAL		1
#define JACK_VAL	10
#define QUEEN_VAL	10
#define KING_VAL	10

#define N_DECKS		6
#define DECK_CARDS	52
#define LIMIT_RAND	2147482647L - (2147482647L % (N_DECKS * DECK_CARDS))

typedef	struct s_card
{
	int	rank;
	int	value;
	int	type;
}	t_card;

typedef struct s_hand
{
	int				has_ace;
	int				bet_amount;
	struct s_card	*cards[16];
	int				n_cards;
	int				total_value;
}	t_hand;

typedef struct s_player
{
	int				money;
	int				n_hands;

	struct s_hand	hands[4];
}	t_player;

//display.c
void	display_cards(t_player *player, t_player *dealer);//DISPLAYS CARDS and total for dealer and player(usually called each turn)
void	show_rules( void );

//game_prep.c
void	reset_player(t_player *player);
void	new_deck(t_card *(*new_deck)[DECK_CARDS * N_DECKS]);		//creates a deck of 52 cards, computes the true value and type of each card
t_card	*new_card( int rank, int type );			//self-explanatory
void	shuffle_deck(t_card *(*new_deck)[DECK_CARDS * N_DECKS]);	//takes a deck of 52 cards and swaps its content 52 times in ascending order with a random card
void	bet(t_player *player);	//ASKS the user for a bet amount, 0 < bet <= player.money

//game_turn.c
int		player_turn(t_player *player, t_card *(*deck)[DECK_CARDS * N_DECKS], t_player *dealer, int curr_hand);
void	dealer_turn(t_player *dealer, t_card *(*deck)[DECK_CARDS * N_DECKS], t_player *player);
void	deal_card(t_card *(*deck)[DECK_CARDS * N_DECKS], t_hand *hand, int amount);

//game_end.c
void	give_result(t_player *player, t_player *dealer);
#endif
