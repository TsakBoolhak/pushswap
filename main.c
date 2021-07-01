#include "libft.h"
#include "pushswap.h"
#include <stdlib.h>
#include <limits.h>

int	ft_search_forbidden_spaces(const char *str)
{
	char	forbidden;
	char	forbidden_spaces[6];
	int		i;

	i = 0;
	forbidden = 9;
	while (i < 5)
	{
		forbidden_spaces[i] = forbidden;
		forbidden++;
		i++;
	}
	forbidden_spaces[i] = '\0';
	if (ft_strchr_charset(str, forbidden_spaces))
		return (1);
	return (0);
}

int	ft_sort_three(t_list **lst, size_t size[2])
{
	int	min;
	int	max;
	int	ret;

	ret = 0;
	if (ft_check_sort_a(lst, size))
		return (ret);
	ft_search_minmax(lst[0], &min, &max);
	if (size[0] == 3 && max == 2)
		ret = ft_reverse_rotate_a(lst);
	else if (size[0] == 3 && max == 1)
		ret = ft_rotate_a(lst);
	if (ret)
		return (ret);
	else if (!ft_check_sort_a(lst, size))
		ret = ft_swap_a(lst);
	return (ret);
}

int	ft_sort_five(t_list **lst, size_t size[2])
{
	int	minmax[2];
	int	ret;

	ret = 0;
	if (ft_check_sort_a(lst, size))
		return (0);
	while (!ret && size[0] > 3)
		ret = ft_push_b(lst, size);
	if (ret || ft_sort_three(lst, size))
		return (1);
	while (size[1] && !ret && !ft_prepare_pa(lst, size))
		ret = ft_push_a(lst, size);
	if (ret || size[1])
		return (1);
	ft_search_minmax(lst[0], minmax, minmax + 1);
	if (*minmax > (int)(size[0] / 2 + size[0] % 2))
	{
		*minmax = (int)(size[0] - *minmax + 2);
		while (--(*minmax) && !ret)
			ret = ft_reverse_rotate_a(lst);
		return (ret);
	}
	while (--(*minmax) && !ret)
		ret = ft_rotate_a(lst);
	return (ret);
}

void	ft_factorise_instruction(t_list **lst)
{
	ft_factorise_cancel_rotate(lst);
	ft_factorise_rotate(lst);
	ft_factorise_cancel_push(lst);
}

char	**ft_args_to_split(int ac, char **av)
{
	char	**tab[3];
	int		i;

	i = 0;
	tab[2] = NULL;
	while (++i < ac)
	{
		tab[0] = ft_split(av[i], ' ');
		if (!tab[0])
		{
			ft_free_tab((void *)tab[2]);
			return (NULL);
		}
		tab[1] = ft_splitjoin(tab[2], tab[0]);
		if (!tab[1])
		{
			ft_free_tab((void *)tab[2]);
			ft_free_tab((void *)tab[0]);
			return (NULL);
		}
		free(tab[2]);
		free(tab[0]);
		tab[2] = tab[1];
	}
	return (tab[2]);
}

int	ft_check_args(int ac, char **av, t_list **lst)
{
	int		i;
	char	**tab;

	tab = ft_args_to_split(ac, av);
	if (!tab)
		return (-1);
	i = 0;
	while (tab[i])
	{
		if (ft_is_nb_valid(&lst[0], tab[i]))
		{
			ft_free_tab((void **)tab);
			ft_lstclear(&lst[0], &free);
			return (-1);
		}
		i++;
	}
	ft_free_tab((void **)tab);
	return (0);
}

