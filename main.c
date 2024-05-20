#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/ioctl.h>

#define HIDE_CURSOR() printf("\e[?25l")
#define SHOW_CURSOR() printf("\e[?25h")
#define MOVE_CURSOR() printf("\e[1;1H")

void getArrMinMax(double *min, double *max, int n, double *arr)
{
  *min = arr[0];
  *max = arr[0];

  for (int i = 0; i < n; i++)
  {
    double ele = arr[i];

    if (ele < *min)
    {
      *min = ele;
    }

    if (ele > *max)
    {
      *max = ele;
    }
  }
}

void rotate(double theta, double *x, double *y)
{
  double thetaRad = theta * 3.14 / 180;

  double xnew = (*x * cos(thetaRad)) - (*y * sin(thetaRad));
  double ynew = (*x * sin(thetaRad)) + (*y * cos(thetaRad));

  *x = xnew;
  *y = ynew;
};

// for Ubuntu use the Noto Color Emoji terminal font for a grid-like layout
void draw(
    int n,
    unsigned short winowHeight,
    unsigned int windowWidth,
    double xPoints[],
    double yPoints[])
{
  double xmin;
  double xmax;
  double ymin;
  double ymax;

  getArrMinMax(&xmin, &xmax, n, xPoints);
  getArrMinMax(&ymin, &ymax, n, yPoints);

  double xPoint0 = xPoints[0];
  double yPoint0 = yPoints[0];

  double xPoint1 = xPoints[1];
  double yPoint1 = yPoints[1];

  double xPoint2 = xPoints[2];
  double yPoint2 = yPoints[2];

  double xPoint3 = xPoints[3];
  double yPoint3 = yPoints[3];

  double slope01 = (yPoint1 - yPoint0) / (xPoint1 - xPoint0);
  double slope12 = (yPoint2 - yPoint1) / (xPoint2 - xPoint1);
  double slope23 = (yPoint3 - yPoint2) / (xPoint3 - xPoint2);
  double slope30 = (yPoint0 - yPoint3) / (xPoint0 - xPoint3);

  int isSide01Top = 0;
  if (yPoint0 == ymax || yPoint1 == ymax)
  {
    isSide01Top = 1;
  }

  int isSide12Top = 0;
  if (yPoint1 == ymax || yPoint3 == ymax)
  {
    isSide12Top = 1;
  }

  for (int y = 0; y < winowHeight - 1; y++)
  {
    for (int x = 0; x < windowWidth - 1; x++)
    {
      double xOffset = windowWidth / 2;
      double yOffset = winowHeight / 2;

      double side01 = (slope01 * (x - (xPoint0 + xOffset))) + (yPoint0 + yOffset);
      double side23 = (slope23 * (x - (xPoint2 + xOffset))) + (yPoint2 + yOffset);

      double side12 = (slope12 * (x - (xPoint1 + xOffset))) + (yPoint1 + yOffset);
      double side30 = (slope30 * (x - (xPoint3 + xOffset))) + (yPoint3 + yOffset);

      int condition = 0;
      if (isSide01Top && isSide12Top)
      {
        condition = y <= side01 && y >= side23 && y <= side12 && y >= side30;
      }
      else if (isSide01Top && !isSide12Top)
      {
        condition = y <= side01 && y >= side23 && y >= side12 && y <= side30;
      }
      else if (!isSide01Top && isSide12Top)
      {
        condition = y >= side01 && y <= side23 && y >= side12 && y <= side30;
      }
      else
      {
        condition = y >= side01 && y <= side23 && y <= side12 && y >= side30;
      }

      if (condition)
      {
        printf("*");
      }
      else
      {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void make_corners(int *n, double **xpos, double **ypos)
{
  *n = 4;

  *xpos = (double *)malloc((*n) * sizeof(double));
  *ypos = (double *)malloc((*n) * sizeof(double));

  (*xpos)[0] = 10.0;
  (*xpos)[1] = 10.0;
  (*xpos)[2] = -10.0;
  (*xpos)[3] = -10.0;

  (*ypos)[0] = 10.0;
  (*ypos)[1] = -10.0;
  (*ypos)[2] = -10.0;
  (*ypos)[3] = 10.0;
}

int main()
{
  struct winsize windowSize;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize) == -1)
  {
    perror("ioctl");
    return 1;
  }

  HIDE_CURSOR();

  int n;
  double *xPoints, *yPoints;

  make_corners(&n, &xPoints, &yPoints);

  while (1)
  {
    MOVE_CURSOR();
    system("clear");
    draw(n, windowSize.ws_row, windowSize.ws_col, xPoints, yPoints);

    for (int k = 0; k < n; k++)
    {
      int r = 10;
      rotate(r, &xPoints[k], &yPoints[k]);
    }

    double wait_s = 0.05;
    usleep(wait_s * 1000000);
  }

  SHOW_CURSOR();

  return 0;
}
