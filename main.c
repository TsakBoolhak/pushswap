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

void	ft_swap_a(t_list *lst[2])
{
	t_list	*tmp;

	printf("sa\n");
	if (!(lst[0]) || !((lst[0])->next))
		return ;
	tmp = lst[0];
	lst[0] = (lst[0])->next;
	tmp->next = (lst[0])->next;
	(lst[0])->next = tmp;
}

void	ft_swap_b(t_list *lst[2])
{
	t_list	*tmp;

	printf("sb\n");
	if (!(lst[1]) || !((lst[1])->next))
		return ;
	tmp = lst[1];
	lst[1] = (lst[1])->next;
	tmp->next = (lst[1])->next;
	(lst[1])->next = tmp;
}

void	ft_swap_both(t_list *lst[2])
{
	printf("ss\n");
	ft_swap_a(lst);
	ft_swap_b(lst);
}

void	ft_push_a(t_list *lst[2], size_t size[2])
{
	t_list	*to_push;

	printf("pa\n");
	if (!lst[1])
		return ;
	to_push = lst[1];
	lst[1] = to_push->next;
	to_push->next = NULL;
	ft_lstadd_front(&lst[0], to_push);
	size[0]++;
	size[1]--;
}

void	ft_push_b(t_list *lst[2], size_t size[2])
{
	t_list	*to_push;

	printf("pb\n");
	if (!lst[0])
		return ;
	to_push = lst[0];
	lst[0] = to_push->next;
	to_push->next = NULL;
	ft_lstadd_front(&lst[1], to_push);
	size[1]++;
	size[0]--;
}

void	ft_rotate_a(t_list *lst[2])
{
	t_list	*tmp;
	t_list	*last;

	printf("ra\n");
	if (!(lst[0]) || !((lst[0])->next))
		return ;
	tmp = lst[0];
	last = ft_lstlast(tmp);
	lst[0] = tmp->next;
	tmp->next = NULL;
	last->next = tmp;
}

void	ft_rotate_b(t_list *lst[2])
{
	t_list	*tmp;
	t_list	*last;

	printf("rb\n");
	if (!(lst[1]) || !((lst[1])->next))
		return ;
	tmp = lst[1];
	last = ft_lstlast(tmp);
	lst[1] = tmp->next;
	tmp->next = NULL;
	last->next = tmp;
}

void	ft_rotate_both(t_list *lst[2])
{
	printf("rr\n");
	ft_rotate_a(lst);
	ft_rotate_b(lst);
}

void	ft_reverse_rotate_a(t_list *lst[2])
{
	t_list	*last;
	t_list	*tmp;

	printf("rra\n");
	if (!(lst[0]) || !((lst[0])->next))
		return ;
	tmp = lst[0];
	last = ft_lstlast(tmp);
	while (tmp->next != last)
		tmp = tmp->next;
	last->next = lst[0];
	lst[0] = last;
	tmp->next = NULL;
}

void	ft_reverse_rotate_b(t_list *lst[2])
{
	t_list	*last;
	t_list	*tmp;

	printf("rrb\n");
	if (!(lst[1]) || !((lst[1])->next))
		return ;
	tmp = lst[1];
	last = ft_lstlast(tmp);
	while (tmp->next != last)
		tmp = tmp->next;
	last->next = lst[1];
	lst[1] = last;
	tmp->next = NULL;
}

void	ft_reverse_rotate_both(t_list *lst[2])
{
	printf("rrr\n");
	ft_reverse_rotate_a(lst);
	ft_reverse_rotate_b(lst);
}

