#ifndef MY_GLOBAL_H
# define MY_GLOBAL_H
# include "./color_defs.h"
# include "./gol_defs.h"
# include "./mlx_hdler.h"
# include <pthread.h>

t_thread	thread_arr[NUM_OF_THREADS];
pthread_mutex_t		public_mutex;

int	palette[PALLETTE_COUNT][3] = {
		NORMAL,
		RETRO,
		GREEN,
		REEED,
		HORNET,
		SHADOW,
		CYAN,
		MIST,
		INVERT,
		PINK,
		COOL,
		REDMST
	};

int	palette_index;

char	**map;

int	map_width;
int	map_height;

int	win_width;
int	win_height;

void	*mlx_ptr;
void	*mlx_window;
t_img	bg_ptr;

#endif
