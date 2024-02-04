#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 128

int main() {
    int fd = open("file.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char *buffer = (char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    size_t bufferSize = BUFFER_SIZE;
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, 1)) > 0) {
        if (buffer[bytesRead - 1] == '\n') {
            // Found end of line, process the line
            buffer[bytesRead] = '\0';  // Null-terminate the line
            printf("Read line: %s", buffer);

            // Reset the buffer for the next line
            free(buffer);
            buffer = (char *)malloc(BUFFER_SIZE);
            if (buffer == NULL) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
            bufferSize = BUFFER_SIZE;
        } else if (bytesRead == bufferSize) {
            // Buffer is full, realloc to double the size
            bufferSize *= 2;
            buffer = (char *)realloc(buffer, bufferSize);
            if (buffer == NULL) {
                perror("Memory allocation error");
                exit(EXIT_FAILURE);
            }
        }
    }

    if (bytesRead == -1) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    }

    free(buffer);
    close(fd);
    return 0;
}