int	ft_check_sort_a(t_list *lst[2], size_t size[2])
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

	ret = *(int *)(lst->content);
	index = 1;
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
	while (lst)
	{
		if (*(int *)(lst->content) < ret)
		{
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
	lowest = ft_get_max(lst, &result);
	if (lowest > nb)
		lowest = ft_get_min(lst, &result); 
//	printf("nb to insert %d\n", nb);
//	printf("search lowest : lowest at start %d result %d\n", lowest, result);
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

	index = 1;
	highest = ft_get_min(lst, &result);
	if (highest > nb)
		highest = ft_get_max(lst, &result); 
//	printf("nb to insert %d\n", nb);
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
//	printf("search highet : highest at end %d result %d\n", highest, result);
	return (result);
}

void	ft_prepare_pa(t_list *lst[2], size_t size[2])
{
	int	index;


//	printf("prepare pa\n");
	index = ft_search_for_lowest(lst[0], *(int *)(lst[1]->content));
//	printf("index = %d\n", index);
	if (index > (int)(size[0] / 2 + size[0] % 2))
	{
		index = (int)(size[0]) - index;
//		printf("index = %d\n", index);
		while (index)
		{
			ft_reverse_rotate_a(lst);
			index--;
		}
	}
	else
	{
		while (index > 1)
		{
			ft_rotate_a(lst);
			index--;
		}
	}
//	printf("pa is preped\n");
}

void	ft_prepare_pb(t_list *lst[2], size_t size[2])
{
	int	index;

//	printf("prepare pb\n");
	index = ft_search_for_highest(lst[1], *(int *)(lst[0]->content));
//	printf("index = %d\n", index);
	if (index > (int)(size[1] / 2 + size[1] % 2))
	{
		index = (int)(size[1]) - index + 1;
		while (index > 0)
		{
//			printf("index = %d\n", index);
			ft_reverse_rotate_b(lst);
			index--;
		}
	}
	else
	{
		while (index > 1)
		{
			ft_rotate_b(lst);
			index--;
		}
	}
//	printf("pb is preped\n");
}

void	ft_sort_three(t_list *lst[2], size_t size[2])
{
	int	min;
	int	max;

	if (ft_check_sort_a(lst, size))
		return ;
	ft_search_minmax(lst[0], &min, &max);
	if (size[0] == 3 && max == 2)
		ft_reverse_rotate_a(lst);
	else if (size[0] == 3 && max == 1)
		ft_rotate_a(lst);
	if (!ft_check_sort_a(lst, size))
		ft_swap_a(lst);
}

void	ft_sort_five(t_list *lst[2], size_t size[2])
{
	int	min;
	int	max;

	if (ft_check_sort_a(lst, size))
		return ;
	while (size[0] > 3)
		ft_push_b(lst, size);
	ft_sort_three(lst, size);
	while (size[1])
	{
		ft_prepare_pa(lst, size);
		ft_push_a(lst,size);
	}
	ft_search_minmax(lst[0], &min, &max);
	if (min > (int)(size[0] / 2 + size[0] % 2))
	{
		min = (int)(size[0] - min + 2);
		while (--min)
			ft_reverse_rotate_a(lst);
	}
	else
	{
		while (--min)
			ft_rotate_a(lst);
	}
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

int	ft_pick_from_start(t_list *lst, int *arr, int chunk_i, int chunk_size)
{
	int	start;
	int	end;
	int	ret;

	start = ((chunk_i - 1) * chunk_size);
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

int	ft_pick_from_end(t_list *lst, int *arr, int chunk_i, int chunk_size)
{
	int	start;
	int	end;
	int	i;
	int	ret;

	start = ((chunk_i - 1) * chunk_size);
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
	t_list	*lst[2];
	size_t	size[2];
	char	**tab;
	int		*arr;
	int		arr_size;
	int		chunk_nb;
	int		chunk_i;
	int		chunk_size;
	int		first_chosen;
	int		last_chosen;

	if (ac < 2)
		return (0);
	i = 1;
	lst[0] = NULL;
	lst[1] = NULL;
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

	arr_size = size[0];
	arr = ft_get_arr_from_list(lst[0], arr_size);
	if (!arr)
	{
		ft_putstr_fd("Error: not enough memory\n", 2);
		ft_lstclear(&lst[0], &free);
		return (0);
	}
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
		ft_sort_three(lst, size);
	}
	else if (size[0] < 6)
	{
		ft_sort_five(lst, size);
	}
	else
	{
		chunk_size = size[0] / (size[0] / 25);
		chunk_nb = arr_size / chunk_size + (arr_size % chunk_size != 0);
		chunk_i = 1;
		while (chunk_i <= chunk_nb)
		{
			if (chunk_i == chunk_nb && arr_size % chunk_size)
				chunk_size = arr_size % chunk_size;
			first_chosen = ft_pick_from_start(lst[0], arr, chunk_i, chunk_size);
			last_chosen = ft_pick_from_end(lst[0], arr, chunk_i, chunk_size);
//			printf("first %d last %d chunk_i %d chunk_nb %d chunk_size %d\n", first_chosen, last_chosen, chunk_i, chunk_nb, chunk_size);
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
					ft_rotate_a(lst);
					first_chosen--;
				}
			}
			else
			{
				while (last_chosen)
				{
					ft_reverse_rotate_a(lst);
					last_chosen--;
				}
			}
			ft_prepare_pb(lst, size);
			ft_push_b(lst,size);
		}


//		printf("last move\n");
		ft_search_minmax(lst[1], &chunk_i, &chunk_nb);
		if (chunk_nb > (int)(size[1] / 2 + size[1] % 2))
		{
			chunk_nb = (int)(size[1] - chunk_nb + 2);
			while (--chunk_nb)
				ft_reverse_rotate_b(lst);
		}
		else
		{
			while (--chunk_nb)
				ft_rotate_b(lst);
		}
		while (size[1])
			ft_push_a(lst, size);
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

	free(arr);
	ft_lstclear(&lst[0], &free);
	ft_lstclear(&lst[1], &free);
	return (0);
}
