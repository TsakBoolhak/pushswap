#include "libft.h"
#include "pushswap.h"
#include <stdlib.h>

int	ft_sort_three(t_list **lst, size_t *size)
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

int	ft_sort_short(t_list **lst, size_t *size)
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

int	ft_pswap_core(t_list **lst, size_t *size, int **arr, t_chunk *chunk)
{
	if (size[0] < 10)
	{
		lst[3] = ft_lstdup(lst[0], NULL);
		if (!lst[3] || ft_sort_short(lst, size))
			return (ft_error_shutdown(lst, arr));
		ft_factorise_instruction(&lst[2]);
		lst[4] = ft_lstdup(lst[2], NULL);
		if (!lst[4])
			return (ft_error_shutdown(lst, arr));
	}
	else
	{
		if (ft_check_sort_a(lst, size))
		{
			ft_lstclear(&lst[0], &free);
			return (0);
		}
		lst[3] = ft_lstdup(lst[0], NULL);
		*arr = ft_get_arr_from_list(lst[0], size[2]);
		if (!lst[3] || !*arr)
			return (ft_error_shutdown(lst, arr));
		if (!ft_main_loop(lst, arr, size, chunk))
			return (0);
	}
	return (1);
}
