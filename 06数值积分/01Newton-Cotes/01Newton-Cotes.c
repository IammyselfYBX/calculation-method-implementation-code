#include <stdio.h>
#define MAXSIZE 7
void input(double f[MAXSIZE+1], double a, double b, long n); 
int main(int argc, char *argv[])
{
    long c[MAXSIZE][MAXSIZE/2 +2] = {{2, 1},               
                                     {6, 1, 4},
                                     {8, 1, 3}, 
                                     {90, 7, 32, 12},
                                     {288, 19, 75, 50}, 
                                     {840, 41, 216, 27, 272},
                                     {17280, 751, 3577, 1323, 2989}};
    double a, b, f[MAXSIZE+1], integral;
    long n, i;
    printf("请输入积分区间边界a, b(用, 隔开): ");
    scanf("%lf, %lf", &a, &b);
    printf("请输入求积节点的个数(2~8): ");
    scanf("%ld", &n);
    if(n >8 || n <2){
        printf("输入节点个数不在(2~8)的范围!!!\n");
        return -1;
    }
    input(f, a, b, n);
    integral = 0;
    for(i = 0; i < n/2; i++){
      integral += (f[i] + f[n-i-1]) * c[n-2][i+1]/c[n-2][0]; 
    }
    if(n%2){
      integral += f[n/2] * c[n-2][n/2+1]/c[n-2][0];
    }
    integral *= b-a;
    printf("积分值 = %lf\n", integral);
    
    return 0;
}


void input(double f[MAXSIZE+1], double a, double b, long n)
{
  long i;
  double h;
  h = (b-a)/(n-1);
  printf("请输入求积节点纵坐标:\n");
  for (i = 0; i <= n-1; i++) {
    printf("x[%ld] = %lf, f[%ld]=", i, a+i*h, i);
    scanf("%lf", &f[i]);
  }
}

