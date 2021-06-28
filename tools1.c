#include "libft.h"
#include "pushswap.h"
#include <limits.h>
#include <stdlib.h>

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

int	ft_prepare_pa(t_list **lst, size_t size[2])
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

int	ft_prepare_pb(t_list **lst, size_t size[2])
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
