/* 
 * 高斯消元法求解线性方程组—— 顺序高斯消元法
 */

#include <stdio.h>
#include <math.h>
#define MAXSIZE 50 // 定义最大50阶的矩阵

void input (double a[MAXSIZE][MAXSIZE + 1], long); // 输入增广矩 阵
void output_matrix(double a[MAXSIZE][MAXSIZE+1], long n); //输出增广矩阵
void output(double x[MAXSIZE], long n);            //输出结果

int main(int argc, char *argv[])
{
    double a[MAXSIZE][MAXSIZE+1], x[MAXSIZE], s;
    long n, i, j, k;
    // n 是方程阶数
    printf("请输入原方程的阶数:");
    scanf("%ld", &n);
    input(a, n); //输入方程
    output_matrix(a, n);

    // 消元过程
    for(k = 0; k<= n-2; k++){
      for (i =k+1; i <= n-1; i++) {
        a[i][k] /= -a[k][k];
        for(j=k+1; j<=n; j++){
          a[i][j] += a[i][k] * a[k][j];
        }
      }
    }

    printf("打印消元后的上三角矩阵\n");
    output_matrix(a, n);

    // 回代(自上而下地求解上三角方程组)
    for(k = n-1; k>=0; k--){
      s = 0;
      for(j = k+1; j<=n-1; j++){
        s += a[k][j] * x[j];
      }
      x[k] = (a[k][n] - s) / a[k][k];
    }
    output(x, n);

    return 0;
}

void input(double a[MAXSIZE][MAXSIZE+1], long n)
{
  long i, j;
  printf("请输入原方程组的增广矩阵(用" "隔开):\n");
  for (i =1; i <= n; i++) {
      for (j = 0; j <= n; j++) {
        scanf("%lf", &a[i-1][j]);
      }

  }

}

void output_matrix(double a[MAXSIZE][MAXSIZE+1], long n)
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

void output(double x[MAXSIZE], long n)
{
  long k;
  printf("原方程组的解:\n");
  for (k=1; k <= n; k++) {
    printf("   %lf", x[k-1]);
  }
  printf("\n");
}

