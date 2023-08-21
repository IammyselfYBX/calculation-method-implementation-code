#include <stdio.h>
#include <math.h>
#define MAXSIZE 50

void input(double a[], double b[], double c[], double d[], long n);
void output(double x[], long n);

int main(int argc, char *argv[])
{
    double a[MAXSIZE], b[MAXSIZE], c[MAXSIZE], d[MAXSIZE], x[MAXSIZE];
    long n, i;
    printf("请输入原方程的阶数:");
    scanf("%ld", &n);
    input(a, b, c, d, n);
    for (i = 1; i < n; i++) {
        a[i] /= -b[i-1];       
        b[i] += c[i-1] * a[i]; 
        d[i] += d[i-1] * a[i]; 
    }

    x[n-1] = d[n-1] / b[n-1]; 
    for(i = n-2; i>= 0; i--){
      x[i] = (d[i] - c[i] * x[i+1])/b[i];
    }
    output(x, n);
    printf("\n");
      
    return 0;
}

void input(double a[], double b[], double c[], double d[], long n)
{
  long i;
  printf("请输入原方程组的增广矩阵:\n");
  printf("b1, c1, d1: ");
  scanf("%lf, %lf, %lf", &b[0], &c[0], &d[0]);
  for (i = 2; i <= n-1; i++) {
    printf("a%ld, b%ld, c%ld, d%ld: ", i, i, i, i);
    scanf("%lf, %lf, %lf, %lf", &a[i-1], &b[i-1], &c[i-1], &d[i-1]);
  }
  printf("a%ld, b%ld, d%ld: ", n, n, n);
  scanf("%lf, %lf, %lf", &a[n-1], &b[n-1], &d[n-1]);
}

void output(double x[], long n)
{
  long i;
  printf("方程组的解为:\n");
  for (i = 1; i <= n; i++) {
    printf(" %lf", x[i-1]);
  }
}
