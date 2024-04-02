#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int border_width = 40;
int border_height = 40;

// int n = 4;
// double xpos[] = {10, 10, -10, -10};
// double ypos[] = {5, -5, 5, -5};


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
        double x = round(xpos[k] + 15);
        double y = round(ypos[k] + 15);
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
  // big X
  // int n = 20;
  // double xpos[] = { 1, 1, -1, -1, 2, 2, -2, -2, 3, 3, -3, -3, 4, 4, -4, -4, 5, 5, -5, -5};
  // double ypos[] = { 1, -1, 1, -1, 2, -2, 2, -2, 3, -3, 3, -3, 4, -4, 4, -4, 5, -5, 5, -5};

  // square
  int n = 38;
  // int n = 20;
  double xpos[n];
  double ypos[n];
  int idx = 0;
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      // top/bottom
      if (i == 0 || i == 10 - 1)
      {
        xpos[idx] = j;
        ypos[idx] = i;
        idx++;
      }
      else if (j == 0 || j == 10 - 1)
      {
        xpos[idx] = j;
        ypos[idx] = i;
        idx++;
      }
    }
  }

  // int n = 5;
  // double xpos[] = {0, 2, 0, -2, 0};
  // double ypos[] = {0, 0, 2, 0, -2};

  for (int i = 0; i < 6; i++)
  {}

  while (1)
  {
    system("clear");
    draw(n, xpos, ypos);
    
    for (int k = 0; k < n; k++)
    {
      rotate(10, &xpos[k], &ypos[k]);
    }

    double wait_s = 0.05;
    usleep(wait_s * 1000000);
  }

  return 0;
}
