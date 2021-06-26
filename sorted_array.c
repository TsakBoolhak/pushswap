#include "libft.h"

void	ft_swap(int *a, int *b)
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
				break ;
			}
			start++;
		}
		i++;
		lst = lst->next;
	}
	return (ret);
}
