#ifndef MLX_HDLER_H
# define MLX_HDLER_H
# include "./minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_img
{
	char	*data_addr;
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		xpm_width;
	int		xpm_height;
}t_img;


void	get_img_data(t_img *img);
void	put_pixel_to_img(t_img *img, int horiz, int vert, int color);

/*this function fill draw background.*/
void	fill_background( void );
/*this function put background to display.*/
void	put_background(void);
#endif
