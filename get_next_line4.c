#include "get_next_line.h"
#include <fcntl.h>
#include <string.h>
t_list *create_node(char *str)
{
	t_list *node;
	
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node -> content = str;
	node -> next = NULL;
	return (node);
}

void add_to_list(t_list **lst, t_list *node)
{
	t_list *tmp;
	
	tmp = *lst;
	if (!tmp)
	{
		*lst = node;
		return ;
	}
	while (tmp -> next)
		tmp = tmp -> next;
	tmp -> next = node;
}

void print_list(t_list *lst)
{
	while (lst)
	{
		printf("I'm list's item: %s\n", lst->content);
		lst = lst -> next;
	}
}
void create_list(t_list **lst, int fd)
{
	char *str;
	int i;
	
	int flag = 1;
	while (flag)
	{
		printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
		i = 0;
		str = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!str)
			return ;
		while (i < BUFFER_SIZE && read(fd, (str + i), 1) > 0)
		{
			//printf("I'm here\n");
			if (str[i] == '\n')
			{
				printf("helloooo\n");
				flag = 0;
			}
			i++;
		}
		if (!str[i])
		{
			flag = 0;
		}
		//create node
		t_list *node = create_node(str);
		//append that tode to list
		add_to_list(lst, node);
		print_list(*lst);
	}
}
int len_of_str(t_list *lst)
{
	int len;
	int i;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst -> content[i])
		{
			len++;
			i++;
		}
		lst = lst -> next;
	}
	return (len);
}

char *get_line(t_list *lst)
{
	int str_len;
	char *line;	
	int j;
	t_list *tmp;
	int i;

	j = 0;
	str_len = len_of_str(lst);
	printf("Len of the line: %d\n", str_len);
	line = malloc((str_len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (lst)
	{
		i = 0;
		while (lst -> content[i])
		{
			line[j] = lst -> content[i];
			i++;
			j++;
		}
		tmp = lst ->next;
		free(lst);
		lst = tmp;
	}
	line[j] = '\0';
	return (line);
}

char *get_next_line(int fd)
{
	t_list *lst = NULL;
	char *next_line = NULL;

	//printf("I'm here3\n");
	if (fd < 0 || read(fd, next_line, 0) < 0)
		return (0); 
	printf("I'm here2\n");
	create_list(&lst, fd);
	next_line = get_line(lst);
	lst = NULL;
	return (next_line);
}
/*

int main()
{
	int fd = open("gnlTester/files/nl", O_RDONLY);
	if (!fd)
		return (0);
	printf("%s", get_next_line(fd));	
	//printf("This is the result: %s\n", get_next_line(fd));	
	//printf("This is the result: %s\n", get_next_line(fd));	
	//printf("This is the result: %s\n", get_next_line(fd));	
}
*/