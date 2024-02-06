#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

t_list *new_node(char *content)
{
	t_list *node;
	
	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	node -> content = content;
	node -> next = NULL;
	return (node);
}

void add_to_list(t_list **lst, char *str)
{
	t_list *node;
	
	node = *lst;
	if (!node)
	{
		printf("%d, %s\n", __LINE__, str);
		*lst = new_node(str);
		return ;
	}
	while (node -> next)
		node = node -> next;
	printf("%d, %s\n", __LINE__, str);
	node -> next = new_node(str);
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
char *create_list(t_list **lst, int fd)
{
	char *str;
	int bytes_read;
	int start;

	bytes_read = BUFFER_SIZE;
	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (0);
	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, str, BUFFER_SIZE);
		add_to_list(lst, str);
		start = look_for_newline(str);
		if (start)
			return (str + start);
	}
	return (0);
}

char *get_next_line(int fd)
{
	char *next_line;
	static t_list *lst;
	char *tail;	

	printf("fd: %d, BS: %d, read: %lu\n", fd, BUFFER_SIZE, read(fd, next_line, 0));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) < 0)
		return (0);
	tail = create_list(&lst, fd);
	print_list(lst);
	printf("This is tail: %s\n", tail);
	//return(next_line);
}

int main()
{
	int fd = open("file.txt", O_RDONLY);
	get_next_line(fd);
}
