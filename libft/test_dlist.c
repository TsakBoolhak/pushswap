#include <stdio.h>
#include <stdlib.h>
#include "ft_dlist.h"

void	ft_dlstprint_value(void *content)
{
	if (content)
		printf("%d\n", *(int *)content);
	else
		printf("content is NULL\n");
}

void	*ft_sub_one(void *content)
{
	int	*ret;

	if (!content)
		return (NULL);
	ret = malloc(sizeof(int));
	if (!ret)
		return (NULL);
	*ret = (*(int *)content) - 1;
	return (ret);
}

void	ft_dlstprint_str(void *content)
{
	if (content)
		printf("%s\n", (char *)content);
	else
		printf("content is NULL\n");
}

int		main(int ac, char *av[])
{
	int	tab[10] = {42, -2, 3, 5, 115, 9, 0, 2147483647, -2147483648, -15};
	t_dlist	*lst = NULL;

	for (int i = 0; i < 10; i++)
	{
		t_dlist	*new = ft_dlstnew(tab + i);
		if (!new)
		{
			printf("Error while allocating new node\n");
			return (-1);
		}
		ft_dlstadd_back(&lst, new);
	}

	for (int i = 0; i < 10; i++)
	{
		t_dlist	*new = ft_dlstnew(tab + i);
		if (!new)
		{
			printf("Error while allocating new node\n");
			return (-1);
		}
		ft_dlstadd_front(&lst, new);
	}

	ft_dlstiter(lst, &ft_dlstprint_value);
	printf("\n list contains %lu nodes\n\n", ft_dlstsize(lst));

	ft_dlstdelone(&lst, ft_dlstlast(lst), NULL);
	ft_dlstiter(lst, &ft_dlstprint_value);
	printf("\n list contains %lu nodes\n\n", ft_dlstsize(lst));

	ft_dlstdelone(&lst, lst, NULL);
	ft_dlstiter(lst, &ft_dlstprint_value);
	printf("\n list contains %lu nodes\n\n", ft_dlstsize(lst));

	t_dlist *tmp = ft_dlstfirst(lst);
	int	caca = 1337;
	for (int i = 0; i < 3 && tmp->next ; i++)
	{
		tmp = tmp->next;
	}
	t_dlist	*new = ft_dlstnew(&caca);
	ft_dlstadd_after(&lst, tmp, new);
	new = ft_dlstnew(&caca);
	ft_dlstadd_before(&lst, tmp, new);
	ft_dlstiter(lst, &ft_dlstprint_value);
	printf("\n list contains %lu nodes\n\n", ft_dlstsize(lst));

	new = ft_dlstnew(&caca);
	ft_dlstadd_after(&lst, lst, new);
	new = ft_dlstnew(&caca);
	ft_dlstadd_before(&lst, lst, new);
	ft_dlstiter(lst, &ft_dlstprint_value);
	printf("\n list contains %lu nodes\n\n", ft_dlstsize(lst));

	new = ft_dlstnew(&caca);
	ft_dlstadd_before(&lst, ft_dlstlast(lst), new);
	new = ft_dlstnew(&caca);
	ft_dlstadd_after(&lst, ft_dlstlast(lst), new);
	ft_dlstiter(lst, &ft_dlstprint_value);
	printf("\n list contains %lu nodes\n\n", ft_dlstsize(lst));

	t_dlist	*dup = ft_dlstmap(lst, &ft_sub_one, NULL);
	if (dup)
	{
		printf("\nnewlist :\n");
		ft_dlstiter(dup, &ft_dlstprint_value);
		printf("\n list contains %lu nodes\n\n", ft_dlstsize(dup));
	}
	ft_dlstclear(&lst, NULL);
	ft_dlstclear(&dup, &free);
	if (!lst)
		printf("lst has been set to NULL\n");
	if (!dup)
		printf("lst has been set to NULL\n");
	
	lst = ft_dlstsplit("ceci est un test", ' ');
	ft_dlstiter(lst, &ft_dlstprint_str);
	ft_dlstclear(&lst, &free);

	printf("\n");
	lst = ft_dlstarg_to_list(ac, av);
	ft_dlstiter(lst, &ft_dlstprint_str);
	ft_dlstclear(&lst, NULL);
	return (0);
}
