#include "libft.h"
#include "pushswap.h"
#include <stdlib.h>
#include <stddef.h>

int	ft_add_instruction(t_list **lst, char *str)
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

int	ft_swap_a(t_list **lst)
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

int	ft_swap_b(t_list **lst)
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

int	ft_push_a(t_list **lst, size_t *size)
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

int	ft_push_b(t_list **lst, size_t *size)
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
