#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
# endif

typedef struct	s_list
{
	char		*content;
	struct s_list	*next;
	int		len;
}		t_list;

size_t	ft_strlen(char *str);
int	contains_new_line(char *buffer);
void	lst_add_back(char *buffer, t_list **remainder);
void	separate_line(char *buffer, t_list **remainder, int before_len, int after_len);
void	fill_remainder(t_list **remainder, char *buffer);
char	*ft_strjoin(char *s1, char *s2);
char	*concatenate_all(t_list	**remainder);
char	*get_next_line(int fd);

#endif
