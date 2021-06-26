#include "libft.h"
#include "pushswap.h"
#include <stdlib.h>
#include <limits.h>

int	ft_is_nb_valid(t_list **lst, char *str)
{
	long long	nbr;
	char		*end;
	int			*data;
	t_list		*new;

	if (!ft_isdigit(*str) && *str != '-')
		return (-1);
	nbr = ft_strtoll(str, &end);
	if (end == str || *end || nbr > INT_MAX || nbr < INT_MIN)
		return (-1);
	data = malloc(sizeof(*data));
	if (!data)
		return (-1);
	*data = (int)(nbr);
	new = ft_lstnew(data);
	if (ft_lstcontain_data(*lst, data, sizeof(*data), 1) || !new)
	{
		free(data);
		free(new);
		return (-1);
	}
	ft_lstadd_back(lst, new);
	return (0);
}

void	ft_print_str_data(void *data)
{
	ft_putendl_fd((char *)(data), 1);
}


int	ft_prepare_pa(t_list *lst[3], size_t size[2])
{
	int	index;


	index = ft_search_for_lowest(lst[0], *(int *)(lst[1]->content));
	if (index > (int)(size[0] / 2 + size[0] % 2))
	{
		index = (int)(size[0]) - index + 1;
		while (index)
		{
			if (ft_reverse_rotate_a(lst))
				return (1);
			index--;
		}
	}
	else
	{
		while (index > 1)
		{
			if (ft_rotate_a(lst))
				return (1);
			index--;
		}
	}
	return (0);
}

int	ft_prepare_pb(t_list *lst[3], size_t size[2])
{
	int	index;

	index = ft_search_for_highest(lst[1], *(int *)(lst[0]->content));
	if (index > (int)(size[1] / 2 + size[1] % 2))
	{
		index = (int)(size[1]) - index + 1;
		while (index > 0)
		{
			if (ft_reverse_rotate_b(lst))
				return (1);
			index--;
		}
	}
	else
	{
		while (index > 1)
		{
			if (ft_rotate_b(lst))
				return (1);
			index--;
		}
	}
	return (0);
}

int	ft_sort_three(t_list *lst[3], size_t size[2])
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

int	ft_sort_five(t_list *lst[3], size_t size[2])
{
	int	min;
	int	max;
	int	ret;

	ret = 0;
	if (ft_check_sort_a(lst, size))
		return (0);
	while (!ret && size[0] > 3)
		ret = ft_push_b(lst, size);
	if (ret || ft_sort_three(lst, size))
		return (1);
	while (size[1] && !ret && !ft_prepare_pa(lst, size))
		ret = ft_push_a(lst,size);
	if (ret || size[1])
		return (1);
	ft_search_minmax(lst[0], &min, &max);
	if (min > (int)(size[0] / 2 + size[0] % 2))
	{
		min = (int)(size[0] - min + 2);
		while (--min && !ret)
			ret = ft_reverse_rotate_a(lst);
	}
	else
	{
		while (--min && !ret)
			ret = ft_rotate_a(lst);
	}
	return (ret);
}


int	*ft_get_arr_from_list(t_list *lst, int size)
{
	int	*arr;
	int	i;

	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arr[i] = *(int *)(lst->content);
		lst = lst->next;
		i++;
	}
	ft_quicksort(arr, 0, size - 1);
	return (arr);
}


void	ft_factorise_cancel_push(t_list **alst)
{
	t_list	*lst;
	t_list	*tmp;

	if (!alst || !*alst)
		return ;
	lst = *alst;
	while (lst->next)
	{
		if (!ft_strcmp(lst->content, "pb"))
		{
			tmp = lst->next;
			while (tmp && (!ft_strcmp(tmp->content, "pa") || !ft_strcmp(tmp->content, "pb")))
			{
				if (!ft_strcmp(tmp->content, "pa"))
				{
					ft_lstdelone(alst, tmp, &free);
					tmp = lst;
					lst = lst->next;
					ft_lstdelone(alst, tmp, &free);
					break ;
				}
				tmp = tmp->next;
			}
		}
		lst = lst->next;
	}
}

