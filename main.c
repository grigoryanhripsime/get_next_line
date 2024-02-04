#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
	int fd = open("file.txt", O_RDONLY);
	if (!fd)
		return (0);
	printf("%s\n", get_next_line(fd));
	printf("\n");
}