#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main()
{
	int	fd;
	char	*line;

	fd = open("test", O_RDONLY);
	if (fd == -1)
		printf("Nope");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		printf("%s\n", line);
		free(line);
	}
}
