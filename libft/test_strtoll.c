#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

int	main(int ac, char *av[])
{
	char		*end;
	long long	nb;
	int			i;

	if (ac < 2)
		puts("You should enter strings as arguments in order to test strtoll");
	i = 1;
	while (i < ac)
	{
		printf("Test #%d\n", i);
		puts("Let's first test the real strtoll :");
		nb = strtoll(av[i], &end, 10);
		printf("str's address : %p , str : \"%s\"\n", (void *)av[i], av[i]);
		printf("end's address : %p , *end's value : '%d'\n", (void *)end, *end);
		printf("nb = %lli\n", nb);
		puts("Now let's try our custom strtoll :");
		nb = ft_strtoll(av[i], &end);
		printf("str's address : %p , str : \"%s\"\n", (void *)av[i], av[i]);
		printf("end's address : %p , *end's value : '%d'\n", (void *)end, *end);
		printf("nb = %lli\n", nb);
		puts("----------------------------------------------");
		puts("");
		i++;
	}
	return (0);
}
