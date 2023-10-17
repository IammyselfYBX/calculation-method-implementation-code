#include <stdio.h>
#include <math.h>
#define MAXSIZE 50
void input(double a[MAXSIZE][MAXSIZE], double b[MAXSIZE], long n);
void output(double x[MAXSIZE], long n);

int main(int argc, char *argv[]){
  double a[MAXSIZE][MAXSIZE], b[MAXSIZE], x[MAXSIZE];//, oldx[MAXSIZE];
  double epsilon, e, s, oldx;
   long n, i, j, k, maxk;
   scanf("%ld" , &n);
   input(a, b, n);
   for(i =0; i <= n-1; i++){
     scanf("%lf", &x[i]);
   }
   maxk = 1000;
   epsilon = 0.000001;

   for(k=1; k <= maxk; k++){
     e = 0;
     for(i=0; i<= n-1; i++){
       oldx = x[i];
       s = 0;
       for(j=0; j <= n-1; j++){
         if(j!=i){
           s += a[i][j] * x[j];
         }
       }
       x[i] = (b[i] - s)/a[i][i];
       if(e < fabs(oldx - x[i])){
         e = fabs(oldx - x[i]);
       }
     }
     
     if( e< epsilon){
       break;
     }
   }
   if( k <= maxk){
     output(x, n);
   }else{
     printf("迭代次数已经超过上限\n");
   }
 
   return 0;
}


void input(double a[MAXSIZE][MAXSIZE], double b[MAXSIZE], long n){
 long i, j;
 for(i=0; i <= n-1; i++){
   for(j=0; j<= n-1; j++){
     scanf("%lf", &a[i][j]);
   }
 }

 for(i=0; i <= n-1; i++){
    scanf("%lf", &b[i]);
  }
}

void output(double x[MAXSIZE], long n){
 long i;
 for(i = 0; i <= n-1; i++){
   printf("%lf ", x[i]);
 }
}
