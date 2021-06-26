#include "libft.h"

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
	int	ret;
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
	int	ret;
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
	int	index;
	int	result;

	index = 1;
	result = 0;
	lowest = ft_get_max(lst, &result);
	if (lowest < nb)
	{
		lowest = ft_get_min(lst, &result);
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
	return (result);
}

int	ft_search_for_highest(t_list *lst, int nb)
{
	int	highest;
	int	index;
	int	result;

	result = 1;
	index = 1;
	highest = ft_get_min(lst, &result);
	if (highest > nb)
		highest = ft_get_max(lst, &result);
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
	return (result);
}