void	ft_factorise_rotate(t_list **alst)
{
	t_list	*lst;
	t_list	*tmp;
	char	*str;

	if (!alst || !*alst)
		return ;
	lst = *alst;
	while (lst->next)
	{
		if (!ft_strcmp(lst->content, "ra"))
		{
			tmp = lst->next;
			while (tmp && ft_strcmp(tmp->content, "pa") && ft_strcmp(tmp->content, "pb") && ft_strcmp(tmp->content, "sa") && ft_strcmp(tmp->content, "sb"))
			{
				if (!ft_strcmp(tmp->content, "rb"))
				{
					ft_lstdelone(alst, tmp, &free);
					str = (char *)(lst->content);
					str[1] = 'r';
					break;
				}
				tmp = tmp->next;
			}
		}
		else if (!ft_strcmp(lst->content, "rb"))
		{
			tmp = lst->next;
			while (tmp && ft_strcmp(tmp->content, "pa") && ft_strcmp(tmp->content, "pb") && ft_strcmp(tmp->content, "sa") && ft_strcmp(tmp->content, "sb"))
			{
				if (!ft_strcmp(tmp->content, "ra"))
				{
					ft_lstdelone(alst, tmp, &free);
					str = (char *)(lst->content);
					str[1] = 'r';
					break;
				}
				tmp = tmp->next;
			}
		}
		else if (!ft_strcmp(lst->content, "rra"))
		{
			tmp = lst->next;
			while (tmp && ft_strcmp(tmp->content, "pa") && ft_strcmp(tmp->content, "pb") && ft_strcmp(tmp->content, "sa") && ft_strcmp(tmp->content, "sb"))
			{
				if (!ft_strcmp(tmp->content, "rrb"))
				{
					ft_lstdelone(alst, tmp, &free);
					str = (char *)(lst->content);
					str[2] = 'r';
					break;
				}
				tmp = tmp->next;
			}
		}
		else if (!ft_strcmp(lst->content, "rrb"))
		{
			tmp = lst->next;
			while (tmp && ft_strcmp(tmp->content, "pa") && ft_strcmp(tmp->content, "pb") && ft_strcmp(tmp->content, "sa") && ft_strcmp(tmp->content, "sb"))
			{
				if (!ft_strcmp(tmp->content, "rra"))
				{
					ft_lstdelone(alst, tmp, &free);
					str = (char *)(lst->content);
					str[2] = 'r';
					break;
				}
				tmp = tmp->next;
			}
		}
		lst = lst->next;
	}
}

void	ft_factorise_cancel_rotate(t_list **alst)
{
	t_list	*lst;
	t_list	*tmp;

	if (!alst || !*alst)
		return ;
	lst = *alst;
	while (lst->next)
	{
		if (!ft_strcmp(lst->content, "ra"))
		{
			tmp = lst->next;
			while (tmp && ft_strcmp(tmp->content, "pa") && ft_strcmp(tmp->content, "pb") && ft_strcmp(tmp->content, "sa") && ft_strcmp(tmp->content, "sb"))
			{
				if (!ft_strcmp(tmp->content, "rra"))
				{
					ft_lstdelone(alst, tmp, &free);
					tmp = lst;
					lst = lst->next;
					ft_lstdelone(alst, tmp, &free);
					break;
				}
				tmp = tmp->next;
			}
		}
		else if (!ft_strcmp(lst->content, "rb"))
		{
			tmp = lst->next;
			while (tmp && ft_strcmp(tmp->content, "pa") && ft_strcmp(tmp->content, "pb") && ft_strcmp(tmp->content, "sa") && ft_strcmp(tmp->content, "sb"))
			{
				if (!ft_strcmp(tmp->content, "rrb"))
				{
					ft_lstdelone(alst, tmp, &free);
					tmp = lst;
					lst = lst->next;
					ft_lstdelone(alst, tmp, &free);
					break;
				}
				tmp = tmp->next;
			}
		}
		lst = lst->next;
	}
}

void	ft_factorise_instruction(t_list **lst)
{
	ft_factorise_cancel_rotate(lst);
	ft_factorise_rotate(lst);
	ft_factorise_cancel_push(lst);
}

