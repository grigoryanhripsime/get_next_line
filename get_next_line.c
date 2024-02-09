#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void print_list(t_list *lst)
{
	while (lst)
	{
		printf("list item: %s\n", lst -> content);
		lst = lst -> next;
	}
}

char	*ft_strdup(const char *s1)
{
	int		s1_size;
	char	*s2;
	int		i;

	i = 0;
	s1_size = 0;
	while (s1[s1_size])
		s1_size++;
	s2 = (char *)malloc(s1_size * sizeof(char) + 1);
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void add_to_list(t_list **lst, char *str)
{
	t_list *node;
	t_list *new;
	
	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new -> content = str;
	new -> next = NULL;	
	node = *lst;
	if (!node)
	{
		*lst = new;
		return ;
	}
	while (node -> next)
		node = node -> next;
	node -> next = new;
}

int look_for_newline(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (i);
}

int create_list(t_list **lst, int fd)
{
	char *str;
	int bytes_read;
	int lst_size;

	lst_size = 0;
	bytes_read = BUFFER_SIZE;
	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (0);
	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, str, BUFFER_SIZE);
		if (bytes_read <= 0)
		{	
			free(str);
			return (lst_size);
		}
		str[bytes_read] = '\0';
		add_to_list(lst, ft_strdup(str));
		lst_size += look_for_newline(str);
		if (look_for_newline(str) != BUFFER_SIZE)
			break ;
	}
	free(str);
	return (lst_size);
}

char *create_line(t_list *lst, int line_len)
{
	char *str;
	int i;
	int j;

	if (!lst)
		return (0);
	i = 0;
	str = malloc((line_len + 1) * sizeof(char));
	if (!str)
		return (0);
	while (i < line_len && lst)
	{
		j = 0;
		while (i < line_len && lst -> content[j])
		{
			str[i] = lst -> content[j];
			i++;
			j++;
		}
		lst = lst -> next;
	}
	str[i] = '\0';
	return (str);
}

void clear_list(t_list **lst, int line_len)
{
	t_list *tmp;

	if (!lst)
		return ;
	while (line_len >= BUFFER_SIZE && *lst)
	{
		tmp = (*lst) -> next;
		free((*lst) -> content);
		free(*lst);
		*lst = tmp;
		line_len -= BUFFER_SIZE;
	}
	while (*lst && *((*lst) -> content))
	{
		if (*((*lst) -> content) != '\n')
		{
			(*lst) -> content++;
		}
		else
		{
			(*lst) -> content++;
			break ;
		}
	}
}

char *get_next_line(int fd)
{
	char *next_line;
	static t_list *lst = NULL;
	static int line_len = 0;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) < 0)
		return (NULL);
	line_len += create_list(&lst, fd);
	next_line = create_line(lst, line_len);
	clear_list(&lst, line_len);
	line_len = BUFFER_SIZE - (line_len % BUFFER_SIZE);
	return (next_line);
}

int main()
{
	int fd = open("gnlTester/files/nl", O_RDWR);
	char *str = get_next_line(fd);
 	printf("%s", str);
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	//system("leaks a.out");
}