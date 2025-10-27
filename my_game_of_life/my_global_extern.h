#ifndef MY_GLOBAL_EXTERN_H
# define MY_GLOBAL_EXTERN_H
# include "./gol_defs.h"
# include "./color_defs.h"
# include "./mlx_hdler.h"
# include <pthread.h>

typedef struct s_thread	t_thread;
extern t_thread		thread_arr[NUM_OF_THREADS];
extern pthread_mutex_t	public_mutex;

extern int	palette[PALLETTE_COUNT][3];

extern int	palette_index;

extern char	**map;

extern int	map_width;
extern int	map_height;
 
extern int	win_width;
extern int	win_height;
 
extern void	*mlx_ptr;
extern void	*mlx_window;
extern t_img	bg_ptr;

#endif
