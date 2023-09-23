/*
 * Doolittle分解
 * 描述:给定一 n 阶矩阵 A ，利用 Doolittle 分解法给出矩阵A 之分解 A = LU
 * */
#include <stdio.h>
#include <math.h>

void Doolittle(int n, double A[][100], double L[][100], double U[][100]);

int main() {
 	  int n;
    double A[100][100], L[100][100], U[100][100];
    	
    scanf("%d", &n);
	  for(int i = 0; i < n; i++){
	  	for(int j = 0; j < n; j++){
	  		scanf("%lf", &A[i][j]);
	  	}
	  }
  	Doolittle(n, A, L, U);
  
  	for(int i = 0; i < n; i++){
  		for(int j = 0;j < n; j++){
  			printf("%lf ", L[i][j]);	
		}	
		printf("\n");
	  }
	  for(int i = 0; i < n; i++){
    		for(int j = 0;j < n; j++){
    			printf("%lf ", U[i][j]);	
	  	}
	  	printf("\n");	
	  }
}

void Doolittle(int n, double A[][100], double L[][100], double U[][100]){
  	//Doolittle分解
   // U赋初值
   for (int i = 0; i < n; i++) {
       U[0][i] = A[0][i];
   }
  	for(int j = 0; j <= n-1; j++){
        double s = 0;
    	  //计算矩阵L之第i列第k行元素
        // l_{ij} = \frac{a_{ij} - \sum\limits_{k=1}^{j-1} l_{ik}u_{kj}}{u_{jj}} \quad i = j+1, j+2, \dots, n
        // 给 L 的对角线赋值为1
        L[j][j] =1;
        for(int i = j+1; i <= n-1; i++){
          for(int k = 0; k<= j; k++){
            s += L[i][k] * U[k][j];
          }
          L[i][j] = (A[i][j] - s)/U[j][j];
      }

      //计算矩阵U之第i行第k列元素
      // u_{ij} = a_{ij} - \sum\limits_{k=1}^{i-1} l_{ik}u_{kj} \quad j = i, i+1, \dots, n
      for(int k = j+1; k <= n-1; k++){
          s = 0;
          for(int i = 0; i <= j; i++){
              s += L[j+1][i] * U[i][k];
          }
          U[j+1][k] = A[j+1][k] - s;
      }
    }
    
  	return;
}
