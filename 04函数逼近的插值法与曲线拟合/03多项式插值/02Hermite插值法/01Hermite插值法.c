/* 
 * n个插值节点带1阶导数的埃尔米特插值
 */
#include <stdio.h>
#define MAXSIZE 50
void input(double x[MAXSIZE], double f[MAXSIZE], double df[MAXSIZE], long n);

int main(int argc, char *argv[])
{
    double x[MAXSIZE], f[MAXSIZE], df[MAXSIZE], Interpolation_x, Interpolation_y, l, dl;
    long n, i, j;
    printf("请输入插值节点的个数: ");
    scanf("%ld", &n);
    input(x, f, df, n);
    printf("请输入插值点: ");
    scanf("%lf", &Interpolation_x);
    Interpolation_y = 0; 
    for (i = 0; i <= n-1; i++) {
      l = 1;
      for(j = 0; j <= n-1; j++){
        if(j != i){
          l *= (Interpolation_x - x[j]) / (x[i] - x[j]);
        }
      }

      dl = 0;
      for(j = 0; j<= n-1; j++){
        if(j != i){
          dl += 1/(x[i] - x[j]);
        }
      }
      Interpolation_y += (1-2 * dl * (Interpolation_x - x[i])) * l * l * f[i] + (Interpolation_x - x[i])* l * l * df[i];
    }
    printf("插值点(x, y)= (%lf, %lf)\n", Interpolation_x, Interpolation_y);

    return 0;
}


void input(double x[MAXSIZE], double f[MAXSIZE], double df[MAXSIZE], long n)
{
  long i;
  for(i = 0; i <= n-1; i++)
    {
      printf("请输入插值节点x[%ld], 函数值f[%ld], 导数值df[%ld](请用,隔开):", i, i, i);
      scanf("%lf, %lf, %lf", &x[i], &f[i], &df[i]);
    }
}

