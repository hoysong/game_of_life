#include "./gol_defs.h"
#include "./my_global_extern.h"
/****************************************/
/*this file will get/set next map frame.*/
/****************************************/

static int	is_alive(char c)
{
	if (c == '1' || c == STILL_ALIVE || c == GONNA_DIE
//	if ((c >= '1' && c <= '8')
			|| c == GONNA_DIE)
		return (1);
	return (0);
}

static void surrounding_check_setup(int width, int height)
{
	int	count_alive = 0;

	int	min_wid = width - 1;
	int	plus_wid = width + 1;
	int	min_hei = height - 1;
	int	plus_hei = height + 1;

	if (width == 0)
		min_wid = map_width - 1;
	if (height == 0)
		min_hei = map_height - 1;
	if (width == map_width - 1)
		plus_wid = 0;
	if (height == map_height - 1)
		plus_hei = 0;

	if (is_alive(map[min_hei][min_wid]))
		count_alive++;
	if (is_alive(map[min_hei][width]))
	   count_alive++;
	if (is_alive(map[min_hei][plus_wid]))
	   count_alive++;
	if (is_alive(map[height][plus_wid]))
	   count_alive++;
	if (is_alive(map[plus_hei][plus_wid]))
	   count_alive++;
	if (is_alive(map[plus_hei][width]))
	   count_alive++;
	if (is_alive(map[plus_hei][min_wid]))
	   count_alive++;
	if (is_alive(map[height][min_wid]))
		count_alive++;

	if (map[height][width] == '0')
	{
		if (count_alive == 3)
			map[height][width] = REVIVE;
	}
	else if (map[height][width] == '1')
//	else if (map[height][width] <= '8' && map[height][width] >= '1')
	{
		if (count_alive == 3 || count_alive == 2)
			map[height][width] = STILL_ALIVE;
//			map[height][width]++;
		else
			map[height][width] = GONNA_DIE;
	}
}

static void map_normalize(char *c)
{
	if (*c == REVIVE || *c == STILL_ALIVE)
//	if (*c == REVIVE)
		*c = '1';
	else if (*c <= '8' && *c >= '1')
	{
	}
	else if (*c > '8')
		*c = '0';
	else
		*c = '0';
}

#include <unistd.h>
static void *thread_map_modify( void *param )
{
	t_thread	*thread = param;
	int	width = 0;
	int	height = thread->map_chunk_start;
	int	height_end = thread->map_chunk_end;
	while (height < height_end)
	{
		pthread_mutex_lock(thread->next_mutex);
		pthread_mutex_lock(&(thread->personal_mtx));
		while (width < map_width)
		{
			surrounding_check_setup(width, height);
			width++;
		}
		pthread_mutex_unlock(thread->next_mutex);
		pthread_mutex_unlock(&(thread->personal_mtx));
		width = 0;
		height++;
	}
	width = 0;
	height = thread->map_chunk_start;
	while (height < height_end)
	{
		pthread_mutex_lock(thread->next_mutex);
		pthread_mutex_lock(&(thread->personal_mtx));
		while (width < map_width)
		{
			map_normalize(&(map[height][width]));
			width++;
		}
		pthread_mutex_unlock(thread->next_mutex);
		pthread_mutex_unlock(&(thread->personal_mtx));
		width = 0;
		height++;
	}
}

/*before multi threading*/
void map_modify( void )
{
	int	width = 0;
	int	height = 0;
	while (height < map_height)
	{
		while (width < map_width)
		{
			surrounding_check_setup(width, height);
			width++;
		}
		width = 0;
		height++;
	}
	width = 0;
	height = 0;
	while (height < map_height)
	{
		while (width < map_width)
		{
			map_normalize(&(map[height][width]));
			width++;
		}
		width = 0;
		height++;
	}
}

/*multi threading*/
//extern void	wait_for_threads( void );
//void		map_modify( void )
//{
//	int	i = 0;
//	while (i < NUM_OF_THREADS)
//	{
//		pthread_create(&(thread_arr[i].thread_id), NULL, thread_map_modify, &(thread_arr[i]));
//		i++;
//	}
//	wait_for_threads();
//}
