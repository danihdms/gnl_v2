#include "get_next_line.h"


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
	while (*(buffer++))
		if (*buffer == '\n')
			return (1);
	return (0);
}

void	lst_add_back(char *buffer, t_list **remainder)
{
	t_list	*new;
	t_list	*tmp;
	int	i;

	if (!buffer || !remainder)
		return;
	new = malloc(sizeof(t_list));
	if (!new)
		return;
	new->next = NULL;
	new->len = ft_strlen(buffer);
	new->content = malloc(sizeof(char) * (ft_strlen(buffer) + 1));
	if (!(new->content))
		return;
	i = -1;
	while (buffer[++i])
		new->content[i] = buffer[i];
	new->content[i] = 0;
	if (!*remainder)
		*remainder = new;
	else
	{
		tmp = *remainder;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	separate_line(char *buffer, t_list **remainder, int before_len, int after_len)
{
	char	*before_new_line;
	char	*after_new_line;
	int	i;

	if (!buffer || !remainder)
		return;
	before_new_line = malloc(sizeof(char) * (before_len + 1));
	if (!before_new_line)
		return;
	i = -1;
	while (++i < before_len)
		before_new_line[i] = buffer[i];
	before_new_line[i] = 0;
	after_new_line = malloc(sizeof(char) * (after_len + 1));
	if (!after_new_line)
		return;
	i = -1;
	while (++i < after_len)
		after_new_line[i] = buffer[before_len + i];
	after_new_line[after_len + i] = 0;
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
	before_len++;
	while (buffer[before_len + after_len])
		after_len++;
	separate_line(buffer, remainder, before_len, after_len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int			i;
	int			j;
	char		*res;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = 0;
	return (res);
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
	res = malloc(sizeof(char) * (total_len + 1));
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
	char	*line;
	static t_list	*remainder;
	
	
	if (!remainder || (remainder && !contains_new_line(remainder->content)))
		fill_remainder(fd, &remainder);
	// 3. concatenate to get line
	line = concatenate_all(&remainder);
	if (!line)
		return (NULL);
	// 4. clean remainder
	clean_remainder(&remainder);

	return (line);
}
