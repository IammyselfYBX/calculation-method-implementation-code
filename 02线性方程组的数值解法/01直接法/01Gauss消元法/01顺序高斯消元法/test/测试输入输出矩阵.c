#include <stdio.h>
#define MAXSIZE 100
void input(double a[MAXSIZE][MAXSIZE+1], long n);
void output(double a[MAXSIZE][MAXSIZE+1], long n);

    
int main(int argc, char *argv[])
{
    double a[MAXSIZE][MAXSIZE+1];
    long n;
    printf("请输入方程组的阶数: ");
    scanf("%ld", &n);
    input(a, n);
    output(a, n);
    
    return 0;
}

void input(double a[MAXSIZE][MAXSIZE+1], long n)
{
  long i, j;
  printf("请输入原方程组的增广矩阵:\n");
  for (i =1; i <= n; i++) {
      for (j = 0; j <= n; j++) {
        scanf("%lf", &a[i-1][j]);
      }
  }
}

void output(double a[MAXSIZE][MAXSIZE+1], long n)
{
    long i, j;
    printf("原方程组的增广矩阵为:\n");
    for (i = 1; i <= n; i++) {
        for (j = 0; j <= n; j++) {
            printf("%10.2lf", a[i-1][j]);
        }
        printf("\n");
    }
}
