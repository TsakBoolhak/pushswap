#include "libft.h"
#include "pushswap.h"
#include <stddef.h>

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
