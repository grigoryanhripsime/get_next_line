#include "get_next_line.h"
#include <fcntl.h>

void create_line(t_list **lst, int fd)
{
	char *str;
	int read_bytes;

	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return ;
	while ()
	{
		read_bytes = read(fd, str, BUFFER_SIZE);
		if ()
	}
}


char *get_next_line(int fd)
{
	static t_list *lst;
	char *next_line = NULL;

	if (fd <= 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) <= 0)
		return (0);
	create_list(&lst, fd);
	return (next_line);
}

