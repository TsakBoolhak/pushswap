#include "libft.h"
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

#include <stdio.h>

void	ft_print_int_data(void *data)
{
	printf("%d\n", *(int *)data);
}

void	ft_print_str_data(void *data)
{
	ft_putendl_fd((char *)(data), 1);
}

int	ft_add_instruction(t_list *lst[3], char *str)
{
	char	*copy;
	t_list	*new_node;

	copy = ft_strdup(str);
	new_node = ft_lstnew(copy);
	if (!copy || !new_node)
	{
		free(copy);
		return (1);
	}
	ft_lstadd_back(&lst[2], new_node);
	return (0);
}

int	ft_swap_a(t_list *lst[3])
{
	t_list	*tmp;

	if (ft_add_instruction(lst, "sa"))
		return (1);
	if (!(lst[0]) || !((lst[0])->next))
		return (0);
	tmp = lst[0];
	lst[0] = (lst[0])->next;
	tmp->next = (lst[0])->next;
	(lst[0])->next = tmp;
	return (0);
}

int	ft_swap_b(t_list *lst[3])
{
	t_list	*tmp;

	if (ft_add_instruction(lst, "sb"))
		return (1);
	if (!(lst[1]) || !((lst[1])->next))
		return (0);
	tmp = lst[1];
	lst[1] = (lst[1])->next;
	tmp->next = (lst[1])->next;
	(lst[1])->next = tmp;
	return (0);
}

int	ft_swap_both(t_list *lst[3])
{
	if(ft_add_instruction(lst, "ss") || ft_swap_a(lst) || ft_swap_b(lst))
		return (1);
	return (0);
}

int	ft_push_a(t_list *lst[3], size_t size[2])
{
	t_list	*to_push;

	if (ft_add_instruction(lst, "pa"))
		return (1);
	if (!lst[1])
		return (0);
	to_push = lst[1];
	lst[1] = to_push->next;
	to_push->next = NULL;
	ft_lstadd_front(&lst[0], to_push);
	size[0]++;
	size[1]--;
	return (0);
}

int	ft_push_b(t_list *lst[3], size_t size[2])
{
	t_list	*to_push;

	if (ft_add_instruction(lst, "pb"))
		return (1);
	if (!lst[0])
		return (0);
	to_push = lst[0];
	lst[0] = to_push->next;
	to_push->next = NULL;
	ft_lstadd_front(&lst[1], to_push);
	size[1]++;
	size[0]--;
	return (0);
}

int	ft_rotate_a(t_list *lst[3])
{
	t_list	*tmp;
	t_list	*last;

	if (ft_add_instruction(lst, "ra"))
		return (1);
	if (!(lst[0]) || !((lst[0])->next))
		return (0);
	tmp = lst[0];
	last = ft_lstlast(tmp);
	lst[0] = tmp->next;
	tmp->next = NULL;
	last->next = tmp;
	return (0);
}

int	ft_rotate_b(t_list *lst[3])
{
	t_list	*tmp;
	t_list	*last;

	if (ft_add_instruction(lst, "rb"))
		return (1);
	if (!(lst[1]) || !((lst[1])->next))
		return (0);
	tmp = lst[1];
	last = ft_lstlast(tmp);
	lst[1] = tmp->next;
	tmp->next = NULL;
	last->next = tmp;
	return (0);
}

int	ft_rotate_both(t_list *lst[3])
{
	if (ft_add_instruction(lst, "rr") || ft_rotate_a(lst) || ft_rotate_b(lst))
		return (1);
	return (0);
}

int	ft_reverse_rotate_a(t_list *lst[3])
{
	t_list	*last;
	t_list	*tmp;

	if (ft_add_instruction(lst, "rra"))
		return (1);
	if (!(lst[0]) || !((lst[0])->next))
		return (0);
	tmp = lst[0];
	last = ft_lstlast(tmp);
	while (tmp->next != last)
		tmp = tmp->next;
	last->next = lst[0];
	lst[0] = last;
	tmp->next = NULL;
	return (0);
}

