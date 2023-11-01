#include <stdio.h>
#include <math.h>
#define MAXSIZE 50

void input(double a[][MAXSIZE], double v[], long n);
void matrix_product(double a[][MAXSIZE], double u[], double v[], long n);
void normalization(double u[], double v[], long n, double *pm1);
void output(double v[], long n, double m1);

int main(int argc, char *argv[])
{
    double a[MAXSIZE][MAXSIZE], u[MAXSIZE], v[MAXSIZE];
    double epsilon, m0, m1;
    long n, maxk, i;
    printf("请输入方阵A的阶数: ");
    scanf("%ld", &n);
    input(a, v, n);
    printf("请输入最大迭代次数: ");
    scanf("%ld", &maxk);
    printf("请输入主特征值的精度要求: ");
    scanf("%lf", &epsilon);
    matrix_product(a, u, v, n);
    normalization(u, v, n, &m1);
    for (i = 1; i <= maxk; i++) {
      m0 = m1;
      matrix_product(a, u, v, n);
      normalization(u, v, n, &m1);
      if (fabs(m1 - m0) <= epsilon) {
        break;
      }
    }
    if (i <= maxk) {
      output(v, n, m1);
    }else{
      printf("迭代次数已超过上限\n");
    }

    return 0;
}

void input(double a[][MAXSIZE], double v[], long n)
{
  long i, j;
  printf("请输入%ld阶方阵A: \n", n);
  for (i = 0; i <= n-1; i++) {
      for (j = 0; j <= n-1; j++) {
        scanf("%lf", &a[i][j]);
      }
  }
  printf("请输入初始迭代向量: \n");
  for (i = 0; i <= n-1; i++) {
    scanf("%lf", &v[i]);
  }
}

void matrix_product(double a[][MAXSIZE], double u[], double v[], long n)
{
  long i, j;
  for (i = 0; i <= n-1; i++) {
    u[i] = 0;
    for (j = 0; j <= n-1; j++) {
      u[i] += a[i][j] * v[j];
    }
  }
}

void normalization(double u[], double v[], long n, double *pm1)
{
  long i;
  * pm1 = u[0];
  for (i = 1; i <= n-1; i++) {
    if (fabs(* pm1) < fabs(u[i])) {
      * pm1 = u[i];
      }
  }
  for (i = 0; i <= n-1; i++) {
    v[i] = u[i] / (* pm1);
  }
}

void output(double v[], long n, double m1)
{
  long i;
  printf("方阵A的主特征值约为: %lf\n", m1);
  printf("其对应特征向量约为: \n");
  for (i = 0; i <= n-1; i++) {
      printf("%lf\n", v[i]);
  }
}
