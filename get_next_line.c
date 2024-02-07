#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

t_list *new_node(char *content)
{
	t_list *node;
	
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
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
		//printf("%d, %s\n", __LINE__, str);
		*lst = new_node(str);
		return ;
	}
	while (node -> next)
		node = node -> next;
	//printf("%d, %s\n", __LINE__, str);
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
		return (NULL);
	while (bytes_read == BUFFER_SIZE)
	{
		bytes_read = read(fd, str, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			printf("aaaaa\n");
			str[0] = '\0';
			return (str);
		}
		str[bytes_read] = '\0';
		add_to_list(lst, strdup(str));
		start = look_for_newline(str);
		if (start)
			return (strdup(str + start));
	}
	return (NULL);
}

int str_len(t_list *lst)
{
	int len;
	int i;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst -> content[i] && lst)
		{
			len++;
			i++;
			if (lst -> content[i] == '\n')
			{
				i++;
				len++;
				return (len);;
			}

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

	j = 0;
	len = str_len(lst);
	//printf("Len of the str: %d\n", len);
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
		printf("I'm here %d\n", j);
		line[j] = '\0';
	}
	return (line);
}

void clear_list(t_list **lst)
{
	t_list *tmp;
	
	tmp = *lst;
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
	static char *tail;	

	next_line = NULL;
	//printf("fd: %d, BS: %d, read: %lu\n", fd, BUFFER_SIZE, read(fd, next_line, 0));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) < 0)
		return (NULL);
	if (tail)
	{
		add_to_list(&lst, tail);
	}
	tail = create_list(&lst, fd);
	print_list(lst);
	//printf("This is tail: %s\n", tail);
	next_line = create_line(lst);
	//printf("%s\n", next_line);
	clear_list(&lst);
	printf("%d, %lu\n", next_line[0], strlen(next_line));
	return (next_line);
}

int main()
{
	int fd = open("gnlTester/files/empty", O_RDWR);
	printf("%d\n", get_next_line(fd) == NULL);
	//printf("Res: %s", get_next_line(fd));
}
