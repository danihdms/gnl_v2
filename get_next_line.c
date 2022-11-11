#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}
int	contains_new_line(char *buffer)
{
	if (!buffer)
		return (0);
	while (*buffer)
		if (*buffer == '\n')
			return (1);
	return (0);
}

void	lst_add_back(char *buffer, t_list **remainder)
{
	t_list	*new;
	int	i;

	if (!buffer || !remainder)
		return;
	new = malloc(sizeof(t_list));
	if (!new)
		return;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
	if (!(new->content))
		return;
	i = -1;
	while (buffer[++i])
		new->content[i] = buffer[i];
	new->content[i] = 0;
	while ((*remainder)->next)
		*remainder = (*remainder)->next;
	(*remainder)->next = new;
}

void	separate_line(char *buffer, t_list **remainder)
{
	char	*to_new_line;
	char	*after_new_line;

}

void	fill_remainder(int fd, t_list **remainder)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return;
	while (!contains_new_line(buffer))
	{
		read(fd, buffer, BUFFER_SIZE);
		if (!contains_new_line(buffer))
			lst_add_back(buffer, remainder);
	}
	separate_line(buffer, remainder);
}

char	*get_next_line(int fd)
{
	int	read_int;
	char	*line;
	static t_list	*remainder;

	// 1. Read file until new line is found, addind to remainder.
	fill_remainder(fd, &remainder);
	// 2. Separate the line containing the new line, adding it to remainder
	// 3. concatenate to get line
	// 4. clean remainder

	return (line);
}
