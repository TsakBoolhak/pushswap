#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include "libft.h"
# include <stddef.h>

typedef struct s_chunk
{
	int	i;
	int	nb;
	int	size;
	int	size_origin;
}t_chunk;

/*
** instructions1.c
*/
int		ft_add_instruction(t_list **lst, char *str);
int		ft_swap_a(t_list **lst);
int		ft_swap_b(t_list **lst);
int		ft_push_a(t_list **lst, size_t *size);
int		ft_push_b(t_list **lst, size_t *size);

/*
** instructions2.c
*/
int		ft_rotate_a(t_list **lst);
int		ft_rotate_b(t_list **lst);
int		ft_reverse_rotate_a(t_list **lst);
int		ft_reverse_rotate_b(t_list **lst);
int		ft_check_sort_a(t_list **lst, size_t *size);

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
int		ft_pick_from_start(t_list *lst, int *arr, t_chunk chunk);
int		ft_pick_from_end(t_list *lst, int *arr, t_chunk chunk);

/*
** tools1.c
*/
int		ft_is_nb_valid(t_list **lst, char *str);
void	ft_print_str_data(void *data);
int		ft_prepare_pa(t_list **lst, size_t size[2]);
int		ft_prepare_pb(t_list **lst, size_t size[2]);
int		*ft_get_arr_from_list(t_list *lst, int size);

/*
** factorise_instructions.c
*/
void	ft_factorise_cancel_push(t_list **alst);
void	ft_replace_by_r(t_list **alst, t_list *lst, char *to_find);
void	ft_factorise_rotate(t_list **alst);
void	ft_delete_both(t_list **alst, t_list **lst, char *to_find);
void	ft_factorise_cancel_rotate(t_list **alst);

#endif
