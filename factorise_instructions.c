#include "libft.h"
#include <stdlib.h>

void	ft_factorise_cancel_push(t_list **alst)
{
	t_list	*lst;
	t_list	*tmp;

	lst = *alst;
	while (lst && lst->next)
	{
		if (!ft_strcmp(lst->content, "pb"))
		{
			tmp = lst->next;
			while (tmp && (!ft_strcmp(tmp->content, "pa")
					|| !ft_strcmp(tmp->content, "pb")))
			{
				if (!ft_strcmp(tmp->content, "pa"))
				{
					ft_lstdelone(alst, tmp, &free);
					tmp = lst;
					lst = lst->next;
					ft_lstdelone(alst, tmp, &free);
					break ;
				}
				tmp = tmp->next;
			}
		}
		lst = lst->next;
	}
}

void	ft_replace_by_r(t_list **alst, t_list *lst, char *to_find)
{
	t_list	*tmp;
	char	*str;
	size_t	index;

	tmp = lst->next;
	str = (char *)(lst->content);
	index = ft_strlen(to_find) - 1;
	while (tmp && ft_strcmp(tmp->content, "pa")
		&& ft_strcmp(tmp->content, "pb") && ft_strcmp(tmp->content, "sa")
		&& ft_strcmp(tmp->content, "sb"))
	{
		if (!ft_strcmp(tmp->content, to_find))
		{
			ft_lstdelone(alst, tmp, &free);
			str[index] = 'r';
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_factorise_rotate(t_list **alst)
{
	t_list	*lst;

	lst = *alst;
	while (lst && lst->next)
	{
		if (!ft_strcmp(lst->content, "ra"))
			ft_replace_by_r(alst, lst, "rb");
		else if (!ft_strcmp(lst->content, "rb"))
			ft_replace_by_r(alst, lst, "ra");
		else if (!ft_strcmp(lst->content, "rra"))
			ft_replace_by_r(alst, lst, "rrb");
		else if (!ft_strcmp(lst->content, "rrb"))
			ft_replace_by_r(alst, lst, "rra");
		lst = lst->next;
	}
}

void	ft_delete_both(t_list **alst, t_list **lst, char *to_find)
{
	t_list	*tmp;

	tmp = (*lst)->next;
	while (tmp && ft_strcmp(tmp->content, "pa") && ft_strcmp(tmp->content, "pb")
		&& ft_strcmp(tmp->content, "sa") && ft_strcmp(tmp->content, "sb"))
	{
		if (!ft_strcmp(tmp->content, to_find))
		{
			ft_lstdelone(alst, tmp, &free);
			tmp = *lst;
			*lst = (*lst)->next;
			ft_lstdelone(alst, tmp, &free);
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_factorise_cancel_rotate(t_list **alst)
{
	t_list	*lst;

	lst = *alst;
	while (lst && lst->next)
	{
		if (!ft_strcmp(lst->content, "ra"))
			ft_delete_both(alst, &lst, "rra");
		else if (!ft_strcmp(lst->content, "rb"))
			ft_delete_both(alst, &lst, "rrb");
		lst = lst->next;
	}
}
