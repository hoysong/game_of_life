#include "gol_defs.h"
#include "my_global_extern.h"
#include <stdlib.h>
#include <time.h>

/****************/
/*no arg logics.*/
/****************/
static void	no_arg_map_gen( void )
{
	int	i = 0;
	map_width = 1920 / PIX_SIZE;
	map_height = 1000 / PIX_SIZE;
	win_width = map_width * PIX_SIZE;
	win_height = map_height * PIX_SIZE;
	map = malloc(sizeof(char *) * (map_height + 1));
	map[map_height] = NULL;
	while (i < map_height)
	{
		map[i] = malloc(sizeof(char) * (map_width + 1));
		i++;
	}
}
static void	fill_one_line( char *str )
{
	int	i = 0;
	while (i < map_width)
	{
		if (rand() % 9 <= 0)
			str[i] = '1';
		else
			str[i] = '0';
		i++;
	}
	str[i] = '\0';
}
void	no_arg_logic( void )
{
	int	i = 0;
	int	random;
	no_arg_map_gen();
	srand(time(NULL));
	while (i < map_height)
	{
		fill_one_line(map[i]);
		i++;
	}
}
