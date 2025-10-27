#include "./my_global_extern.h"
#include "./gol_defs.h"
#include <stdio.h>

void	set_threads()
{
	int i = NUM_OF_THREADS - 1;
	pthread_mutex_init(&public_mutex, NULL);
	while (i > -1)
	{
		thread_arr[i].thread_num = i;
		pthread_mutex_init(&(thread_arr[i].personal_mtx), NULL);

		/*set img bound that handle.*/
		thread_arr[i].img_chunk_start = (win_height / NUM_OF_THREADS) * i;
		if (i != NUM_OF_THREADS - 1)
			thread_arr[i].img_chunk_end = (win_height / NUM_OF_THREADS) * (i + 1);
		else
			thread_arr[i].img_chunk_end = win_height;

		/*set map bound that handle.*/
		thread_arr[i].map_chunk_start = (map_height / NUM_OF_THREADS) * i;
		if (i != NUM_OF_THREADS - 1)
			thread_arr[i].map_chunk_end = (map_height / NUM_OF_THREADS) * (i + 1);
		else
			thread_arr[i].map_chunk_end = map_height;

		/*init next mutex.*/
		if (i != NUM_OF_THREADS - 1)
			thread_arr[i].next_mutex = &(thread_arr[i + 1].personal_mtx);
		else
			thread_arr[i].next_mutex = &(thread_arr[0].personal_mtx);
		i--;
	}
}

void	print_init_status( void )
{
	printf("map_width  : %d\n", map_width);
	printf("map_height : %d\n", map_height);
	printf("win_width  : %d\n", win_width);
	printf("win_height : %d\n", win_height);
	printf("\n");
	printf("*****************\n");
	printf("Threads announce.\n");
	printf("*****************\n");

	int	i = 0;
	while (i < NUM_OF_THREADS)
	{
		printf("==== THREAD : %d ====\n", thread_arr[i].thread_num);
		printf("map_start: %d\n", thread_arr[i].map_chunk_start);
		printf("map_end  : %d\n", thread_arr[i].map_chunk_end);
		printf("img_start: %d\n", thread_arr[i].img_chunk_start);
		printf("img_end  : %d\n", thread_arr[i].img_chunk_end);
		printf("curr_mtx : %p\n", &(thread_arr[i].personal_mtx));
		printf("next_mtx : %p\n", thread_arr[i].next_mutex);
		i++;
	}
}
