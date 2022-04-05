
#include "so_long.h"

int32_t	main(int32_t argc, char **argv)
{
	char			**map;
	int32_t			fd;

	map = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			return (ft_putendl_fd("Error\n Invalid file", STDOUT_FILENO) \
					, EXIT_FAILURE);
		if (!check_ext(argv[1], ".ber"))
			return (EXIT_FAILURE);
		input_handler(fd, map);
	}
	else if (argc > 2)
		return (ft_putendl_fd("Error\nToo many arguments dude", \
				STDOUT_FILENO), EXIT_FAILURE);
	else
		return (ft_putendl_fd("Error\nNot enough arguments dude", \
				STDOUT_FILENO), EXIT_FAILURE);
	return (0);
}