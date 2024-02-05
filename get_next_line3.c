#include "get_next_line.h"
#include <fcntl.h>
char *get_next_line(int fd)
{

}


char *read_buffer_size_bites(int fd, int *end)
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
				{
					*end = 1;
					break;
                }
				i++;
        }
		if (!str[i])
			*end = 1;
        return (str);
}

t_list *create_node(char *content)
{
	t_list *node;
	
	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	printf("thsi is content: %s\n", content);
	node -> content = &content;
	node -> next = NULL;
 
	printf("thsi is content: %s\n", *(node -> content));
	return (node);
}

void lst_addlast(t_list **lst, t_list *node) {
    if (!(*lst)) {
        // If the list is empty, set the list pointer to the new node
        *lst = node;
    } else {
        // Traverse to the end of the list
        t_list *current = *lst;
        while (current->next) {
            current = current->next;
        }
        // Add the new node to the end of the list
        current->next = node;
    }
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

int main()
{
	static t_list *lst;
	int end;

	end = 0;
    int fd = open("file.txt", O_RDONLY);
    if (!fd)
		return (0);
	while (!end)
	{
		lst_addlast(&lst, create_node(read_buffer_size_bites(fd, &end)));
		printf("%d\n", __LINE__);
	}
	printf("%s\n", *(lst -> content));
	printf("%d\n", ft_lstsize(lst));
}
