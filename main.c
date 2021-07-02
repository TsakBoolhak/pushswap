#include "libft.h"
#include "pushswap.h"

int	main(int ac, char *av[])
{
	t_list	*lst[5];
	size_t	size[3];
	int		*arr;
	t_chunk	chunk;

	ft_initialise(lst, size, &arr, &chunk);
	if (ac < 2)
		return (0);
	else if (ft_check_args(ac, av, lst))
		return (ft_error_shutdown(lst, &arr));
	size[0] = ft_lstsize(lst[0]);
	size[2] = size[0];
	if (ft_pswap_core(lst, size, &arr, &chunk))
		return (ft_print_n_quit(lst, &arr));
	else
		return (0);
}
