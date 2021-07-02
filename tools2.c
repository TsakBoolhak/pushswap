#include "libft.h"
#include "pushswap.h"
#include <stdlib.h>

int	ft_search_forbidden_spaces(const char *str)
{
	char	forbidden;
	char	forbidden_spaces[6];
	int		i;

	i = 0;
	forbidden = 9;
	while (i < 5)
	{
		forbidden_spaces[i] = forbidden;
		forbidden++;
		i++;
	}
	forbidden_spaces[i] = '\0';
	if (ft_strchr_charset(str, forbidden_spaces))
		return (1);
	return (0);
}

void	ft_factorise_instruction(t_list **lst)
{
	ft_factorise_cancel_rotate(lst);
	ft_factorise_rotate(lst);
	ft_factorise_cancel_push(lst);
}

char	**ft_args_to_split(int ac, char **av)
{
	char	**tab[3];
	int		i;

	i = 0;
	tab[2] = NULL;
	while (++i < ac)
	{
		tab[0] = ft_split(av[i], ' ');
		if (!tab[0])
		{
			ft_free_tab((void *)tab[2]);
			return (NULL);
		}
		tab[1] = ft_splitjoin(tab[2], tab[0]);
		if (!tab[1])
		{
			ft_free_tab((void *)tab[2]);
			ft_free_tab((void *)tab[0]);
			return (NULL);
		}
		free(tab[2]);
		free(tab[0]);
		tab[2] = tab[1];
	}
	return (tab[2]);
}

int	ft_check_args(int ac, char **av, t_list **lst)
{
	int		i;
	char	**tab;

	tab = ft_args_to_split(ac, av);
	if (!tab)
		return (-1);
	i = 0;
	while (tab[i])
	{
		if (ft_is_nb_valid(&lst[0], tab[i]))
		{
			ft_free_tab((void **)tab);
			ft_lstclear(&lst[0], &free);
			return (-1);
		}
		i++;
	}
	ft_free_tab((void **)tab);
	return (0);
}
