#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
#include <stdio.h>
# include <unistd.h>

typedef struct s_list {
	char *content;
	struct s_list *next;
}	t_list;

char *get_next_line(int fd);
int main();
#endif
