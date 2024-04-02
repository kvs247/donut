#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int border_width = 100;
int border_height = 50;

int start_x = 50;
int start_y = 25;

void draw(int x, int y)
{
  for (int i = 0; i < border_height; i++)
  {
    for (int j = 0; j < border_width; j++)
    {
      // top/bottom
      if (i == 0 || i == border_height - 1)
      {
        printf("-");
      }
      // left/right
      else if (j == 0 || j == border_width - 1)
      {
        printf("|");
      }
      // icon
      else if ((i == y) && (j == x))
      {
        printf("X");
      }
      else
      {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void update_position(int *x_ptr, int *y_ptr)
{
  int dx_dir = (rand() % 2) ? 1 : -1;
  int dx = dx_dir * (rand() % 5);

  int dy_dir = (rand() % 2) ? 1 : -1;
  int dy = dy_dir * (rand() % 5);

  int new_x = *x_ptr + dx;
  int new_y = *y_ptr + dy;

  if (new_x < 0 || border_width < new_x || new_y < 0 || border_height < new_y)
  {
    update_position(x_ptr, y_ptr);
    printf("nice\n");
  }
  else
  {
    *x_ptr = new_x;
    *y_ptr = new_y;
  }
}

int main()
{
  int x = start_x;
  int y = start_y;
  while (1)
  {
    system("clear");
    draw(x, y);
    update_position(&x, &y);

    double delay_seconds = 0.2;
    usleep(delay_seconds * 1000000);
  }

  return 0;
}