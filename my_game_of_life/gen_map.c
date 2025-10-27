#include "./gol_defs.h"
#include "./my_libft/libft.h"
#include "./my_global_extern.h"
#include <fcntl.h>
#include <stdio.h>

/**********************/
/*hook/loop functions.*/
/**********************/
static void	print_gnl_list(t_dnode *node)
{
	printf("PRINTING_MAP\n");
	while (node)
	{
		printf("%s\n", (char *)node->data);
		node = node->next_node;
	}
	printf("\n");
}
static void	to_null(char *str)
{
	while(*str)
	{
		if (*str == '\n')
			*str = '\0';
		str++;
	}
}
static void	nl_to_nul(t_dnode *node)
{
	while (node)
	{
		to_null((char *)node->data);
		node = node->next_node;
	}
}
static int	count_nodes(t_dnode *node)
{
	int i = 0;
	while (node)
	{
		i++;
		node = node->next_node;
	}
	return (i);
}
static void	fill_map(t_dnode *node)
{
	/*get size from text.*/
	char	**empty_map = NULL;
	int	i = 0;
	map_width = ft_strlen((char *)node->data);
	map_height = count_nodes(node);
	win_width = map_width * PIX_SIZE;
	win_height = map_height * PIX_SIZE;

	empty_map = malloc(sizeof(char *) * (map_height + 1));
	empty_map[map_height] = NULL;

	while (i < map_height)
	{
		empty_map[i] = ft_strdup((char *)node->data);
		node = node->next_node;
		i++;
	}
	map = empty_map;
	print_splits(empty_map);
}
static void	read_pars_map(char *argv)
{
	t_dnode	*node;
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		exit(1);
	node = get_gnl_node(fd);
	node = node->next_node;
	destroy_doubly_node(find_head_dubly(node));
	destroy_doubly_node(find_tail_dubly(node));
	nl_to_nul(node);
	print_gnl_list(node);

	fill_map(node);

	node = node->next_node;
	destroy_doubly_list(node);
}

/*
 * If there's an argument when execute, main will gen map from file.
 * Don't mind other functions from this file.
 * Cuz only main function just need function below.
 */
void	gen_map( char *argv )
{
	read_pars_map(argv);
}
