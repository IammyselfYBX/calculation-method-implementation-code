#include <stdio.h>
#include <math.h>
#define MAXSIZE 50
void input(double a[][MAXSIZE], double v[], long n); 
void doolittle(double a[][MAXSIZE], long n);
void back_substitution(double a[][MAXSIZE], double v[], long n); 
void normalization(double v[], long n, double * pm1); 
void output(double v[], long n, double m1);

int main(int argc, char *argv[])
{
    double a[MAXSIZE][MAXSIZE], v[MAXSIZE];
    double epsilon, m0, m1;
    long n, maxk, k;
    printf("请输入方阵A的阶数: ");
    scanf("%ld", &n);
    input(a, v, n);
    printf("请输入最大迭代次数: ");
    scanf("%ld", &maxk);
    printf("请输入主特征值的精度要求: ");
    scanf("%lf", &epsilon);
    doolittle(a, n);
    back_substitution(a, v, n);
    normalization(v, n, &m1);
    for(k=1; k<= maxk; k++){
      m0 = m1;
      back_substitution(a, v, n);
      normalization(v, n, &m1);
      if(fabs(m1-m0) <= epsilon){
        break;
      }
    }
    if(k <= maxk){
      output(v, n, 1/m1);
    }else{
      printf("迭代次数已经超过上限\n");
    }
    
    return 0;
}


void input(double a[][MAXSIZE], double v[], long n)
{
  long i, j;
  printf("请输入%ld阶方阵A: \n", n);
  for (i = 0; i <= n-1; i++) {
    for(j = 0; j <= n-1; j++){
      scanf("%lf", &a[i][j]);
    }
  }
  printf("请输入初始迭代向量(请用’ ‘隔开): ");
  for(i = 0; i <= n-1; i++){
    scanf("%lf", &v[i]);
  }
}

void doolittle(double a[][MAXSIZE], long n)
{
  long i,j, k;
  double s;
  for(k = 0; k <= n-2; k++){
    for(i = k+1; i <= n-1; i++){
      s = 0;
      for(j=0; j <= k-1; j++){
        s += a[i][j] * a[j][k];
      }
      a[i][k] = (a[i][k] -s)/a[k][k];
    }
    for(j=k+1; j <= n-1; j++){
      s = 0;
      for(i=0; i<=k; i++){
        s += a[k+1][i] * a[i][j];
      }
      a[k+1][j] -= s;
    }
  }
}

void back_substitution(double a[][MAXSIZE], double v[], long n)
{
  double s;
  long i, j;
  for(i = 1; i<=n-1; i++){
    s = 0;
    for(j=0; j<=i-1; j++){
      s += a[i][j]*v[j];
    }
    v[i] -= s;
  }
  for( i=n-1; i >= 0; i--){
    s = 0;
    for(j=i+1; j<=n-1; j++){
      s += a[i][j] * v[j];
    }
    v[i] = (v[i] - s)/a[i][i];
  }
}

void normalization(double v[], long n, double * pm1)
{
  long i;
  * pm1 = v[0];
  for(i = 0; i <= n-1; i++){
    if(fabs(* pm1) < fabs(v[i])){
      * pm1 = v[i];
    }
  }
  for(i =0; i <= n-1; i++){
    v[i] = v[i]/(* pm1);
  }
}

void output(double v[], long n, double m1)
{
  long i;
  printf("方阵A的主特征值约为: %lf\n", m1);
  printf("其对应的特征向量约为: \n");
  for(i=0; i<=n-1; i++){
    printf("%lf ", v[i]);
  }
}

