#include "get_next_line.h"
#include <fcntl.h>

t_list  *ft_lstnew(void *content)
{
        t_list  *node;

        node = (t_list *)malloc(sizeof(t_list));
        if (!node)
                return (0);
        node -> content = content;
        node -> next = NULL;
        return (node);
}
void ft_lstadd_back(t_list **lst, char *str)
{
	t_list *tmp;
	
	if (!(*lst))
	{
		(*lst) = ft_lstnew(str);
		return ;
	}
	tmp = *lst;
	while (tmp -> next)
		tmp = tmp -> next;
	tmp -> next = ft_lstnew(str);
}
char    *ft_strchr(const char *s, int c)
{
        while (*s)
        {
                if (*s == (char) c)
                        return ((char *) s);
                s++;
        }
        if (c == '\0')
                return ((char *) s);
        return (0);
}
int create_list(t_list **lst, int fd)
{
	char *str;
	int read_bytes;
	int flag;
	int i;

	flag = 0;
	if (!str)
		return (0);
	while (!flag)
	{
		str = malloc((BUFFER_SIZE + 1) * sizeof(char));
		read_bytes = read(fd, str, BUFFER_SIZE);
		str[read_bytes] = '\0';
		ft_lstadd_back(lst, str);
		if (ft_strchr(str, '\n'))
				flag = 2;
		if (read_bytes > BUFFER_SIZE)
			flag = 1;	
	}
	return (flag);
}

void print_list(t_list *lst)
{
	while (lst)
	{
		printf("This is list item: %s\n", lst -> content);
		lst = lst -> next;
	}
	
}

int str_len(t_list *lst)
{
	int len;
	int i;	

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst -> content[i] && lst -> content[i] != '\n')
		{
			len++;
			i++;
		}
		lst = lst -> next;
	}
	return (len);
}

int     ft_lstsize(t_list *lst)
{
        int     count;

        count = 0;
        while (lst)
        {
                count++;
                lst = lst -> next;
        }
        return (count);
}

char *create_line(t_list *lst)
{
	int len;
	int i;
	char *str;
	
	len = str_len(lst);
	i = 0;
	//printf("This is len of the str: %d\n", len);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	while (lst)
	{
		while (*(lst -> content) && *(lst -> content) != '\n')
		{
			str[i] = *(lst -> content);
			lst -> content++;
			i++;
		}
		str[i] = '\0';
		lst = lst -> next;
	}
	return (str);	
}

char *move_to_start(char *str)
{
	int start;
	int i;
	
	i = 0;
	start = 0;
	while (str[start] && str[start] != '\n')
		start++;
	while (str[start + i])
	{
		str[i] = str[start + i];
		i++;
	}
	return (str);
}

void clean_list(t_list **lst, int res)
{
	t_list *tmp;
	
	while ((*lst) -> next)
	{
		tmp = (*lst) -> next;
		free((*lst) -> content);
		free(*lst);
		*lst = tmp;
	}
	if (res == 1)
	{
		free((*lst) -> content);
		free(*lst);
		*lst = NULL;
	}
	else if (res == 2)
	{
		(*lst) -> content = move_to_start((*lst) -> content);
		printf("%s\n", (*lst) -> content);
	}
}

char *get_next_line(int fd)
{
	static t_list *lst;
	char *next_line = NULL;

	if (fd <= 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) < 0)
		return (0);
	
	int res = create_list(&lst, fd);
	next_line = create_line(lst);
	printf("Lst len: %d\n", ft_lstsize(lst));
	//clean_list(&lst, res);
	print_list(lst);
	return (next_line);
}
int main()
{
	int fd = open("file.txt", O_RDONLY);
	printf("This is the result: %s\n", get_next_line(fd));
	printf("This is the result: %s\n", get_next_line(fd));
}
