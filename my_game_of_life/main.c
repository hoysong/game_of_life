#include "./gol_defs.h"
#include "./my_global.h"
#include "./my_libft/libft.h"
#include <unistd.h>
#include <stdio.h>

#include <sys/time.h>

long long	prog_start_time;

long long       get_call_time(void)
{
	struct timeval  s_time;
	
	gettimeofday(&s_time, NULL);
	return (s_time.tv_sec * 1000 + s_time.tv_usec / 1000);
}

void		map_modify( void );
static int	loop_function( void *param )
{
	static int frame_count;
	int	x;
	int	y;
	mlx_mouse_get_pos(mlx_ptr, mlx_window, &x, &y);
	if (x > 10 && x < win_width - 10 &&
		y > 10 && y < win_height - 10)
	{
		map[y / PIX_SIZE][x / PIX_SIZE] = '1';
		map[y / PIX_SIZE - 1][x / PIX_SIZE] = '1';
		map[y / PIX_SIZE + 1][x / PIX_SIZE] = '1';
		map[y / PIX_SIZE][x / PIX_SIZE - 1] = '1';
		map[y / PIX_SIZE][x / PIX_SIZE + 1] = '1';
	}
	fill_background();
	put_background();
	map_modify();
	usleep(1000 * 1);
//	if (frame_count++ > 120)
//	{
//		printf("%lld\n", get_call_time() - prog_start_time);
//		exit(0);
//	}
	return (0);
}

static int	destroy_win_hook( void *nothing )
{
	mlx_loop_end(mlx_ptr);
	return (0);
}

static void	delete( void )
{
	/*destroy image.*/
	mlx_destroy_image(mlx_ptr, bg_ptr.img_ptr);
	/*destroy win first*/
	mlx_destroy_window(mlx_ptr, mlx_window);
	/*destroy display(mlx_ptr).*/
	mlx_destroy_display(mlx_ptr);
	/*free mlx display pointer (mlx_ptr).*/
	free(mlx_ptr);
	/*free_map*/
	free_splits(map);
}

static int	key_hook_func(int input)
{
	if (input == XK_Escape)
		mlx_loop_end(mlx_ptr);
	else if (input == XK_Left)
	{
		if (palette_index > 0)
			palette_index--;
	}
	else if (input == XK_Right)
	{
		if (palette_index < PALLETTE_COUNT - 1)
			palette_index++;
	}
	return (0);
}

extern void	set_threads( void );
extern void	print_init_status( void );
extern void	no_arg_logic( void );
extern void	gen_map( char *argv );
int	main(int argc, char **argv)
{	
	if (argc == 1)
		no_arg_logic();
	else
		gen_map(argv[1]);
	palette_index = 0;
	mlx_ptr = mlx_init();
	set_threads();
	print_init_status();
	mlx_window = mlx_new_window( mlx_ptr, win_width, win_height, "Game_Of_Life" );
	mlx_hook( mlx_window, KeyPress, KeyPressMask, key_hook_func, NULL );
	mlx_hook( mlx_window, DestroyNotify, NoEventMask, destroy_win_hook, mlx_ptr );
	bg_ptr.img_ptr = mlx_new_image(mlx_ptr, win_width, win_height);
	get_img_data(&bg_ptr);
	prog_start_time = get_call_time();
	mlx_loop_hook(mlx_ptr, loop_function, NULL);
	mlx_loop( mlx_ptr );
	delete();
	return (0);
}
