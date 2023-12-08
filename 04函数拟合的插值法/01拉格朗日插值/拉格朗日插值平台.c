#include <stdio.h>
#include <math.h>
#define MAXSIZE 50

void input(double x[MAXSIZE], double y[MAXSIZE], long n);

int main(int argc, char *argv[])
{
    double x[MAXSIZE], y[MAXSIZE], l[MAXSIZE], Interpolation_x[MAXSIZE], Interpolation_y[MAXSIZE], tmp;
    long n,m, i, j;
    printf("请输入插值节点的个数:");
    scanf("%ld", &n);
    input(x, y, n);
    printf("请输入待求节点的个数:");
    scanf("%ld", &m);
    for (i = 0; i < m; i++)
    {
      printf("请输入待计算的插值点x的值:");
      scanf("%lf", Interpolation_x[i]);
      Interpolation_y[i] = 0;
      for (i = 0; i <= n-1; i++) {
          tmp = 1;
          for(j = 0; j <= n-1; j++){
            if(j != i){
              tmp *= (Interpolation_x[i] - x[j]) / (x[i] - x[j]);
            }
          }
        l[i] = tmp;
        Interpolation_y[i] += tmp * y[i];
     }
    }
    
    //printf("-----------------------------\n");
    //printf("Lagrange插值节点的基函数:\n");
    //for (int i = 0; i < n; i++) {
    //    printf("l[%d] = %ld\n", i, l[i]);
    //}
    printf("-----------------------------\n");
    for (i = 0; i < m; i++)
    {
      printf("插值点(x, y) = (%lf, %lf)\n", Interpolation_x[i], Interpolation_y[i]);
    }
    
    return 0;
}


void input(double x[MAXSIZE], double y[MAXSIZE], long n)
{
  long i;
  for (i = 0; i <= n-1; i++) {
    printf("请输入插值节点 x[%ld], y[%ld]:(中间用英文' '隔开): ", i, i);
    scanf("%lf %lf", &x[i], &y[i]);
  }
}
