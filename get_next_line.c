#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

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
	return (0);
}

void print_list(t_list *lst)
{
	while (lst)
	{
		printf("list item: %s\n", lst -> content);
		lst = lst -> next;
	}
}
void create_list(t_list **lst, int fd)
{
	char *str;
	int bytes_read;

	bytes_read = BUFFER_SIZE;
	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return ;
	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, str, BUFFER_SIZE);
		if (bytes_read <= 0)
		{	
			free(str);
			return ;
		}
		str[bytes_read] = '\0';
		add_to_list(lst, strdup(str));
	}
	return ;
}

int str_len(t_list *lst)
{
	int len;
	int i;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst -> content[i])
		{
			if (lst -> content[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		lst = lst -> next;
	}
	return (len);
}

char *create_line(t_list *lst)
{
	int len;
	char *line;	
	int i;
	int j;

	if (!lst)
		return (0);
	j = 0;
	len = str_len(lst);
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (lst)
	{
		i = 0;
		while (lst ->content[i])
		{
			line[j] = lst -> content[i];
			j++;
			if (lst -> content[i] == '\n')
				break ;
			i++;
		}
		lst = lst -> next;
	}
	line[j] = '\0';
	return (line);
}

void clear_list(t_list **lst)
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

char *get_next_line(int fd)
{
	char *next_line;
	static t_list *lst;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) < 0)
		return (NULL);
	create_list(&lst, fd);
	print_list(lst);
	next_line = create_line(lst);
	clear_list(&lst);
	return (0);
}
/*
int main()
{
	int fd = open("gnlTester/files/empty", O_RDWR);
	printf("%d\n", get_next_line(fd) == NULL);
	//printf("Res: %s", get_next_line(fd));
}
*/
