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
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}


char	*ft_strdup(const char *s1)
{
	int		s1_size;
	char	*s2;
	int		i;

	i = 0;
	s1_size = ft_strlen(s1);
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

int there_is_nl(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
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
		if (there_is_nl(str))
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

	if (!lst || !line_len)
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

void free_list(t_list **lst)
{
	t_list *tmp;

	while (*lst)
	{
		tmp = (*lst) -> next;
		free((*lst) -> content);
		free(*lst);
		*lst = tmp;
	}
}
int clear_list(t_list **lst)
{
	t_list *tmp;
	int str_len;
	int before_newline;
	char *save;

	if (!*lst)
		return (0);
	tmp = *lst;
	save = NULL;
	while (tmp -> next)
		tmp = tmp -> next;
	str_len = ft_strlen(tmp -> content);
	before_newline = look_for_newline(tmp -> content);
	if (before_newline && before_newline != str_len)
		save = ft_strdup((tmp -> content) + before_newline);
	free_list(lst);
	if (save && *save)
	{
		add_to_list(lst, save);
		return (ft_strlen(save));
	}
	return (0);
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
	line_len = clear_list(&lst);
	return (next_line);
}

int main()
{
	int fd = open("gnlTester/files/multiple_nlx5", O_RDWR);
	// //char *str = get_next_line(fd);
 	// printf("%s", str);
	// free(str);
	// // str = get_next_line(fd);
	// // printf("%s", str);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	//system("leaks a.out");
}