int	ft_reverse_rotate_b(t_list *lst[3])
{
	t_list	*last;
	t_list	*tmp;

	if (ft_add_instruction(lst, "rrb"))
		return (1);
	if (!(lst[1]) || !((lst[1])->next))
		return (0);
	tmp = lst[1];
	last = ft_lstlast(tmp);
	while (tmp->next != last)
		tmp = tmp->next;
	last->next = lst[1];
	lst[1] = last;
	tmp->next = NULL;
	return (0);
}

int	ft_reverse_rotate_both(t_list *lst[2])
{
	if (ft_add_instruction(lst, "rrr") || ft_reverse_rotate_a(lst))
		return (1);
	else if (ft_reverse_rotate_b(lst))
		return (1);
	return (0);
}

int	ft_check_sort_a(t_list *lst[3], size_t size[2])
{
	int		nb;
	t_list	*tmp;

	if (size[0] < 2)
		return (1);
	nb = *(int *)(lst[0]->content);
	tmp = lst[0]->next;
	while (tmp)
	{
		if (nb > *(int *)(tmp->content))
			return (0);
		nb = *(int *)(tmp->content);
		tmp = tmp->next;
	}
	return (1);
}

void	ft_search_minmax(t_list *lst, int *min_pos, int *max_pos)
{
	int	minmax[2];
	int	index;

	if (!lst)
		return ;
	index = 1;
	minmax[0] = *(int *)(lst->content);
	minmax[1] = minmax[0];
	*min_pos = 1;
	*max_pos = 1;
	while (lst)
	{
		if (minmax[0] > *(int *)(lst->content))
		{
			minmax[0] = *(int *)(lst->content);
			*min_pos = index;
		}
		else if (minmax[1] < *(int *)(lst->content))
		{
			minmax[1] = *(int *)(lst->content);
			*max_pos = index;
		}
		index++;
		lst = lst->next;
	}
}

int	ft_get_max(t_list *lst, int *max_index)
{
	int ret;
	int	index;

	ret = 0;
	if (lst)
		ret = *(int *)(lst->content);
	index = 1;
	*max_index = 1;
	while (lst)
	{
		if (*(int *)(lst->content) > ret)
		{
			ret = *(int *)(lst->content);
			*max_index = index;
		}
		lst = lst->next;
		index++;
	}
	return (ret);
}

int	ft_get_min(t_list *lst, int *min_index)
{
	int ret;
	int	index;

	ret = 0;
	if (lst)
		ret = *(int *)(lst->content);
	index = 1;
	*min_index = 1;
	while (lst)
	{
		if (*(int *)(lst->content) < ret)
		{
//			printf("index = %d ret = %d content = %d\n", index, ret, *(int*)(lst->content));
			ret = *(int *)(lst->content);
			*min_index = index;
		}
		lst = lst->next;
		index++;
	}
	return (ret);
}

int	ft_search_for_lowest(t_list *lst, int nb)
{
	int	lowest;
	int index;
	int	result;

	index = 1;
	result = 0;
//	printf("nb to insert %d\n", nb);
	lowest = ft_get_max(lst, &result);
//	printf("search lowest : lowest at start %d result %d\n", lowest, result);
	if (lowest < nb)
	{
		lowest = ft_get_min(lst, &result); 
//		printf("search lowest : lowest at end %d result %d\n", lowest, result);
		return (result);
	}
	while (lst)
	{
		if (nb < *(int *)(lst->content) && lowest > *(int *)(lst->content))
		{
			result = index;
			lowest = *(int *)(lst->content);
		}
		index++;
		lst = lst->next;
	}
//	printf("search lowest : lowest at end %d result %d\n", lowest, result);
	return (result);
}

int	ft_search_for_highest(t_list *lst, int nb)
{
	int	highest;
	int index;
	int	result;

//	printf("nb to insert %d\n", nb);
	result = 1;
	index = 1;
	highest = ft_get_min(lst, &result);
//	printf("highest = %d, nb = %d\n", highest, nb);
	if (highest > nb)
//	{
		highest = ft_get_max(lst, &result); 
//	}
//	printf("search lowest : highest at start %d result %d\n", highest, result);
	while (lst)
	{
		if (nb > *(int *)(lst->content) && highest < *(int *)(lst->content))
		{
			result = index;
			highest = *(int *)(lst->content);
		}
		index++;
		lst = lst->next;
	}
//	printf("search highest : highest at end %d result %d\n", highest, result);
	return (result);
}

