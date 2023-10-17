#include <stdio.h>

//#define MaxStep 1000
//#define eps 0.000001

double _abs(double a){
    return a > 0 ? a : -a;
}

double _max(double a, double b){
    return a > b ? a : b;
}

void Gauss_Seidel(int n , double a[][100] , double b[], double x[]){
    int MaxStep=1000;
    double eps = 0.000001;
    //判断迭代是否可进行
    for(int i = 1; i <= n; i++){
        if(_abs(a[i][i]) < 1e-15){
            printf("Fail.");
            return;
        }
    }

    int cnt = 0;
    double err = eps + 1.0;
    double tmp;         //临时变量 存放正在计算的数值
                        //计算完毕后滚动存放到数组x中

    while((err >= eps) && (cnt <= MaxStep)){
        err = 0;
        for(int i = 1; i <= n; i++){
            //迭代
            tmp = b[i];
            for(int j = 1; j <= n; j++){
                if(j != i){
                    tmp -= a[i][j] * x[j];
                }
            }
            tmp /= a[i][i];

            //计算误差
            err = _max(err,_abs(tmp-x[i])/(1.0+_abs(tmp)));
            
            x[i] = tmp; 

            
        }
        
        //更新计算次数
        cnt++;
        
    }

    if(cnt >= MaxStep){
		printf("Fail.");
        return;
	}
	else{
		for(int i = 1; i <= n; i++){
			printf("%lf ", x[i]);
		}
        return;
	}

}

int main(){
	
    int n;
    double a[100][100];
    double b[100],x[100];

    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            scanf("%lf", &a[i][j]);
        }
    }
    for(int i = 1; i <= n; i++){
        scanf("%lf", &b[i]);
    }
    for(int i = 1; i <= n; i++){
        scanf("%lf", &x[i]);
    }

    Gauss_Seidel(n, a, b, x);

    return 0;

}
