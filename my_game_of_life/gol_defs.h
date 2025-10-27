#ifndef GOL_DEF_H
# define GOL_DEF_H

# define PIX_SIZE 5

/*threads will read map array and modify.*/
/*and also draw image..*/
# define NUM_OF_THREADS 8

# define STILL_ALIVE 'A'
# define GONNA_DIE 'D'
# define REVIVE 'R'

# include <pthread.h>

typedef struct s_thread
{
	/*basic info's.*/
	pthread_t	thread_id;
	int		thread_num;

	/*the chunk that this thread will handle.*/
	int		map_chunk_start;
	int		map_chunk_end;
	int		img_chunk_start;
	int		img_chunk_end;

	/*mutexes.*/
	pthread_mutex_t	personal_mtx;
	pthread_mutex_t	*next_mutex;
	pthread_mutex_t	*pub_mtx;
}	t_thread;

#endif
