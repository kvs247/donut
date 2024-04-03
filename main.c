#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define HIDE_CURSOR() printf("\e[?25l")
#define SHOW_CURSOR() printf("\e[?25h")
#define MOVE_CURSOR() printf("\e[1;1H")

int border_width = 80;
int border_height = 45;

void rotate(double theta, double *x, double *y) {
  double theta_rad = theta * 3.14 / 180;

  double new_x = (*x * cos(theta_rad)) - (*y * sin(theta_rad));
  double new_y = (*x * sin(theta_rad)) + (*y * cos(theta_rad));

  *x = new_x;
  *y = new_y;

  // printf("%f %f\n", new_x, new_y);
};

void draw(int n, double xpos[], double ypos[])
{
  for (int i = 0; i < border_height; i++)
  {
    for (int j = 0; j < border_width; j++)
    {
      int do_draw = 0;
      for (int k = 0; k < n; k++)
      {
        double x = round(xpos[k] + 50);
        double y = round(ypos[k] + 20);
        if ((abs((double)i - y) < 1) && (abs((double)j - x) < 1))
        {
          do_draw = 1;
          printf("*");
          // break;
        }
      }

      if (!do_draw)
      {
        printf(" ");
      }
    }
    printf("\n");
  }
}

int main()
{
  HIDE_CURSOR();

  // square

  int square_height = 20;
  int square_width = 20;

  // int n = 56;
  int n = (2 * square_height) + (2 * square_width) - 4;
  double xpos[n];
  double ypos[n];
  
  int idx = 0;
  for (int i = 0; i < square_height; i++)
  {
    for (int j = 0; j < square_width; j++)
    {
      // top/bottom
      if (i == 0 || i == square_height - 1)
      {
        xpos[idx] = j;
        ypos[idx] = i;
        idx++;
      }
      // left/right
      else if (j == 0 || j == square_width - 1)
      {
        xpos[idx] = j;
        ypos[idx] = i;
        idx++;
      }
    }
  }
  printf("%d", idx);

  while (1)
  {
    // MOVE_CURSOR();
    system("clear");
    draw(n, xpos, ypos);
    
    for (int k = 0; k < n; k++)
    {
      rotate(10, &xpos[k], &ypos[k]);
    }

    double wait_s = 0.05;
    usleep(wait_s * 1000000);
  }

  SHOW_CURSOR();

  return 0;
}
