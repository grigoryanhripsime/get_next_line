/*

Use read function for reading each charecter from file, checking for '\n' or EOF
if there were 10 chars create new node

*/

#include "get_next_line.h"

int print_file(int fd)
{
	char c[1];

	while (read(fd, &c, 1) > 0)
	{
		if (c[0] == '\n')
			printf("heyheyhey\n");
		printf("%c", c[0]);
				
	}
	return (0);
}

int lst_size(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst -> next;
	}
	return (count);
}

t_list *create_node(char *str)
{
	t_list *node;
	node -> content = str;
	node -> next = NULL;
	printf("I'm %d\n", __LINE__);
	return (node);
}

t_list *lstlast(t_list *lst)
{
	while (lst -> next)
		lst = lst -> next;
	return lst;
}

void lst_add_last(t_list **lst, t_list *new)
{
	t_list	*node;
// printf("I'm %d\n", __LINE__);
	if (!(*lst))
	{
		printf("I'm %d\n", __LINE__);
		*lst = new;
		printf("This is in list: %s\n", (*lst) -> content);
		return ;
	}
	// printf("I'm %d\n", __LINE__);
	node = lstlast(*lst);
	node -> next = new;
	printf("abcd\n");
}

int read_buffer_size_bytes(int fd, t_list **lst)
{
	char *str;
	int i;

	i = 0;
	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (0);
	while (i < BUFFER_SIZE && read(fd, (str + i), 1))
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	printf("%s\n", str);
	printf("I'm %d\n", __LINE__);
	lst_add_last(lst, create_node(str));
	printf("I'm %d\n", __LINE__);
	if (i == BUFFER_SIZE)
		return (1);
	printf("I'm %d\n", __LINE__);
	return (0);
}

int str_len(t_list *lst)
{
	int len;
	int i;

	i = 0;
	printf("I'm %d\n", __LINE__);
	len = 0;
	while (lst)
	{
		printf("I'm %d\n", __LINE__);
		printf("here i am\n");
		while (lst -> content && lst -> content[i])
		{
			len++;
			i++;
			printf("%d %d\n", __LINE__, lst -> content[i]);
		}
		lst = lst -> next;
	}
	printf("this is len: %d\n", len);
	return (len);
}
char *fill_str(char *str, t_list *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		while (lst -> content)
		{
			str[i] = *(lst -> content);
			i++;
			lst -> content++;
		}
		lst = lst -> next;
	}
	return (str);
}

char *create_line(t_list *lst)
{
	int len;
	char *str;

	printf("I'm %d\n", __LINE__);
	len = str_len(lst);
	printf("Len of the str: %d\n", len);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	fill_str(str, lst);
	return (str);
}

char *get_next_line(int fd)
{
	static t_list *lst;

	int flag = 0;
	while (!flag)
	{
		if (!read_buffer_size_bytes(fd, &lst))
		{
			printf("I'm %d\n", __LINE__);
			flag = 1;
			return (create_line(lst));
		}
	}
	return(0);
}
