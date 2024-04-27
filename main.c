#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/ioctl.h>

#define HIDE_CURSOR() printf("\e[?25l")
#define SHOW_CURSOR() printf("\e[?25h")
#define MOVE_CURSOR() printf("\e[1;1H")

int border_width = 80;
int border_height = 45;

void rotate(double theta, double *x, double *y)
{
  double theta_rad = theta * 3.14 / 180;

  double new_x = (*x * cos(theta_rad)) - (*y * sin(theta_rad));
  double new_y = (*x * sin(theta_rad)) + (*y * cos(theta_rad));

  *x = new_x;
  *y = new_y;
};

void draw(int n, unsigned short wheight, unsigned int wwidth, double xpos[], double ypos[])
{
  for (int i = 0; i < wheight - 1; i++)
  {
    for (int j = 0; j < wwidth - 1; j++)
    {
      int do_draw = 0;
      for (int k = 0; k < n; k++)
      {
        double x = round(xpos[k] + (wwidth / 2));
        double y = round(ypos[k] + (wheight / 2));
        if ((abs((double)i - y) < 1) && (abs((double)j - x) < 1))
        {
          do_draw = 1;
          printf("*");
          break; // need this?
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

void make_square_border(int *n, double **xpos, double **ypos)
{
  int square_height = 20;
  int square_width = 30;

  int i_range = square_height / 2;
  int j_range = square_width / 2;

  *n = (2 * square_height) + (2 * square_width) - 4;

  *xpos = (double *)malloc((*n) * sizeof(double));
  *ypos = (double *)malloc((*n) * sizeof(double));

  int idx = 0;
  for (int i = -i_range; i < i_range; i++)
  {
    for (int j = -j_range; j < j_range; j++)
    {
      // top/bottom
      if (i == -i_range || i == i_range - 1)
      {
        (*xpos)[idx] = j;
        (*ypos)[idx] = i;
        idx++;
      }
      // left/right
      else if (j == -j_range || j == j_range - 1)
      {
        (*xpos)[idx] = j;
        (*ypos)[idx] = i;
        idx++;
      }
    }
  }
}

void make_square(int *n, double **xpos, double **ypos)
{
  int square_height = 20;
  int square_width = 20;

  int i_range = square_height / 2;
  int j_range = square_width / 2;

  *n = square_height * square_width;

  *xpos = (double *)malloc((*n) * sizeof(double));
  *ypos = (double *)malloc((*n) * sizeof(double));

  int idx = 0;
  for (int i = -i_range; i < i_range; i++)
  {
    for (int j = -j_range; j < j_range; j++)
    {
      (*xpos)[idx] = j;
      (*ypos)[idx] = i;
      idx++;
    }
  }
}

int main()
{
  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
  {
    perror("ioctl");
    return 1;
  }

  HIDE_CURSOR();

  int n;
  double *xpos, *ypos;

  // make_square_border(&n, &xpos, &ypos);
  make_square(&n, &xpos, &ypos);

  while (1)
  {
    MOVE_CURSOR();
    system("clear");
    draw(n, ws.ws_row, ws.ws_col, xpos, ypos);

    for (int k = 0; k < n; k++)
    {
      int r = 10;
      rotate(r, &xpos[k], &ypos[k]);
    }

    double wait_s = 0.05;
    // double wait_s = 1;
    usleep(wait_s * 1000000);
  }

  SHOW_CURSOR();

  return 0;
}
