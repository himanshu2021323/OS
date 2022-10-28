#include <stdio.h>
#include <stdlib.h> 

int main(int argc, char const *argv[])
{
	FILE *file;

	if (argc == 1)
	{
		printf("ERROR: Enter file name\n");
	}

	if (strcmp(argv[1], "-n") == 0)
	{
		file = fopen(argv[2], "r");
		if (file == NULL)
		{
			perror("Error: ");
		}
		else
		{
			char *buffer = NULL;
			size_t l = 0;
			size_t read;
			int count = 1;
			while ((read = getline(&buffer, &l, file)) != -1)
			{
				printf("%d %s", count++, buffer);
			}
			fclose(file);
		}
	}

	else if (strcmp(argv[1], "-E") == 0)
	{
		file = fopen(argv[2], "r");
		if (file == NULL)
		{
			perror("Error: ");
		}
		else
		{
			char *buffer = NULL;
			size_t l = 0;
			size_t read;

			while ((read = getline(&buffer, &l, file)) != -1)
			{
				strtok(buffer, "\n");
				printf("%s$ \n", buffer);
			}
			fclose(file);
		}
	}
	else
	{
		file = fopen(argv[1], "r");
		if (file == NULL)
		{
			perror("Error: ");
		}
		else
		{
			char *buffer = NULL;
			size_t l = 0;
			size_t read;

			while ((read = getline(&buffer, &l, file)) != -1)
			{
				printf("%s ", buffer);
			}
			fclose(file);
		}
	}
	// cat(argc, argv);
	return 0;
}