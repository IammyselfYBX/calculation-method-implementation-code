/******三次样条插值，边界条件为给定两个端点的一阶导数值*************/
#include<stdio.h>
#include <math.h>
#define N 4
double zhuigan(double m[N+1],double b2[N-1],double a[N+1])   //返回数组m
{
	int i,j;
	double A[N-1][N-1],L[N-1][N-1],U[N-1][N-1],a1[N-1],b1[N-2],y[N-1];
	for(i=0;i<N-1;i++)                     //输入系数矩阵
	{
		for(j=0;j<N-1;j++)
		{
			if(i==j)
			{
				A[i][j]=2;
			}
			else if(j==i+1)
			{
				A[i][j]=a[i+1];
			}
			else if(i>=1&&j==i-1)
			{
				A[i][j]=1-a[i+1];
			}
			else
				A[i][j]=0;
		}
	}
	for(i=0;i<N-1;i++)
	{
		for(j=0;j<N-1;j++)
		{
			printf("%lf\t",A[i][j]);
			if(j==N-2)
				printf("\n");
		}
	}
	a1[0]=A[0][0];
	for(i=0;i<N-2;i++)
	{
		b1[i]=A[i][i+1]/a1[i];
		a1[i+1]=A[i+1][i+1]-A[i+1][i]*b1[i];
	}
	for(i=0;i<N-1;i++)
	{
		for(j=0;j<N-1;j++)
		{
			if(i==j)
				L[i][j]=a1[i];
			else if(j==i-1)
				L[i][j]=A[i][j];
			else
				L[i][j]=0;
		}
	}
	printf("输出下三角矩阵\n");
	for(i=0;i<N-1;i++)
	{
		for(j=0;j<N-1;j++)
		{
			printf("%lf\t",L[i][j]);
			if(j==N-2)
				printf("\n");
		}
	}
	for(i=0;i<N-1;i++)
	{
		for(j=0;j<N-1;j++)
		{
			if(i==j)
				U[i][j]=1;
			else if(j==i+1)
				U[i][j]=b1[i];
			else
				U[i][j]=0;
		}
	}
	printf("输出上三角矩阵\n");
	for(i=0;i<N-1;i++)
	{
		for(j=0;j<N-1;j++)
		{
			printf("%lf\t",U[i][j]);
			if(j==N-2)
				printf("\n");
		}
	}
	printf("\n");
	//解下三角方程组Ly=b
	y[0]=b2[0]/L[0][0];
	for(i=1;i<N-1;i++)
	{
		y[i]=(b2[i]-L[i][i-1]*y[i-1])/L[i][i];
	}
	
	for(i=0;i<N-1;i++)
		printf("%lf\t",y[i]);
	printf("\n");
	//解上三角方程组Ux=y
	m[N-1]=y[N-2];
	for(i=N-2;i>=1;i--)
	{
		m[i]=y[i-1]-U[i-1][i]*m[i+1];
	}
	return 0;
}
double S(double x_,double x[],double y[],double m[])
{
	int i;
	double s;
	for(i=0;i<N;i++)
	{
		if(x_>=x[i]&&x_<=x[i+1])
			break;
		else
			;
	}
	s=(1+2*(x_-x[i])/(x[i+1]-x[i]))*pow(((x_-x[i+1])/(x[i]-x[i+1])),2)*y[i]+(1+2*(x_-x[i+1])/(x[i]-x[i+1]))*pow(((x_-x[i])/(x[i+1]-x[i])),2)*y[i+1]+(x_-x[i])*pow(((x_-x[i+1])/(x[i]-x[i+1])),2)*m[i]+(x_-x[i+1])*pow(((x_-x[i])/(x[i+1]-x[i])),2)*m[i+1];
	return s;

}
void main()
{
	int i;
	double x[N+1],y[N+1],a[N+1],b[N+1],m[N+1],h[N],b2[N-1],s,x_;
	m[0]=2.125;m[N]=-2.375;
	printf("请输入插值点及其对应的函数值");                   //可进行交互输入
	for(i=0;i<N+1;i++)
	{
		scanf("%lf%lf",&x[i],&y[i]);
	}
	printf("请输入边界条件，即边界点的一阶导");     
	scanf("%lf%lf",&m[0],&m[N]);     
	for(i=0;i<N;i++)
	{
		h[i]=x[i+1]-x[i];
	}
	for(i=1;i<N;i++)
	{
		a[i]=h[i-1]/(h[i-1]+h[i]);
		b[i]=3*((1-a[i])/h[i-1]*(y[i]-y[i-1])+a[i]*(y[i+1]-y[i])/h[i]);
	}
	b2[0]=b[1]-(1-a[1])*m[0];
	b2[N-2]=b[N-1]-a[N-1]*m[N];
	for(i=1;i<N-2;i++)
	{
		b2[i]=b[i+1];
	}
/*	for(i=0;i<N-1;i++)
		printf("%lf\t",b2[i]);  */         //输出部分右端项
	printf("\n");
	printf("输出三对角矩阵\n");
	zhuigan(m,b2,a);
	for(i=0;i<N+1;i++)
		printf("%lf\t",m[i]);
	printf("\n");
	printf("请输入近似点");
	scanf("%lf",&x_);
	s=S(x_,x,y,m);
	printf("近似值为%lf",s);
	printf("请输入近似点");
	scanf("%lf",&x_);
	s=S(x_,x,y,m);
	printf("近似值为%lf",s);
}
