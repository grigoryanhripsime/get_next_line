/*

Use read function for reading each charecter from file, checking for '\n' or EOF
if there were 10 chars create new node

*/

#include "get_next_line.h"

int print_file(int fd)
{
	char c[1];

	//printf("%lu\n", read(fd, &c, 1));
	while (read(fd, &c, 1) > 0)
	{
		if (c[0] == '\n')
			printf("heyheyhey\n");
		printf("%c", c[0]);
				
	}
	return (0);
}



char *get_next_line(int fd)
{
	print_file(fd);
	
}
