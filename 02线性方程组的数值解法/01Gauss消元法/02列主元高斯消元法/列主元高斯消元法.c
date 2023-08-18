#include <stdio.h>
#include <math.h>
#define MAXSIZE 50 // 定义最大50阶的矩阵

void input (double a[MAXSIZE][MAXSIZE + 1], long); // 输入增广矩 阵
void output_matrix(double a[MAXSIZE][MAXSIZE+1], long n); //输出增广矩阵
void output(double x[MAXSIZE], long n);            //输出结果

int main(int argc, char *argv[])
{
    double a[MAXSIZE][MAXSIZE+1], x[MAXSIZE], s, max, t;
    // a[][] 存放增广矩阵
    // x[] 存放求解的 x 向量
    // s 是回代时使用，是用来存储中间变量的
    long n, i, j, k, maxi;
    printf("请输入原方程的阶数:");
    scanf("%ld", &n);
    input(a, n); //输入方程
    printf("原方程组的增广矩阵为:\n");
    output_matrix(a, n);

    // 消元过程
    for (k = 0; k <= n-2; k++) {
      max = a[k][k];
      maxi = k;
      for (i =k+1; i <= n-1; i++) {
        if(fabs(a[i][k]) > fabs(max)){
          max = a[i][k];
          maxi = i;
        }
      }
      if(0 == max){
        break;
      }
      if(maxi != k){
        for(j =k ; j<=n; j++){
          t = a[k][j];
          a[k][j] = a[maxi][j];
          a[maxi][j] = t;
        }
      }
      for (i =k+1; i <=n-1; i++) {
        a[i][k] /= -a[k][k];
        for(j=k+1; j<=n; j++){
          a[i][j] += a[i][k] * a[k][j];
        }
      }
    }

    // 回代过程
    if(0 == max){
      printf("原方程组无解\n");
    }else{
      for(k = n-1; k>=0; k--){
        s = 0;
        // s 存放的是将之前求解完的值都带入方程中系数得到的临时变量
        // eg: 已经求得 x_3 = 2, x_2 = 1
        // 带入方程 2x_1 + 5*x_2 - 3*x_3 = -3中
        // s = 5*1 - 3*2 = -1

        // 下面的循环就是实现上述例子来计算s的值
        for(j = k+1; j<=n-1; j++){
          s += a[k][j] * x[j];
          // x[j] 是已经求解的 x_{i} 值
          // a[k][j] 是方程x_{i}前的系数
        }

        // 计算新的 x 值
        x[k] = (a[k][n] - s) / a[k][k];
        // a[k][k] 就是代求x前的系数
        // a[k][n] 就是等号右端的常数
        // 就是移项在除上 当前系数
        // eg: 已知方程 2x_1 + 5*x_2 - 3*x_3 = -3
        // 其中 s = 5*x_2 - 3*x_3 = -1
        // x_1 = (-3 -s)/2
      }
    
      //输出结果
      output(x, n);
    }
      
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