int	main(int ac, char *av[])
{
	int		i;
	t_list	*lst[3];
	t_list	*original_list;
	t_list	*best_instruction;
	size_t	size[2];
	char	**tab;
	int		*arr;
	int		arr_size;
	int		chunk_nb;
	int		chunk_i;
	int		chunk_size;
	int		chunk_size_origin;
	int		first_chosen;
	int		last_chosen;

	if (ac < 2)
		return (0);
	i = 1;
	arr = NULL;
	lst[0] = NULL;
	lst[1] = NULL;
	lst[2] = NULL;
	best_instruction = NULL;
	original_list = NULL;
	ft_memset(size, 0, sizeof(size));
	if (ac == 2)
	{
		tab = ft_split(av[1], ' ');
		if (!tab || !*tab)
		{
			ft_free_tab((void **)tab);
			ft_putstr_fd("Error\n", 2);
			return (0);
		}
		i = 0;
		while (tab[i])
		{
			if (ft_is_nb_valid(&lst[0], tab[i]))
			{
				ft_putstr_fd("Error\n", 2);
				ft_free_tab((void **)tab);
				ft_lstclear(&lst[0], &free);
				return (0);
			}
			i++;
		}
		ft_free_tab((void **)tab);
	}
	else
	{
		while (av[i])
		{
			if (ft_is_nb_valid(&lst[0], av[i]))
			{
				ft_putstr_fd("Error\n", 2);
				ft_lstclear(&lst[0], &free);
				return (0);
			}
			i++;
		}
	}
	size[0] = ft_lstsize(lst[0]);
	if (size[0] < 4)
	{
		if (ft_sort_three(lst, size))
		{
			ft_putstr_fd("Error: not enough memory\n", 2);
			ft_lstclear(&lst[0], &free);
			ft_lstclear(&lst[1], &free);
			ft_lstclear(&lst[2], &free);
			return (0);
		}
		ft_lstiter(lst[2], &ft_print_str_data);
		ft_lstclear(&lst[0], &free);
		ft_lstclear(&lst[2], &free);
		return (0);
	}
	else if (size[0] < 6)
	{
		if (ft_sort_five(lst, size))
		{
			ft_putstr_fd("Error: not enough memory\n", 2);
			ft_lstclear(&lst[0], &free);
			ft_lstclear(&lst[1], &free);
			ft_lstclear(&lst[2], &free);
			return (0);
		}
		ft_lstiter(lst[2], &ft_print_str_data);
		ft_lstclear(&lst[0], &free);
		ft_lstclear(&lst[2], &free);
		return (0);
	}
	else
	{
		arr_size = size[0];
		arr = ft_get_arr_from_list(lst[0], arr_size);
		if (!arr)
		{
			ft_putstr_fd("Error: not enough memory\n", 2);
			ft_lstclear(&lst[0], &free);
			return (0);
		}
		original_list = ft_lstdup(lst[0], NULL);
		if (!original_list)
		{
			ft_lstclear(&lst[0], &free);
			ft_putstr_fd("Error: not enough memory\n", 2);
			return (0);
		}
		i = 0;
		while (i < 5)
		{
			if (size[0] < 250)
				chunk_size = (int)(size[0]) / (5 + i) + ((int)(size[0]) / (5 + i) < 1);
			else
				chunk_size = size[0] / (12 + i);
			chunk_size_origin= chunk_size;
			chunk_nb = arr_size / chunk_size + (arr_size % chunk_size != 0);
			chunk_i = 1;
			while (chunk_i <= chunk_nb)
			{
				if (chunk_i == chunk_nb && arr_size % chunk_size)
					chunk_size = arr_size % chunk_size;
				first_chosen = ft_pick_from_start(lst[0], arr, chunk_i, chunk_size, chunk_size_origin);
				last_chosen = ft_pick_from_end(lst[0], arr, chunk_i, chunk_size, chunk_size_origin);
				if (first_chosen == 0)
				{
					chunk_i++;
					continue ;
				}
				last_chosen = size[0] - last_chosen + 1;
				first_chosen--;
				if (first_chosen <= last_chosen)
				{
					while (first_chosen)
					{
						if (ft_rotate_a(lst))
						{
							free(arr);
							ft_putstr_fd("Error: not enough memory\n", 2);
							ft_lstclear(&lst[0], &free);
							ft_lstclear(&lst[1], &free);
							ft_lstclear(&lst[2], &free);
							ft_lstclear(&original_list, &free);
							ft_lstclear(&best_instruction, &free);
							return (0);
						}
						first_chosen--;
					}
				}
				else
				{
					while (last_chosen)
					{
						if (ft_reverse_rotate_a(lst))
						{
							free(arr);
							ft_putstr_fd("Error: not enough memory\n", 2);
							ft_lstclear(&lst[0], &free);
							ft_lstclear(&lst[1], &free);
							ft_lstclear(&lst[2], &free);
							ft_lstclear(&original_list, &free);
							ft_lstclear(&best_instruction, &free);
							return (0);
						}
						last_chosen--;
					}
				}
				if (ft_prepare_pb(lst, size) || ft_push_b(lst,size))
				{
					ft_putstr_fd("Error: not enough memory\n", 2);
					free(arr);
					ft_lstclear(&lst[0], &free);
					ft_lstclear(&lst[1], &free);
					ft_lstclear(&lst[2], &free);
					ft_lstclear(&original_list, &free);
					ft_lstclear(&best_instruction, &free);
					return (0);
				}
			}
	

			ft_search_minmax(lst[1], &chunk_i, &chunk_nb);
			if (chunk_nb > (int)(size[1] / 2 + size[1] % 2))
			{
				chunk_nb = (int)(size[1] - chunk_nb + 2);
				while (--chunk_nb)
				{
					if (ft_reverse_rotate_b(lst))
					{
						free(arr);
						ft_putstr_fd("Error: not enough memory\n", 2);
						ft_lstclear(&lst[0], &free);
						ft_lstclear(&lst[1], &free);
						ft_lstclear(&lst[2], &free);
						ft_lstclear(&original_list, &free);
						ft_lstclear(&best_instruction, &free);
						return (0);
					}
				}
			}
			else
			{
				while (--chunk_nb)
				{
					if (ft_rotate_b(lst))
					{
						free(arr);
						ft_putstr_fd("Error: not enough memory\n", 2);
						ft_lstclear(&lst[0], &free);
						ft_lstclear(&lst[1], &free);
						ft_lstclear(&lst[2], &free);
						ft_lstclear(&original_list, &free);
						ft_lstclear(&best_instruction, &free);
						return (0);
					}
				}
			}
			while (size[1])
			{
				if (ft_push_a(lst, size))
				{
					free(arr);
					ft_putstr_fd("Error: not enough memory\n", 2);
					ft_lstclear(&lst[0], &free);
					ft_lstclear(&lst[1], &free);
					ft_lstclear(&lst[2], &free);
					ft_lstclear(&original_list, &free);
					ft_lstclear(&best_instruction, &free);
					return (0);
				}
			}
			ft_factorise_instruction(&lst[2]);
			ft_lstclear(&lst[0], NULL);
			if (!best_instruction || ft_lstsize(lst[2]) < ft_lstsize(best_instruction))
			{
				ft_lstclear(&best_instruction, &free);
				best_instruction = ft_lstdup(lst[2], NULL);
				if (!best_instruction)
				{
					free(arr);
					ft_putstr_fd("Error: not enough memory\n", 2);
					ft_lstclear(&lst[0], NULL);
					ft_lstclear(&lst[2], &free);
					ft_lstclear(&original_list, &free);
					return (0);
				}
				ft_lstclear(&lst[2], NULL);
			}
			else
				ft_lstclear(&lst[2], &free);
			ft_lstclear(&lst[0], NULL);
			lst[2] = NULL;
			lst[0] = ft_lstdup(original_list, NULL);
			if (!lst[0])
			{
				free(arr);
				ft_putstr_fd("Error: not enough memory\n", 2);
				ft_lstclear(&lst[1], &free);
				ft_lstclear(&original_list, &free);
				ft_lstclear(&best_instruction, &free);
				return (0);
			}
			size[0] = ft_lstsize(lst[0]);
			size[1] = 0;
			i++;
		}
	}
	ft_lstiter(best_instruction, &ft_print_str_data);
	free(arr);
	ft_lstclear(&lst[0], NULL);
	ft_lstclear(&lst[1], NULL);
	ft_lstclear(&original_list, &free);
	ft_lstclear(&best_instruction, &free);
	return (0);
}
