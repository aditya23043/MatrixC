#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct m
{
	int **entries;
	int rows;
	int cols;
} Matrix;

void init_matrix(Matrix *m, char* dimension);
void cleanup(Matrix *m);
void print(Matrix *m);

int main()
{

	Matrix m;

	init_matrix(&m, "3x3");

	print(&m);

	cleanup(&m);

	return 0;
}

void init_matrix(Matrix *m, char* dimension)
{
	char buffer[32];
	char *ptr = NULL;

	strncpy(buffer, dimension, sizeof(buffer));
	buffer[sizeof(buffer)-1] = '\0';

	ptr = strchr(buffer, 'x');
	if(ptr == NULL)
	{
		printf("Wrong dimension format (nxm)\n");
		exit(1);
	}
	ptr++;

	m->cols = atoi(ptr);

	ptr = buffer;
	*strchr(buffer, 'x') = '\0';

	m->rows = atoi(ptr);

	m->entries = malloc(sizeof(int*) * m->rows);

	for(int i = 0; i < m->rows; i++)
	{
		m->entries[i] = malloc(sizeof(int) * m->cols);
		for(int j = 0; j < m->cols; j++)
		{
			m->entries[i][j] = 0;	
		}
	}
}

void cleanup(Matrix *m)
{
	for(int i = 0; i < m->rows; i++)
	{
		free(m->entries[i]);
	}
	free(m->entries);
}

void print(Matrix *m)
{
	for(int i = 0; i < m->rows; i++)
	{
		for(int j = 0; j < m->cols; j++)
		{
			printf("%d ", m->entries[i][j]);
		}
		printf("\n");
	}
}
