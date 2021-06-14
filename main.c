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

int	ft_search_for_lowest(t_list *lst, int nb)
{
	int	lowest;
	int index;
	int	result;

	index = 1;
	result = 0;
	lowest = nb;
	while (lst)
	{
		if (nb > *(int *)(lst->content) && lowest > *(int *)(lst->content))
		{
			result = index;
			lowest = *(int *)(lst->content);
		}
		index++;
		lst = lst->next;
	}
	return (result);
}

void	ft_prepare_pb(t_list *lst[2], size_t size[2])
{
	int	index;

	index = ft_search_for_lowest(lst[0], *(int *)(lst[1]->content));
	if (index > (int)(size[0] / 2 + size[0] % 2))
	{
		index = (int)(size[0]) - index;
		while (index)
		{
			ft_reverse_rotate_a(lst);
			index--;
		}
	}
	else
	{
		while (index)
		{
			ft_rotate_a(lst);
			index--;
		}
	}
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
		ft_prepare_pb(lst, size);
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

int	main(int ac, char *av[])
{
	int		i;
	t_list	*lst[2];
	size_t	size[2];
	char	**tab;

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

	printf("list a :\n");
	ft_lstiter(lst[0], &ft_print_int_data);
	printf("list b :\n");
	ft_lstiter(lst[1], &ft_print_int_data);
	printf("list a's size : %zu\n", size[0]);
	printf("list b's size : %zu\n", size[1]);

	if (size[0] < 4)
	{
		ft_sort_three(lst, size);
		printf("\nafter the three sort:\n");
		printf("list a :\n");
		ft_lstiter(lst[0], &ft_print_int_data);
		printf("list b :\n");
		ft_lstiter(lst[1], &ft_print_int_data);
		printf("list a's size : %zu\n", size[0]);
		printf("list b's size : %zu\n", size[1]);
	}
	else if (size[0] < 6)
	{
		ft_sort_five(lst, size);
		printf("\nafter the three sort:\n");
		printf("list a :\n");
		ft_lstiter(lst[0], &ft_print_int_data);
		printf("list b :\n");
		ft_lstiter(lst[1], &ft_print_int_data);
		printf("list a's size : %zu\n", size[0]);
		printf("list b's size : %zu\n", size[1]);
	}
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

	ft_lstclear(&lst[0], &free);
	ft_lstclear(&lst[1], &free);
	return (0);
}
