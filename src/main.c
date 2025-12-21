#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct m
{
  int **entries;
  int rows;
  int cols;
} Matrix;

void init(Matrix *m, char *dimension);
void cleanup(Matrix *m);
void print(Matrix *m);
void i_multiply(Matrix *m, int num);
void input(Matrix *m);
int num_len(int num);
void load_from_file(Matrix *m, char *filename);

int main()
{

  Matrix m;

  init(&m, "3x5");
  // input(&m);

  load_from_file(&m, "matrix");

  // i_multiply(&m, 2);

  print(&m);
  cleanup(&m);

  return 0;
}

void init(Matrix *m, char *dimension) /* <<< */
{
  char buffer[32];
  char *ptr = NULL;

  strncpy(buffer, dimension, sizeof(buffer));
  buffer[sizeof(buffer) - 1] = '\0';

  ptr = strchr(buffer, 'x');
  if (ptr == NULL)
  {
    printf("Wrong dimension format (nxm)\n");
    exit(1);
  }
  ptr++;

  m->cols = atoi(ptr);

  ptr = buffer;
  *strchr(buffer, 'x') = '\0';

  m->rows = atoi(ptr);

  m->entries = malloc(sizeof(int *) * m->rows);

  for (int i = 0; i < m->rows; i++)
  {
    m->entries[i] = malloc(sizeof(int) * m->cols);
    for (int j = 0; j < m->cols; j++)
    {
      m->entries[i][j] = 0;
    }
  }
} /* >>> */

void cleanup(Matrix *m) /* <<< */
{
  for (int i = 0; i < m->rows; i++)
  {
    free(m->entries[i]);
  }
  free(m->entries);
} /* >>> */

void print(Matrix *m) /* <<< */
{
  int max_len = 0;

  for (int i = 0; i < m->rows; i++)
  {
    for (int j = 0; j < m->cols; j++)
    {
      if (num_len(m->entries[i][j]) > max_len)
      {
        max_len = num_len(m->entries[i][j]);
      }
    }
  }

  printf("╭%*c╮\n", (m->cols) * max_len + (1 * 2) + (2 * (m->cols - 1)), ' ');

  for (int i = 0; i < m->rows; i++)
  {
    printf("│");

    for (int j = 0; j < m->cols; j++)
    {
      printf("%*d ", max_len + 1, m->entries[i][j]);
    }
    printf("│\n");
  }

  printf("╰%*c╯\n", (m->cols) * max_len + (1 * 2) + (2 * (m->cols - 1)), ' ');

} /* >>> */

void i_multiply(Matrix *m, int num) /* <<< */
{
  for (int i = 0; i < m->rows; i++)
  {
    for (int j = 0; j < m->cols; j++)
    {
      m->entries[i][j] *= num;
    }
  }
} /* >>> */

void input(Matrix *m) /* <<< */
{
  for (int i = 0; i < m->rows; i++)
  {
    for (int j = 0; j < m->cols; j++)
    {
      scanf("%d", &m->entries[i][j]);
    }
  }
} /* >>> */

int num_len(int num) /* <<< */ { return floor(log10(num)) + 1; } /* >>> */

/*
 * 0 : success
 * 1 : failure
 */
void load_from_file(Matrix *m, char *filename) /* <<< */
{
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
    perror("File open");
    return;
  }

  int ret = 0;
  int i = 0;
  int j = 0;
  while (1)
  {
    if (j >= m->rows)
    {
      break;
    }

    ret = fscanf(fp, "%d", &m->entries[j][i]);
    if (ret == EOF || ret == 0)
    {
      break;
    }
    i++;

    if (i >= m->cols)
    {
      i = 0;
      j++;
    }
  }

} /* >>> */
