#include "libft.h"
#include "pushswap.h"
#include <stdlib.h>

void	ft_initialise(t_list **lst, size_t *size, int **arr, t_chunk *chunk)
{
	int	i;

	i = 0;
	*arr = NULL;
	ft_memset(chunk, 0, sizeof(*chunk));
	ft_memset(size, 0, sizeof(*size) * 3);
	while (i < 5)
	{
		lst[i] = NULL;
		i++;
	}
}

int	ft_error_shutdown(t_list **lst, int **arr)
{
	free(*arr);
	ft_putstr_fd("Error\n", 2);
	ft_lstclear(&lst[0], NULL);
	ft_lstclear(&lst[1], NULL);
	ft_lstclear(&lst[2], &free);
	ft_lstclear(&lst[3], &free);
	ft_lstclear(&lst[4], &free);
	return (0);
}

int	ft_print_n_quit(t_list **lst, int **arr)
{
	ft_lstiter(lst[4], &ft_print_str_data);
	free(*arr);
	ft_lstclear(&lst[0], NULL);
	ft_lstclear(&lst[1], NULL);
	ft_lstclear(&lst[2], NULL);
	ft_lstclear(&lst[3], &free);
	ft_lstclear(&lst[4], &free);
	return (0);
}

int	ft_setup_next(t_list **lst, int **arr, size_t *size)
{
	ft_factorise_instruction(&lst[2]);
	ft_lstclear(&lst[0], NULL);
	if (!lst[4] || ft_lstsize(lst[2]) < ft_lstsize(lst[4]))
	{
		ft_lstclear(&lst[4], &free);
		lst[4] = ft_lstdup(lst[2], NULL);
		if (!lst[4])
			return (ft_error_shutdown(lst, arr));
		ft_lstclear(&lst[2], NULL);
	}
	else
		ft_lstclear(&lst[2], &free);
	ft_lstclear(&lst[0], NULL);
	lst[0] = ft_lstdup(lst[3], NULL);
	if (!lst[0])
		return (ft_error_shutdown(lst, arr));
	size[0] = size[2];
	size[1] = 0;
	return (1);
}

void	ft_setup_loop(size_t *size, t_chunk *chunk, int i)
{
	if (size[0] < 250)
		chunk->size = (int)(size[0]) / (5 + i);
	else
		chunk->size = (int)(size[0]) / (12 + i);
	chunk->size_origin = chunk->size;
	chunk->nb = (int)(size[2]) / chunk->size + (size[2] % chunk->size != 0);
	chunk->i = 1;
}
