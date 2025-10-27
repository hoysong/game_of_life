#include "./mlx_hdler.h"
#include "./gol_defs.h"
#include "./my_global_extern.h"
#include <stdio.h>

/**************/
/*image hdler.*/
/**************/
void	get_img_data(t_img *img)
{
	img->data_addr = mlx_get_data_addr(
			img->img_ptr,
			&(img->bits_per_pixel),
			&(img->size_line),
			&(img->endian));
}

void	put_pixel_to_img(t_img *img, int horiz, int vert, int color)
{
	char	*location_to_put;

	location_to_put = img->data_addr;
	*(unsigned int *)
		(
		location_to_put +
		((img->bits_per_pixel >> 3) * horiz) +
		img->size_line * vert
		) = color;
}

/***************/
/*bg_functions.*/
/***************/
static void	*thread_draw_bg( void *param )
{
	t_thread	*thread = param;
	int		width = 0;
	int		height = thread->img_chunk_start;
	int		height_end = thread->img_chunk_end;

	while (height < height_end)
	{
		while (width < win_width)
		{
			put_pixel_to_img(&bg_ptr, width, height, palette[palette_index][2]);
			width++;
		}
		width = 0;
		height++;
	}
}

/*send threads to function.*/
static void	draw_bg_color( void )
{
	int	i = 0;
	while (i < NUM_OF_THREADS)
	{
		pthread_create(&(thread_arr[i].thread_id), NULL, thread_draw_bg, &(thread_arr[i]));
		i++;
	}
}

//static void	draw_bg_color( void )
//{
//	int		width = 0;
//	int		height = 0;
//
//	while (height < win_height)
//	{
//		while (width < win_width)
//		{
//			put_pixel_to_img(&bg_ptr, width, height, palette[palette_index][2]);
//			width++;
//		}
//		width = 0;
//		height++;
//	}
//}

#include <unistd.h>
#include "./color_defs.h"
static void	*thread_draw_gl_2( void *param )
{
	t_thread	*thread = param;
	int		width = 0;
	int		height = PIX_SIZE * (thread->thread_num);
	int		height_end = win_height;

	width = PIX_SIZE * (thread->thread_num);
	height = 0;
	while (width < win_width)
	{
		while (height < win_height)
		{
			put_pixel_to_img(&bg_ptr, width, height, palette[palette_index][0]);
			height++;
		}
		height = 0;
		width += PIX_SIZE * NUM_OF_THREADS;
	}
}
static void	*thread_draw_gl( void *param )
{
	t_thread	*thread = param;
	int		width = 0;
	int		height = PIX_SIZE * (thread->thread_num);
	int		height_end = win_height;

	while (height < height_end)
	{
		while (width < win_width)
		{
			put_pixel_to_img(&bg_ptr, width, height, palette[palette_index][0]);
			width++;
		}
		width = 0;
		height += PIX_SIZE * NUM_OF_THREADS;
	}

//	width = PIX_SIZE * (thread->thread_num);
//	height = 0;
//	while (width < win_width)
//	{
//		while (height < win_height)
//		{
//			put_pixel_to_img(&bg_ptr, width, height, palette[palette_index][0]);
//			height++;
//		}
//		height = 0;
//		width += PIX_SIZE * NUM_OF_THREADS;
//	}
}

//static void 	draw_gridline( void )
//{
//	int	width = 0;
//	int	height = 0;
//	while (height < win_height)
//	{
//		while (width < win_width)
//		{
//			put_pixel_to_img(&bg_ptr, width, height, palette[palette_index][0]);
//			width++;
//		}
//		width = 0;
//		height += PIX_SIZE;
//	}
//	width = 0;
//	height = 0;
//	while (width < win_width)
//	{
//		while (height < win_height)
//		{
//			put_pixel_to_img(&bg_ptr, width, height, palette[palette_index][0]);
//			height++;
//		}
//		height = 0;
//		width += PIX_SIZE;
//	}
//}
//
static void	draw_gridline( void )
{
	int	i = 0;
	while (i < NUM_OF_THREADS)
	{
		pthread_create(&(thread_arr[i].thread_id), NULL, thread_draw_gl, &(thread_arr[i]));
		i++;
	}
}

static void	draw_gridline_2( void )
{
	int	i = 0;
	while (i < NUM_OF_THREADS)
	{
		pthread_create(&(thread_arr[i].thread_id), NULL, thread_draw_gl_2, &(thread_arr[i]));
		i++;
	}
}

static void fill_pixel( int width, int height )
{
	int	add_wid = 0;
	int	add_hei = 0;
	while (add_hei < PIX_SIZE)
	{
		while (add_wid < PIX_SIZE)
		{
			put_pixel_to_img(&bg_ptr, width + add_wid, height + add_hei, palette[palette_index][1]);
			add_wid++;
		}
		add_wid = 0;
		add_hei++;
	}
}

static void *thread_draw_pixel( void *param )
{
	t_thread	*thread = param;
	int		width = 0;
	int		height = thread->map_chunk_start;
	int		height_end = thread->map_chunk_end;

	while (height < height_end)
	{
		while (width < map_width)
		{
			if (map[height][width] >= '1' && map[height][width] <= '8')
				fill_pixel(width * PIX_SIZE, height * PIX_SIZE);
			width++;
		}
		width = 0;
		height++;
	}
}

//static void draw_pixel( void )
//{
//	int	width = 0;
//	int	height = 0;
//	while (height < map_height)
//	{
//		while (width < map_width)
//		{
//			if (map[height][width] == '1')
//			{
//				fill_pixel(width * PIX_SIZE, height * PIX_SIZE);
//			}
//			width++;
//		}
//		width = 0;
//		height++;
//	}
//}

static void	draw_pixel( void )
{
	int	i = 0;
	while (i < NUM_OF_THREADS)
	{
		pthread_create(&(thread_arr[i].thread_id), NULL, thread_draw_pixel, &(thread_arr[i]));
		i++;
	}
}


void wait_for_threads( void )
{
	int	i = 0;
	while (i < NUM_OF_THREADS)
	{
		pthread_join(thread_arr[i].thread_id, NULL);
		++i;
	}
}

void	fill_background( void )
{
	draw_bg_color();
	wait_for_threads();
	draw_gridline();
	wait_for_threads();
	draw_gridline_2();
	wait_for_threads();
	draw_pixel();
	wait_for_threads();
}

void	put_background(void)
{
	mlx_put_image_to_window(mlx_ptr, mlx_window, bg_ptr.img_ptr, 0, 0);
}
