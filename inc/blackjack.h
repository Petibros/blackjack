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

#define N_DECKS		3
#define DECK_CARDS	52
#define LIMIT_RAND	2147482647L - (2147482647L % (N_DECKS * DECK_CARDS))

typedef struct s_bindings
{
	char	STAND;
	char	HIT;
	char	DOUBLE;
	char	SPLIT;
	char	HAND_1;
	char	HAND_2;
	char	HAND_3;
	char	HAND_4;
}	t_bindings;

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
	int				curr_hand;
	int				money;
	int				n_hands;
	int				last_bet;

	struct s_hand	hands[4];
}	t_player;

//display.c
void	display_cards(t_player *player, t_player *dealer);			//DISPLAYS CARDS and total for dealer and player(usually called each turn)
void	show_rules( void );

//game_start.c
void	reset_player(t_player *player);								//sets all values to default
int		new_deck(t_card *(*new_deck)[DECK_CARDS * N_DECKS]);		//creates a deck of n_cards = DECK_CARDS * N_DECKS
t_card	*new_card( int rank, int type );							//allocs and sets value for a t_card *
void	shuffle_deck(t_card *(*new_deck)[DECK_CARDS * N_DECKS]);	//swaps a deck's content <n_cards> times in ascending order with a random card
int		bet(t_player *player);										//ASKS the user for a bet amount, 0 < bet <= player.money

//game_turn.c
int		player_turn(t_player *player, t_card *(*deck)[DECK_CARDS * N_DECKS], t_player *dealer, t_bindings *bindings);//takes user input and applies it
void	dealer_turn(t_player *dealer, t_card *(*deck)[DECK_CARDS * N_DECKS], t_player *player);				  //draws till 17 total_value
void	deal_card(t_card *(*deck)[DECK_CARDS * N_DECKS], t_hand *hand, int amount);							  //takes a card from deck to hand <amount> times

//game_end.c
void	give_result(t_player *player, t_player *dealer);			//comparison between total sums, blackjack detection and distributes the money
void	free_cards(t_card *(*deck)[DECK_CARDS * N_DECKS], t_player *player, t_player *dealer); //frees cards in the deck and in all hands

//game_prep.c
int		get_bindings(t_bindings *bindings);		//reads from bindings.txt and sets t_binding struct
int		gen_seed( void );						//gens a seed by reading from /dev/random and calls srandom() with it
#endif
