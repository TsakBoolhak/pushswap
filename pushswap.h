#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include "libft.h"
# include <stddef.h>

/*
** instructions1.c
*/
int		ft_add_instruction(t_list *lst[3], char *str);
int		ft_swap_a(t_list *lst[3]);
int		ft_swap_b(t_list *lst[3]);
int		ft_push_a(t_list *lst[3], size_t size[2]);
int		ft_push_b(t_list *lst[3], size_t size[2]);

/*
** instructions2.c
*/
int		ft_rotate_a(t_list *lst[3]);
int		ft_rotate_b(t_list *lst[3]);
int		ft_reverse_rotate_a(t_list *lst[3]);
int		ft_reverse_rotate_b(t_list *lst[3]);
int		ft_check_sort_a(t_list *lst[3], size_t size[2]);

/*
** minmax.c
*/
void	ft_search_minmax(t_list *lst, int *min_pos, int *max_pos);
int		ft_get_max(t_list *lst, int *max_index);
int		ft_get_min(t_list *lst, int *min_index);
int		ft_search_for_lowest(t_list *lst, int nb);
int		ft_search_for_highest(t_list *lst, int nb);

/*
** sorted_array.c
*/
void	ft_swap(int *a, int *b);
int		ft_partition(int *arr, int first, int last, int pivot);
void	ft_quicksort(int *arr, int first, int last);
int		ft_pick_from_start(t_list *lst, int *arr, int chunk_i, int chunk_size, int chunk_size_origin);
int		ft_pick_from_end(t_list *lst, int *arr, int chunk_i, int chunk_size, int chunk_size_origin);

#endif
