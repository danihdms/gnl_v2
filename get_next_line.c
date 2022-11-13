#include "get_next_line.h"

void	separate_line(char *buffer, t_list **remainder, int before_len, int after_len)
{
	char	*before_new_line;
	char	*after_new_line;
	int	i;

	if (!buffer || !remainder)
		return;
	before_new_line = calloc(sizeof(char), before_len + 1);
	if (!before_new_line)
		return;
	i = -1;
	while (++i < before_len)
		before_new_line[i] = buffer[i];
	before_new_line[i] = 0;
	after_new_line = calloc(sizeof(char), after_len + 1);
	if (!after_new_line)
		return;
	i = -1;
	while (++i < after_len)
		after_new_line[i] = buffer[before_len + i];
	// // after_new_line[after_len + i] = 0;
	lst_add_back(before_new_line, remainder);
	lst_add_back(after_new_line, remainder);
}

void	fill_remainder(t_list **remainder, char *buffer)
{
	int	before_len;
	int	after_len;
	
	before_len = 0;
	after_len = 0;
	while (buffer[before_len] != '\n')
		before_len++;
	before_len++;
	while (buffer[before_len + after_len])
		after_len++;
	separate_line(buffer, remainder, before_len, after_len);
}

char	*concatenate_all(t_list	**remainder)
{
	int	total_len;
	char	*res;
	t_list	*tmp;

	if (!remainder)
		return (NULL);
	tmp = *remainder;
	total_len= 0;
	while (tmp->next)
	{
		total_len += tmp->len;
		tmp = tmp->next;
	}
	res = calloc(sizeof(char), total_len + 1);
	if (!res)
		return (NULL);
	tmp = *remainder;
	while (tmp->next)
	{
		res = ft_strjoin(res, tmp->content);
		if (!res)
			return (NULL);
		tmp = tmp->next;
	}
	return (res);
}

void	clean_remainder(t_list **remainder)
{
	t_list	*tmp;

	if (!*remainder)
		return ;
	tmp = *remainder;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		*remainder = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = *remainder;
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	static t_list	*remainder;
	static int		read_int = 1;
	char	*buffer;

	if (fd < 0 || BUFFER_SIZE < 0 || read_int <= 0)
	{
		// free(remainder->content);
		// free(remainder);
		return (NULL);
	}
	buffer = calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!contains_new_line(buffer) && read_int > 0)
	{
		read_int = read(fd, buffer, BUFFER_SIZE);
		if (!contains_new_line(buffer))
			lst_add_back(buffer, &remainder);
	}
	if (buffer[0])
		fill_remainder(&remainder, buffer);
	line = concatenate_all(&remainder);
	if (!line)
		return (NULL);
	clean_remainder(&remainder);
	free(buffer);
	return (line);
}
