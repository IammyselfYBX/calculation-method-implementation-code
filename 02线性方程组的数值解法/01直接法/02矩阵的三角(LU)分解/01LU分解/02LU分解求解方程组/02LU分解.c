#include <stdio.h>
#include <math.h>
#define MAXSIZE 50

void input(double a[MAXSIZE][MAXSIZE], double x[MAXSIZE], long n);
void output_matrix(double a[MAXSIZE][MAXSIZE], double x[MAXSIZE], long n);
void output(double x[MAXSIZE], long n);
void print_L(double a[MAXSIZE][MAXSIZE], long n);
void print_U(double a[MAXSIZE][MAXSIZE], long n);

int main(int argc, char *argv[])
{
    double a[MAXSIZE][MAXSIZE], x[MAXSIZE], s;
    long n, i, j, k;
    printf("请输入原方程的阶数: ");
    scanf("%ld", &n);
    input(a, x, n);
    printf("原方程组的增广矩阵为:\n");
    output_matrix(a, x, n);
    for(k = 0; k <= n-2; k++){
      for (i = k+1; i <= n-1; i++) {
        s = 0;
        for(j=0; j<= k-1; j++){
          s += a[i][j] * a[j][k];
        }
        a[i][k] = (a[i][k] -s)/a[k][k];
      }
      for(j = k+1; j<= n-1; j++){
        s = 0;
        for (i = 0; i <= k; i++) {
          s += a[k+1][i] * a[i][j];
        }
        a[k+1][j] -= s;
      }
    }
    printf("打印一下LU分解后的矩阵:\n");
    print_L(a, n);
    print_U(a, n);

    printf("打印一下右端常数列的值:\n");
    output(x, n);
    for (i = 1; i <= n-1; i++) {
      s=0;
      for(j = 0; j < i; j++){
        s += a[i][j] * x[j];
      }
      x[i] -= s;
    }
    printf("打印中间变量y_1到y_n的值:\n");
    output( x, n);

    for (i = n-1; i >= 0; i--) {
      s = 0;
      for(j = i+1; j<= n-1; j++){
        s += a[i][j] * x[j];
      }
      x[i] = (x[i] - s)/a[i][i];
    }
    printf("原方程组的解为:\n");
    output(x, n);

    return 0;
}

void input(double a[MAXSIZE][MAXSIZE], double x[MAXSIZE], long n)
{
  long i, j;
  printf("请输入原方程组的增广矩阵:(用\" \"隔开):\n");
  for (i = 1; i <= n; i++) {
      for (j = 0; j <= n-1; j++) {
        scanf("%lf", &a[i-1][j]);
      }
      scanf("%lf", &x[i-1]);
  }
}

void output_matrix(double a[MAXSIZE][MAXSIZE], double x[MAXSIZE], long n)
{
    long i, j;
    for (i = 1; i <= n; i++) {
        for (j = 0; j <= n-1; j++) {
            printf("%10.2lf", a[i-1][j]);
        }
        printf("%10.2lf", x[i-1]);
        printf("\n");
    }
}

void output(double x[MAXSIZE], long n)
{
  long i;
  for (i = 0; i <= n-1; i++) {
    printf("  %lf", x[i]);
  }
  printf("\n");
}

void print_L(double a[MAXSIZE][MAXSIZE], long n)
{
  printf("打印单位下三角矩阵L\n");
  long i;
  printf("1\n");
  for(i = 1; i <= n-1; i++){
    for(long j = 0; j < i; j++){
      printf("%lf  ", a[i][j]);
    }
    printf("1\n");
  }
  printf("\n");
}

void print_U(double a[MAXSIZE][MAXSIZE], long n)
{
  printf("打印上三角矩阵U\n");
  for(long i = 0; i <= n-1; i++){
    for(long k = i; k > 0; k--){
      printf("\t  ");
    }
    for(long j =i; j <= n-1; j++){
      printf("%lf  ", a[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

