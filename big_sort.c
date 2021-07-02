#include "libft.h"
#include "pushswap.h"
#include <stddef.h>

int	ft_last_moves(t_list **lst, int **arr, size_t *size, t_chunk *chunk)
{
	ft_search_minmax(lst[1], &chunk->i, &chunk->nb);
	if (chunk->nb > (int)(size[1] / 2 + size[1] % 2))
	{
		chunk->nb = (int)(size[1] - chunk->nb + 2);
		while (--chunk->nb)
		{
			if (ft_reverse_rotate_b(lst))
				return (ft_error_shutdown(lst, arr));
		}
	}
	else
	{
		while (--chunk->nb)
		{
			if (ft_rotate_b(lst))
				return (ft_error_shutdown(lst, arr));
		}
	}
	while (size[1])
	{
		if (ft_push_a(lst, size))
			return (ft_error_shutdown(lst, arr));
	}
	return (1);
}

int	ft_pick_and_push(t_list **lst, int **arr, size_t *size, t_chunk *chunk)
{
	chunk->last_chosen = (int)(size[0]) - chunk->last_chosen + 1;
	chunk->first_chosen--;
	if (chunk->first_chosen <= chunk->last_chosen)
	{
		while (chunk->first_chosen)
		{
			if (ft_rotate_a(lst))
				return (ft_error_shutdown(lst, arr));
			chunk->first_chosen--;
		}
	}
	else
	{
		while (chunk->last_chosen)
		{
			if (ft_reverse_rotate_a(lst))
				return (ft_error_shutdown(lst, arr));
			chunk->last_chosen--;
		}
	}
	if (ft_prepare_pb(lst, size) || ft_push_b(lst, size))
		return (ft_error_shutdown(lst, arr));
	return (1);
}

int	ft_main_loop(t_list **lst, int **arr, size_t *size, t_chunk *chunk)
{
	int	i;

	i = -1;
	while (++i < 5)
	{
		ft_setup_loop(size, chunk, i);
		while (chunk->i <= chunk->nb)
		{
			if (chunk->i == chunk->nb && (int)(size[2]) % chunk->size)
				chunk->size = (int)(size[2]) % chunk->size;
			chunk->first_chosen = ft_pick_from_start(lst[0], *arr, *chunk);
			chunk->last_chosen = ft_pick_from_end(lst[0], *arr, *chunk);
			if (chunk->first_chosen == 0)
			{
				chunk->i++;
				continue ;
			}
			if (!ft_pick_and_push(lst, arr, size, chunk))
				return (0);
		}
		if (!ft_last_moves(lst, arr, size, chunk)
			|| !ft_setup_next(lst, arr, size))
			return (0);
	}
	return (1);
}
