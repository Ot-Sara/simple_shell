#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char *my_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int buffer_index, bytes_in_buffer;
	char *line = NULL, current_char;
	int line_index = 0;

	while (1)
	{
		if (buffer_index >= bytes_in_buffer)
		{
			bytes_in_buffer = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			buffer_index = 0;
			if (bytes_in_buffer <= 0)
			{
				break; } }

		current_char = buffer[buffer_index++];
		if (current_char == '\n')
		{
			line = realloc(line, (line_index + 1) * sizeof(char));
			line[line_index] = '\0';
			return (line); }
		else
		{
			line = realloc(line, (line_index + 2) * sizeof(char));
			line[line_index++] = current_char; }
	}

	if (line != NULL)
	{
		if (line_index > 0)
		{
			line = realloc(line, (line_index + 1) * sizeof(char));
			line[line_index] = '\0'; } }

	return (line);
}
