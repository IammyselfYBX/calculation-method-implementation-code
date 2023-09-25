/*
 * n 次牛顿插值的算法
 * 实现方法
 * 1.先实现差商表，用二维数组 f[i][j]存储
 * 2.利用差商表计算插值节点
 * 3.参考改进：利用秦九韶算法，遇到重复的乘法就提出公因子
 */
#include <stdio.h>
#include <math.h>
#define MAXSIZE 50

void input(double x[MAXSIZE], double f[MAXSIZE][MAXSIZE], long n);

int main(int argc, char *argv[])
{
    double x[MAXSIZE], f[MAXSIZE][MAXSIZE], Interpolation_x, Interpolation_y;
    long n, i, j;
    printf("请输入插值节点个数:");
    scanf("%ld", &n);
    input(x, f, n);
    printf("请输入代求的插值点:");
    scanf("%lf", &Interpolation_x);
    for(j=1; j<= n-1; j++){
      for (i = j; i <= n-1; i++) {
        f[i][j] = (f[i][j-1] - f[i-1][j-1])/(x[i] - x[i-j]);
      }      
    }
    Interpolation_y = f[n-1][n-1];
    for(i = n-2; i>=0; i--){
      Interpolation_y = f[i][i] + (Interpolation_x - x[i]) * Interpolation_y;
    }
    printf("插值点(x, y)=(%lf, %lf)\n", Interpolation_x, Interpolation_y);
  
    return 0;
}


void input(double x[MAXSIZE], double f[MAXSIZE][MAXSIZE], long n)
{
  long i;
  for(i = 0; i <= n-1; i++){
    printf("请输入插值节点x[%ld], y[%ld](中间用英文 \",\"隔开):", i, i);
    scanf("%lf, %lf", &x[i], &f[i][0]);
  }
}
