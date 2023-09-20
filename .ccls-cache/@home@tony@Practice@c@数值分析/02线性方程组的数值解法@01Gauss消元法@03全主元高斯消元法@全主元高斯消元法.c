#include <stdio.h>
#include <math.h>
#define MAXSIZE 50 // 定义最大50阶的矩阵

void input (double a[MAXSIZE][MAXSIZE + 1], long n, long xj[MAXSIZE]); // 输入增广矩 阵
void output_matrix(double a[MAXSIZE][MAXSIZE+1], long n); //输出增广矩阵
void output(double x[MAXSIZE], long n, long xj[MAXSIZE]);            //输出结果

int main(int argc, char *argv[])
{
    double a[MAXSIZE][MAXSIZE+1], x[MAXSIZE], s, max, doublet;
    // a[][] 存放增广矩阵
    // x[] 存放求解的 x 向量
    // s 是回代时使用，是用来存储中间变量的
    long n, i, j, k, maxi, maxj, xj[MAXSIZE], longt;
    printf("请输入原方程的阶数:");
    scanf("%ld", &n);
    input(a, n, xj);

    for(k=0; k <= n-2; k++){
      max = a[k][k];
      maxi = k;
      maxj = k;
      for(j =k; j<= n-1; j++){
        if(fabs(a[i][j]) > fabs(max)){
          max = a[i][j];
          maxi = i;
          maxj = j;
        }
      }
      if(0 == max){
        break;
      }
      if(maxi != k){
        for(j=k; j<=n; j++){
          doublet = a[k][j];
          a[k][j] = a[maxi][j];
          a[maxi][j] = doublet;
        }
      }
      if(maxj != k){
        for (i = 0; i <= n-1; i++) {
          doublet = a[i][k];
          a[i][k] = a[i][maxj];
          a[i][maxj] = doublet;
        }
        longt = xj[k];
        xj[k] = xj[maxj];
        xj[maxj] = longt;
      }
      for(i=k+1; i<=n-1; i++){
        a[i][k] /= -a[k][k];
        for(j=k+1; j<= n; j++){
          a[i][j] += a[i][k] * a[k][j];
        }
      }
    }

    if( 0 == max){
      printf("原方程组无解\n");
    }else {
      for( k =n-1; k >= 0; k--){
        s = 0;
        for(j=k+1; j<= n-1; j++){
          s += a[k][j] * x[j];
        }
        x[k] = (a[k][n] - s)/a[k][k];
      }
      output(x, n, xj);
    }
    
    return 0;
}


void input(double a[MAXSIZE][MAXSIZE+1], long n, long xj[MAXSIZE])
{
  long i, j;
  printf("请输入原方程组的增广矩阵(用" "隔开):\n");
  for (i =1; i <= n; i++) {
      for (j = 0; j <= n; j++) {
        scanf("%lf", &a[i-1][j]);
      }
  }
  for(j =1; j <= n; j++){
    xj[j-1] = j-1;
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

void output(double x[MAXSIZE], long n, long xj[MAXSIZE])
{
  long j, k;
  printf("原方程组的解:\n");
  for (k=1; k <= n; k++) {
    for(j =1; j<= n; j++){
      if((k-1) == xj[j-1]){
        printf("   %lf", x[k-1]);
        break;
      }
    }
  }
  printf("\n");
}
