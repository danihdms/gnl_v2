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

char	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;
	size_t	i;

	if (size >= SIZE_MAX || nmemb >= SIZE_MAX)
		return (NULL);
	res = malloc(size * nmemb);
	if (!res)
		return (NULL);
	i = -1;
	while (++i < size)
		res[i] = 0;
	return (res);
}

void	lst_add_back(char *buffer, t_list **remainder)
{
	t_list	*new;
	t_list	*tmp;

	if (!buffer || !remainder)
		return;
	new = malloc(sizeof(t_list));
	if (!new)
		return;
	new->next = NULL;
	new->len = ft_strlen(buffer);
	new->content = buffer;
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

char	*ft_strjoin(char *s1, char *s2)
{
	int			i;
	int			j;
	char		*res;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	res = calloc(sizeof(char), ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = 0;
	free(s1);
	return (res);
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