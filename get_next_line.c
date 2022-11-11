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

void	separate_line(char *buffer, t_list **remainder, int before_len, int after_len)
{
	char	*before_new_line;
	char	*after_new_line;
	int	i;

	if (!buffer || !remainder)
		return;
	before_new_line = malloc(sizeof(char) * (before_len + 1);
	if (!before_new_len)
		return;
	i = -1;
	while (--i < before_len)
		before_new_line[i] = buffer[i];
	before_new_line[i] = 0;
	after_new_line = malloc(sizeof(char) * (after_len + 1);
	if (!after_new_len)
		return;
	i = -1;
	while (--i < after_len)
		after_new_line[i] = buffer[after_len + i];
	after_new_line[aftr_len + i] = 0;
	lst_add_back(before_new_line, remainder);
	lst_add_back(after_new_line, remainder);
}

void	fill_remainder(int fd, t_list **remainder)
{
	char	*buffer;
	int	before_len;
	int	after_len;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return;
	while (!contains_new_line(buffer))
	{
		read(fd, buffer, BUFFER_SIZE);
		if (!contains_new_line(buffer))
			lst_add_back(buffer, remainder);
	}
	before_len = 1;
	after_len = 0;
	while (buffer[before_len] != '\n')
		before_len++;
	while (buffer[before_len + after_len])
		after_len++;
	separate_line(buffer, remainder, before_len, after_len);
}

char	*get_next_line(int fd)
{
	int	read_int;
	char	*line;
	static t_list	*remainder;

	fill_remainder(fd, &remainder);
	// 3. concatenate to get line
	// 4. clean remainder

	return (line);
}