int	main(int ac, char *av[])
{
	int		i;
	t_list	*lst[5];
	size_t	size[3];
	int		*arr;
	t_chunk	chunk;

	i = 1;
	arr = NULL;
	lst[0] = NULL;
	lst[1] = NULL;
	lst[2] = NULL;
	lst[3] = NULL;
	lst[4] = NULL;
	ft_memset(size, 0, sizeof(size));
	ft_memset(&chunk, 0, sizeof(chunk));
	if (ac < 2)
		return (0);
	else if (ft_check_args(ac, av, lst))
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	size[0] = ft_lstsize(lst[0]);
	if (size[0] < 4)
	{
		if (ft_sort_three(lst, size))
		{
			ft_putstr_fd("Error\n", 2);
			ft_lstclear(&lst[0], &free);
			ft_lstclear(&lst[1], &free);
			ft_lstclear(&lst[2], &free);
			return (0);
		}
		ft_factorise_instruction(&lst[2]);
		ft_lstiter(lst[2], &ft_print_str_data);
		ft_lstclear(&lst[0], &free);
		ft_lstclear(&lst[2], &free);
		return (0);
	}
	else if (size[0] < 6)
	{
		if (ft_sort_five(lst, size))
		{
			ft_putstr_fd("Error\n", 2);
			ft_lstclear(&lst[0], &free);
			ft_lstclear(&lst[1], &free);
			ft_lstclear(&lst[2], &free);
			return (0);
		}
		ft_factorise_instruction(&lst[2]);
		ft_lstiter(lst[2], &ft_print_str_data);
		ft_lstclear(&lst[0], &free);
		ft_lstclear(&lst[2], &free);
		return (0);
	}
	else
	{
		if (ft_check_sort_a(lst, size))
		{
			ft_lstclear(&lst[0], &free);
			return (0);
		}
		size[2] = size[0];
		arr = ft_get_arr_from_list(lst[0], size[2]);
		if (!arr)
		{
			ft_putstr_fd("Error\n", 2);
			ft_lstclear(&lst[0], &free);
			return (0);
		}
		lst[3] = ft_lstdup(lst[0], NULL);
		if (!lst[3])
		{
			free(arr);
			ft_lstclear(&lst[0], &free);
			ft_putstr_fd("Error\n", 2);
			return (0);
		}
		i = 0;
		while (i < 5)
		{
			if (size[0] < 250)
				chunk.size = (int)(size[0]) / (5 + i) + ((int)(size[0]) / (5 + i) < 1);
			else
				chunk.size = (int)(size[0]) / (12 + i);
			chunk.size_origin = chunk.size;
			chunk.nb = (int)(size[2]) / chunk.size + ((int)(size[2]) % chunk.size != 0);
			chunk.i = 1;
			while (chunk.i <= chunk.nb)
			{
				if (chunk.i == chunk.nb && (int)(size[2]) % chunk.size)
					chunk.size = (int)(size[2]) % chunk.size;
				chunk.first_chosen = ft_pick_from_start(lst[0], arr, chunk);
				chunk.last_chosen = ft_pick_from_end(lst[0], arr, chunk);
				if (chunk.first_chosen == 0)
				{
					chunk.i++;
					continue ;
				}
				chunk.last_chosen = (int)(size[0]) - chunk.last_chosen + 1;
				chunk.first_chosen--;
				if (chunk.first_chosen <= chunk.last_chosen)
				{
					while (chunk.first_chosen)
					{
						if (ft_rotate_a(lst))
						{
							free(arr);
							ft_putstr_fd("Error\n", 2);
							ft_lstclear(&lst[0], NULL);
							ft_lstclear(&lst[1], NULL);
							ft_lstclear(&lst[2], &free);
							ft_lstclear(&lst[3], &free);
							ft_lstclear(&lst[4], &free);
							return (0);
						}
						chunk.first_chosen--;
					}
				}
				else
				{
					while (chunk.last_chosen)
					{
						if (ft_reverse_rotate_a(lst))
						{
							free(arr);
							ft_putstr_fd("Error\n", 2);
							ft_lstclear(&lst[0], NULL);
							ft_lstclear(&lst[1], NULL);
							ft_lstclear(&lst[2], &free);
							ft_lstclear(&lst[3], &free);
							ft_lstclear(&lst[4], &free);
							return (0);
						}
						chunk.last_chosen--;
					}
				}
				if (ft_prepare_pb(lst, size) || ft_push_b(lst, size))
				{
					ft_putstr_fd("Error\n", 2);
					free(arr);
					ft_lstclear(&lst[0], NULL);
					ft_lstclear(&lst[1], NULL);
					ft_lstclear(&lst[2], &free);
					ft_lstclear(&lst[3], &free);
					ft_lstclear(&lst[4], &free);
					return (0);
				}
			}
			ft_search_minmax(lst[1], &chunk.i, &chunk.nb);
			if (chunk.nb > (int)(size[1] / 2 + size[1] % 2))
			{
				chunk.nb = (int)(size[1] - chunk.nb + 2);
				while (--chunk.nb)
				{
					if (ft_reverse_rotate_b(lst))
					{
						free(arr);
						ft_putstr_fd("Error\n", 2);
						ft_lstclear(&lst[0], NULL);
						ft_lstclear(&lst[1], NULL);
						ft_lstclear(&lst[2], &free);
						ft_lstclear(&lst[3], &free);
						ft_lstclear(&lst[4], &free);
						return (0);
					}
				}
			}
			else
			{
				while (--chunk.nb)
				{
					if (ft_rotate_b(lst))
					{
						free(arr);
						ft_putstr_fd("Error\n", 2);
						ft_lstclear(&lst[0], NULL);
						ft_lstclear(&lst[1], NULL);
						ft_lstclear(&lst[2], &free);
						ft_lstclear(&lst[3], &free);
						ft_lstclear(&lst[4], &free);
						return (0);
					}
				}
			}
			while (size[1])
			{
				if (ft_push_a(lst, size))
				{
					free(arr);
					ft_putstr_fd("Error\n", 2);
					ft_lstclear(&lst[0], NULL);
					ft_lstclear(&lst[1], NULL);
					ft_lstclear(&lst[2], &free);
					ft_lstclear(&lst[3], &free);
					ft_lstclear(&lst[4], &free);
					return (0);
				}
			}
			ft_factorise_instruction(&lst[2]);
			ft_lstclear(&lst[0], NULL);
			if (!lst[4] || ft_lstsize(lst[2]) < ft_lstsize(lst[4]))
			{
				ft_lstclear(&lst[4], &free);
				lst[4] = ft_lstdup(lst[2], NULL);
				if (!lst[4])
				{
					free(arr);
					ft_putstr_fd("Error\n", 2);
					ft_lstclear(&lst[0], NULL);
					ft_lstclear(&lst[2], &free);
					ft_lstclear(&lst[3], &free);
					return (0);
				}
				ft_lstclear(&lst[2], NULL);
			}
			else
				ft_lstclear(&lst[2], &free);
			ft_lstclear(&lst[0], NULL);
			lst[2] = NULL;
			lst[0] = ft_lstdup(lst[3], NULL);
			if (!lst[0])
			{
				free(arr);
				ft_putstr_fd("Error\n", 2);
				ft_lstclear(&lst[3], &free);
				ft_lstclear(&lst[4], &free);
				return (0);
			}
			size[0] = size[2];
			size[1] = 0;
			i++;
		}
	}
	ft_lstiter(lst[4], &ft_print_str_data);
	free(arr);
	ft_lstclear(&lst[0], NULL);
	ft_lstclear(&lst[1], NULL);
	ft_lstclear(&lst[3], &free);
	ft_lstclear(&lst[4], &free);
	return (0);
}