int	ft_prepare_pa(t_list *lst[3], size_t size[2])
{
	int	index;


//	printf("prepare pa\n");
	index = ft_search_for_lowest(lst[0], *(int *)(lst[1]->content));
//	printf("index = %d\n", index);
	if (index > (int)(size[0] / 2 + size[0] % 2))
	{
		index = (int)(size[0]) - index + 1;
//		printf("index = %d\n", index);
		while (index)
		{
//			printf("rra\n");
			if (ft_reverse_rotate_a(lst))
				return (1);
			index--;
		}
	}
	else
	{
		while (index > 1)
		{
//			printf("ra\n");
			if (ft_rotate_a(lst))
				return (1);
			index--;
		}
	}
//	printf("pa is preped\n");
	return (0);
}

int	ft_prepare_pb(t_list *lst[3], size_t size[2])
{
	int	index;

//	printf("prepare pb\n");
	index = ft_search_for_highest(lst[1], *(int *)(lst[0]->content));
//	printf("index = %d\n", index);
	if (index > (int)(size[1] / 2 + size[1] % 2))
	{
		index = (int)(size[1]) - index + 1;
//		printf("index = %d\n", index);
		while (index > 0)
		{
//			printf("rra\n");
			if (ft_reverse_rotate_b(lst))
				return (1);
			index--;
		}
	}
	else
	{
		while (index > 1)
		{
//			printf("ra\n");
			if (ft_rotate_b(lst))
				return (1);
			index--;
		}
	}
//	printf("pb is preped\n");
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

void ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_partition(int *arr, int first, int last, int pivot)
{
	int	i;
	int	j;

	ft_swap(arr + pivot, arr + last);
	i = first;
	j = i;
	while (i < last)
	{
		if (arr[i] <= arr[last])
		{
			ft_swap(arr + i, arr + j);
			j++;
		}
		i++;
	}
	ft_swap(arr + last, arr + j);
	return (j);
}

void	ft_quicksort(int *arr, int first, int last)
{
	int	pivot;

	if (first < last)
	{
		pivot = last;
		pivot = ft_partition(arr, first, last, pivot);
		ft_quicksort(arr, first, pivot - 1);
		ft_quicksort(arr, pivot + 1, last);
	}
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

void	ft_print_array(int *arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("arr[%d] = %d\n", i, arr[i]);
		i++;
	}
}

int	ft_pick_from_start(t_list *lst, int *arr, int chunk_i, int chunk_size, int chunk_size_origin)
{
	int	start;
	int	end;
	int	ret;

	start = ((chunk_i - 1) * chunk_size_origin);
	end = start + chunk_size;
	ret = 1;
	while (lst)
	{
		start = ((chunk_i - 1) * chunk_size);
		while (start < end)
		{
			if (arr[start] == *(int *)(lst->content))
				return (ret);
			start++;
		}
		ret++;
		lst = lst->next;
	}
	return (0);
}

int	ft_pick_from_end(t_list *lst, int *arr, int chunk_i, int chunk_size, int chunk_size_origin)
{
	int	start;
	int	end;
	int	i;
	int	ret;

	start = ((chunk_i - 1) * chunk_size_origin);
	end = start + chunk_size;
	ret = 0;
	i = 1;
	while (lst)
	{
		start = ((chunk_i - 1) * chunk_size);
		while (start < end)
		{
			if (arr[start] == *(int *)(lst->content))
			{
				ret = i;
				break;
			}
			start++;
		}
		i++;
		lst = lst->next;
	}
	return (ret);
}

int	main(int ac, char *av[])
{
	int		i;
	t_list	*lst[3];
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

//	ft_print_array(arr, arr_size);


//	printf("\n");
//	printf("list a :\n");
//	ft_lstiter(lst[0], &ft_print_int_data);
//	printf("list b :\n");
//	ft_lstiter(lst[1], &ft_print_int_data);
//	printf("list a's size : %zu\n", size[0]);
//	printf("list b's size : %zu\n", size[1]);

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
		if (size[0] < 250)
			chunk_size = (int)(size[0]) / 7 + ((int)(size[0]) / 7 < 1);
		else
			chunk_size = size[0] / 14;
		chunk_size_origin= chunk_size;
		chunk_nb = arr_size / chunk_size + (arr_size % chunk_size != 0);
//		printf("size[0] = %zu, chunk_nb = %d chunk_size = %d(at begin)\n", size[0], chunk_nb, chunk_size);
		chunk_i = 1;
		while (chunk_i <= chunk_nb)
		{
			if (chunk_i == chunk_nb && arr_size % chunk_size)
				chunk_size = arr_size % chunk_size;
			first_chosen = ft_pick_from_start(lst[0], arr, chunk_i, chunk_size, chunk_size_origin);
			last_chosen = ft_pick_from_end(lst[0], arr, chunk_i, chunk_size, chunk_size_origin);
//			printf("first %d last %d chunk_i %d chunk_nb %d chunk_size %d\n", first_chosen, last_chosen, chunk_i, chunk_nb, chunk_size);
			if (first_chosen == 0)
			{
//				printf("when passing to next chun_i : chunk_i = %d, chunk_size = %d, size[0] = %zu\n", chunk_i, chunk_size, size[0]);
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
				return (0);
			}
		}


//		printf("size[0] = %zu, chunk_size = %d\n", size[0], chunk_size);
//		printf("last move\n");
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
				return (0);
			}
		}
	}
