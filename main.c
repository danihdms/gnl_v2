#include <stddef.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main()
{
	int	fd;
	char	*line;

	fd = open("test", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s\n", line);
		free(line);
	}
}
