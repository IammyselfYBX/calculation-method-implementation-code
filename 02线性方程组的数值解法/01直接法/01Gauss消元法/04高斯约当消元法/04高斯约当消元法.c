#include <stdio.h>
#include <math.h>
#define MAXSIZE 50

void input(double a[MAXSIZE][MAXSIZE+1], long n);
void output(double a[MAXSIZE][MAXSIZE+1], long n);

int main(int argc, char *argv[])
{
    double a[MAXSIZE][MAXSIZE+1];
    long n, i, j, k;
    printf("请输入原方程的阶数:");
    scanf("%ld", &n);
    input(a, n); 

    for(k = 0; k<= n-2; k++){
      for (i =k+1; i <= n-1; i++) {
        a[i][k] /= -a[k][k];
        for(j=k+1; j<=n; j++){
          a[i][j] += a[i][k] * a[k][j];
        }
      }
    }
    
    for (k = 0; k < n; k++) { 
      for (j = k + 1; j <= n; j++) {
        a[k][j] /= a[k][k];
      }
      a[k][k] = 1;
    }
    
    for (k = n-1; k > 0; k--) { 
      for (i = k-1; i >= 0 ; i--) {
        a[i][n] -= a[i][k];
        a[i][k] = 0;
      }
    } 
    
    output(a, n);

    return 0;
}


void input(double a[MAXSIZE][MAXSIZE + 1], long n) {
  long i, j;
  printf("请输入原方程组的增广矩阵: \n");
  for (i = 1; i <= n; i++) {
      for (j = 0; j <= n ; j++) {
        scanf("%lf", &a[i-1][j]);
      }
  }
}

void output(double a[MAXSIZE][MAXSIZE + 1], long n) {
  long k;
  printf("原方程组的解为:\n");
  for (k = 1; k <= n; k++) {
    printf("  %lf", a[k-1][n]);
  }
  printf("\n");
}
