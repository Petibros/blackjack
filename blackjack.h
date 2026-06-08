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

void	deal_card(t_card *(*deck)[52], t_player *player, int amount);
void	display_cards(t_player *player, t_player *dealer, int dealer_reveal);//DISPLAYS CARDS and total for dealer and player(usually called each turn)
