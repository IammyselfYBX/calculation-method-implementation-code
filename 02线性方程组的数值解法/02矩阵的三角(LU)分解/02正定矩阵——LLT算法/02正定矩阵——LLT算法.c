#include <stdio.h>
#include <math.h>
#define MAXSIZE 50

void input(double a[MAXSIZE][MAXSIZE], double x[MAXSIZE], long n);
void output(double x[MAXSIZE], long n);

int main(int argc, char *argv[])
{
    double a[MAXSIZE][MAXSIZE], x[MAXSIZE], s;
    long n, i, j, k;
    printf("请输入原方程的阶数:\n");
    scanf("%ld", &n);
    input(a, x, n);
    for (k = 0; k <= n-1; k++) {
      s = 0;
      for (j = 0; j <= k-1; j++) {
        s += a[k][j] * a[k][j];
      }
      a[k][k] = sqrt(a[k][k] - s);
      for(i=k+1; i<= n-1; i++){
        s = 0;
        for (j = 0; j <= k-1; j++) {
          s += a[i][j] * a[k][j];
        }
        a[i][k] = (a[i][k] - s)/ a[k][k];
      }
    }

    for(i = 0; i <= n-1; i++){
      s = 0;
      for(j = 0; j <= i-1; j++){
        s += a[i][j] * x[j];
      }
      x[i] = (x[i] - s)/a[i][i];
    }
    for (i = n-1; i >= 0; i--) {
      s = 0;
      for(j = i+1; j <= n-1; j++){
        s += a[j][i] * x[j];
      }
      x[i] = (x[i] - s)/a[i][i];
    }
    output(x, n);
    
    return 0;
}

void input(double a[MAXSIZE][MAXSIZE], double x[MAXSIZE], long n)
{
  long i, j;
  printf("请输入原方程组的增广矩阵:(用\" \"隔开):\n");
  for (i = 0; i <= n-1; i++) {
    for(j =0; j <= n-1; j++){
      scanf("%lf", &a[i][j]);
    }
    scanf("%lf", &x[i]);
  }
}

void output(double x[MAXSIZE], long n)
{
  long i;
  printf("原方程组的解为:\n");
  for (i = 0; i <= n-1; i++) {
      printf("  %lf\n", x[i]);
  }

}
