/*************************************************
********CUBIC SPLINE FOR EQUIDISTANT POINTS*******
*************************************************/
#include<stdio.h>
#include<math.h>
/*******
 Function that performs Gauss-Elimination and returns the Upper triangular matrix and solution of equations:
There are two options to do this in C.
1. Pass the augmented matrix (a) as the parameter, and calculate and store the upperTriangular(Gauss-Eliminated Matrix) in it.
2. Use malloc and make the function of pointer type and return the pointer.
This program uses the first option.
********/
void gaussEliminationLS(int m, int n, double a[m][n], double x[n-1]){
    int i,j,k;
    for(i=0;i<m-1;i++){
        //Partial Pivoting
        for(k=i+1;k<m;k++){
            //If diagonal element(absolute vallue) is smaller than any of the terms below it
            if(fabs(a[i][i])<fabs(a[k][i])){
                //Swap the rows
                for(j=0;j<n;j++){                
                    double temp;
                    temp=a[i][j];
                    a[i][j]=a[k][j];
                    a[k][j]=temp;
                }
            }
        }
        //Begin Gauss Elimination
        for(k=i+1;k<m;k++){
            double  term=a[k][i]/ a[i][i];
            for(j=0;j<n;j++){
                a[k][j]=a[k][j]-term*a[i][j];
            }
        }
         
    }
    //Begin Back-substitution
    for(i=m-1;i>=0;i--){
        x[i]=a[i][n-1];
        for(j=i+1;j<n-1;j++){
            x[i]=x[i]-a[i][j]*x[j];
        }
        x[i]=x[i]/a[i][i];
    }
             
}
/********************
Cubic Spline coefficients calculator
********************/
void cSCoeffCalc(int n, double h, double sig[n+1], double y[n+1], double a[n], double b[n], double c[n], double d[n]){
    int i;
    for(i=0;i<n;i++){
        d[i]=y[i];
        b[i]=sig[i]/2.0;
        a[i]=(sig[i+1]-sig[i])/(h*6.0);
        c[i]=(y[i+1]-y[i])/h-h*(2*sig[i]+sig[i+1])/6.0;
    }
}
/********************
Function to generate the tridiagonal augmented matrix 
for cubic spline for equidistant data-points
Parameters:
n:
a:
y:
********************/
void tridiagonalCubicSplineGen(int n, double h, double a[n-1][n], double y[n+1]){
    int i;
    for(i=0;i<n-1;i++){
        a[i][i]=4;
    }
    for(i=0;i<n-2;i++){
        a[i][i+1]=1;
        a[i+1][i]=1;
    }
    for(i=0;i<n-1;i++){
        a[i][n-1]=(y[i+2]-2*y[i+1]+y[i])*6/h/h;
    }
} 
/*******
Function that prints the elements of a matrix row-wise
Parameters: rows(m),columns(n),matrix[m][n] 
*******/
void printMatrix(int m, int n, double matrix[m][n]){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%lf\t",matrix[i][j]);
        }
        printf("\n");
    } 
}
/*******
Function that copies the elements of a matrix to another matrix
Parameters: rows(m),columns(n),matrix1[m][n] , matrix2[m][n]
*******/
void copyMatrix(int m, int n, double matrix1[m][n], double matrix2[m][n]){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            matrix2[i][j]=matrix1[i][j];
        }
    } 
}
main(){
    int m,i;
    printf("Enter the no. of data-points:\n");
    scanf("%d",&m);
    int n=m-1;  //Now (n+1) is the total no. of data-points, following our convention
    double x[n+1];
    double y[n+1];
    printf("Enter the x-axis values:\n");
    for(i=0;i<n+1;i++){
        scanf("%lf",&x[i]);
    }
    printf("Enter the y-axis values:\n");
    for(i=0;i<n+1;i++){
        scanf("%lf",&y[i]);
    }
    double h=x[1]-x[0];     //space interval
    double a[n];
    double b[n];
    double c[n];
    double d[n];
    double sig[n+1];
    double sigTemp[n-1];
    sig[0]=0;
    sig[n]=0;
    double tri[n-1][n];
    tridiagonalCubicSplineGen(n,h,tri,y);
    printf("The tridiagonal system for the Natural spline is:\n\n");
    printMatrix(n-1,n,tri);
    //Perform Gauss Elimination 
    gaussEliminationLS(n-1,n,tri,sigTemp);
    for(i=1;i<n;i++){
        sig[i]=sigTemp[i-1];
    }
    for(i=0;i<n+1;i++){
        printf("\nSig[%d] = %lf\n",i,sig[i]);   
    }
    cSCoeffCalc(n,h,sig,y,a,b,c,d);
    printf("The equations of cubic interpolation polynomials between the successive intervals are:\n\n");
    for(i=0;i<n;i++){
        printf("P%d(x) b/w [%lf,%lf] = %lf*(x-%lf)^3+%lf*(x-%lf)^2+%lf*(x-%lf)+%lf\n",i,x[i],x[i+1],a[i],x[i],b[i],x[i],c[i],x[i],d[i]);
    }
     
     
}