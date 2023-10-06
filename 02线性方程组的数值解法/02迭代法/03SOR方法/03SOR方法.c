#include <stdio.h>
#include <math.h>
#define MAXSIZE 100
void input(double a[MAXSIZE][MAXSIZE], double b[MAXSIZE], long n);
void output(double x[MAXSIZE], long n);
long SOR(long n, double A[MAXSIZE][MAXSIZE], double b[MAXSIZE], double x[MAXSIZE], double w, long maxk, double epsilon);
int main(int argc, char *argv[]){
  long n, maxk;
  double epsilon;
  double A[MAXSIZE][MAXSIZE],b[MAXSIZE],x[MAXSIZE], w;

  printf("请输入原方程组的阶数: ");
  scanf("%ld", &n);
  input(A, b, n);
  printf("请输入提速因子ω: ");
  scanf("%lf", &w);
  printf("请输入迭代初始向量(中间用‘ ’隔开): ");
  for(long i =0; i <= n-1; i++){
      scanf("%lf", &x[i]);
  }
  printf("请输入最大迭代次数: ");
  scanf("%ld", &maxk);
  printf("请输入误差上限: ");
  scanf("%lf", &epsilon);
  
  long k = SOR(n, A, b, x, w, maxk, epsilon);
  if( k <= maxk){
      output(x, n);
      printf("迭代次数%ld\n", k);
  }else{
      printf("迭代次数已经超过上限\n");
  }

  return 0;
} 

void input(double a[MAXSIZE][MAXSIZE], double b[MAXSIZE], long n)
{
    printf("请输入原方程的增广矩阵(每一行中的元素用' '隔开)\n");
    for(long i=0; i <= n-1; i++){
     for(long j=0; j<= n-1; j++){
       scanf("%lf", &a[i][j]);
     }
     scanf("%lf", &b[i]);
    }
}

void output(double x[MAXSIZE], long n)
{
    printf("原方程组的解为: \n");
    for(long i=0; i <= n-1; i++)
    {
        printf("%lf\n", x[i]);
    }
}

long SOR(long n, double A[MAXSIZE][MAXSIZE], double b[MAXSIZE], double x[MAXSIZE], double w, long maxk, double epsilon)
{
    double e, oldx, s;
    long k =1, i, j;
    while( k<= maxk){
        e = 0;
       for(i=0; i<= n-1; i++){
         oldx = x[i];
         s = 0;
         for(j=0; j <= n-1; j++){
             s += A[i][j] * x[j];
         }
         x[i] = oldx + w * (b[i] - s)/A[i][i];
         if(e < fabs(oldx - x[i])){
           e = fabs(oldx - x[i]);
         }
       }

       if( e< epsilon){
         break;
       }
       k += 1;
     }

    return k;
}