//	printf("\nafter the sort:\n");
//	printf("list a :\n");
//	ft_lstiter(lst[0], &ft_print_int_data);
//	printf("list b :\n");
//	ft_lstiter(lst[1], &ft_print_int_data);
//	printf("list a's size : %zu\n", size[0]);
//	printf("list b's size : %zu\n", size[1]);
	/*
	printf("\nlet's test swap_a :\n");
	ft_swap_a(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test push_b :\n");
	ft_push_b(lst, size);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test push_b :\n");
	ft_push_b(lst, size);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test swap_b :\n");
	ft_swap_b(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test swap_both :\n");
	ft_swap_both(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test push_a :\n");
	ft_push_a(lst, size);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test rotate_a :\n");
	ft_rotate_a(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test reverse_rotate_a :\n");
	ft_reverse_rotate_a(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test push_b :\n");
	ft_push_b(lst, size);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test push_b :\n");
	ft_push_b(lst, size);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test rotate_b :\n");
	ft_rotate_b(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test reverse_rotate_b :\n");
	ft_reverse_rotate_b(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test rotate_both :\n");
	ft_rotate_both(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test reverse_rotate_both :\n");
	ft_reverse_rotate_both(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test push_a :\n");
	ft_push_a(lst, size);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test push_a :\n");
	ft_push_a(lst, size);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test rotate_b :\n");
	ft_rotate_b(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test reverse_rotate_b :\n");
	ft_reverse_rotate_b(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test push_a :\n");
	ft_push_a(lst, size);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test rotate_b :\n");
	ft_rotate_b(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test reverse_rotate_b :\n");
	ft_reverse_rotate_b(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test push_a :\n");
	ft_push_a(lst, size);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test push_a :\n");
	ft_push_a(lst, size);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test rotate_b :\n");
	ft_rotate_b(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	printf("\nlet's test reverse_rotate_b :\n");
	ft_reverse_rotate_b(lst);
	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);
	*/

//	printf("Before factoring the instructions list :\n");
//	ft_lstiter(lst[2], &ft_print_str_data);
//	printf("After factoring the instructions list :\n");
//	ft_factorise_instruction(&lst[2]);
	ft_lstiter(lst[2], &ft_print_str_data);
	free(arr);
	ft_lstclear(&lst[0], &free);
	ft_lstclear(&lst[1], &free);
	ft_lstclear(&lst[2], &free);
	return (0);
}
