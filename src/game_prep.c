#include "blackjack.h"
#include <stdio.h>
#include <string.h>

int	gen_seed( void )
{
	char		seed[1];
	
	//seed gen (shuffle calls rand())
	int fd = open("/dev/random", O_RDONLY);
	if (fd < 0 || read(fd, seed, 1) < 0)
	{
		perror("problem attempting to read '/dev/random'");
		return (1);
	}
	close(fd);
	srandom(seed[0]);
	return (0);
}

int	get_bindings(t_bindings *bindings)
{
	char	buf[2048];
	char	*ptr;
	int		fd = open("bindings.txt", O_RDONLY);

	if (fd == -1 || read(fd, buf, 2047) < 0)
		return (1);
	buf[2047] = 0;

	ptr = strstr(buf, "SWITCH = '");
	if (!ptr)
		return (1);
	bindings->SWITCH = ptr[strlen("SWITCH = '")];
	ptr = strstr(buf, "STAND = '");
	if (!ptr)
		return (1);
	bindings->STAND = ptr[strlen("STAND = '")];
	ptr = strstr(buf, "HIT = '");
	if (!ptr)
		return (1);
	bindings->HIT = ptr[strlen("HIT = '")];
	ptr = strstr(buf, "SPLIT = '");
	if (!ptr)
		return (1);
	bindings->SPLIT = ptr[strlen("SPLIT = '")];
	ptr = strstr(buf, "DOUBLE = '");
	if (!ptr)
		return (1);
	bindings->DOUBLE = ptr[strlen("DOUBLE = '")];
	ptr = strstr(buf, "HAND 1 = '");
	if (!ptr)
		return (1);
	bindings->HAND_1 = ptr[strlen("HAND 1 = '")];
	ptr = strstr(buf, "HAND 2 = '");
	if (!ptr)
		return (1);
	bindings->HAND_2 = ptr[strlen("HAND 2 = '")];
	ptr = strstr(buf, "HAND 3 = '");
	if (!ptr)
		return (1);
	bindings->HAND_3 = ptr[strlen("HAND 3 = '")];
	ptr = strstr(buf, "HAND 4 = '");
	if (!ptr)
		return (1);
	bindings->HAND_4 = ptr[strlen("HAND 4 = '")];
	
	return (0);
}
