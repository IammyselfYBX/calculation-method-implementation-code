/*
 * 固定边界条件的三次样条插值
 *
 * 编写程序，对给定的 n 个插值节点 (x1,y1),(x2,y2),⋯,(xn,yn) 进行三次样条插值，
 * 并对于给定的 m 个待求节点 x1,x2,⋯,xm 计算其三次样条插值函数值 y1,y2,⋯,ym 。
 * 其中，边界条件取自然边界条件 S′′(x1)=S′′(xn)=0。
 * 由于不能预先知道插值节点个数和待求节点的个数，请使用malloc函数申请诸数组，并在使用完毕后使用free函数释放。
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point{
    double x;
    double y;
}Point;

double cubicSpline(long n, struct Point *points, double xs, double *h, long location);
double compute(long n, struct Point *points, double *M, double xs, double *h, long loaction);
void ColEliminate(long n, double **A, double *b, double *x);
void swapRow(long n, long r, long k, double **A, double *b);
void partition(long n, struct Point *points, double *h);
void sort(long n, struct Point *points);
long findlocation(long n, struct Point *points, double xs);
void print_array(long n, double *array, char *name);
void print_points(long n, struct Point *points);
void print_matrix(double **Matrix, long m, long n);

int main(int argc, char *argv[]){
    printf("请输入插值节点的个数：");
    long n;
    scanf("%ld", &n);

    Point *points = (Point *) malloc (sizeof(Point) * (n + 1));

	double xs; // 待求节点的横坐标。
	double ys; // 待求节点的纵坐标。

    double h[n-1];
    partition(n, points, h);

    printf("请输入待求节点的横坐标：");
	scanf("%lf", &xs);
    long location = findlocation(n, points, xs);

    ys = cubicSpline(n, points, xs, h, location);
	printf("在%lf处利用固定边界条件的三次样条计算的结果：%lf\n", xs, ys);

    free(points);

}

double cubicSpline(long n, struct Point *points, double xs, double *h, long location){
    double * alpha = (double *) malloc (sizeof(double) * (n + 1));
    double *b = (double *) malloc (sizeof(double) * (n + 1));
    double * beta = (double *) malloc (sizeof(double) * (n + 1));
    double *c = (double *) malloc (sizeof(double) * (n + 1));
    double *M = (double *) malloc (sizeof(double) * (n + 1));

    // 这里自定义边界条件 一阶导与二阶导的值
    printf("请输入区间端点导数值 \n");
    printf("左端点的导数值 f'(%lf)：", points[0].x);
    double dy_left;
    scanf("%lf", &dy_left);
    printf("右端点的导数值 f'(%lf)：", points[n-1].x);
    double dy_right;
    scanf("%lf", &dy_right);

    // 对第一行单独赋值
    //alpha[0] = 0.0;
    b[0] = 2.0;
    beta[0] = 1.0;
    c[0] = 6.0 / h[0] * ((points[1].y - points[0].y) / h[0] - dy_left);

    for(long i = 1; i < n-1; i++){
        alpha[i] = h[i - 1] / (h[i - 1] + h[i]);
        b[i] = 2.0;
        beta[i] = h[i] / (h[i - 1] + h[i]);
        c[i] = (6.0 / (h[i-1] + h[i])) * ((points[i + 1].y - points[i].y) / h[i] - (points[i].y - points[i-1].y) / h[i-1]);
    }
    // 对最后一行单独赋值
    alpha[n-1] = 1.0;
    b[n-1]=2.0;
    //beta[n-1]=0.0;
    c[n-1]=6.0 / h[n-2] * (dy_right - (points[n-1].y - points[n-2].y) / h[n-2]);

    double **A = (double **) malloc (sizeof(double *) * n);
    for(long i = 0; i < n; i++){
        A[i] = (double *) malloc (sizeof(double) * n);
    }
    // 3对角矩阵赋值
 	for(long i = 1; i < n; i++)	    A[i][i - 1] = alpha[i];
 	for(long i = 0; i < n; i++)	    A[i][i] = b[i];
 	for(long i = 0; i < n-1; i++) 	A[i][i + 1] = beta[i];

    printf("系数矩阵A = \n");
    print_matrix(A, n, n);
    printf("常数项c = \n");
    print_array(n, c, "c");

    // 列主元消去法求解三对角矩阵
    ColEliminate(n, A, c, M);
    // 消元后的结果
    printf("消元后的结果：\n");
    print_matrix(A, n, n);
    printf("解向量M = \n");
    print_array(n, M, "M");
    // 带入样条插值公式
    return compute(n, points, M, xs, h, location);
    free(alpha);
    free(b);
    free(beta);
    free(c);
    free(M);
}

// 二分法查找待求点所在的区间
long findlocation(long n, struct Point *points, double xs)
{
    if (xs < points[0].x || xs > points[n - 1].x)
    {
        printf("要求的点不在已给的区间[%lf, %lf]内\n", points[0].x, points[n - 1].x);
        return -1;
    }

    long left = 0, right = n - 1, mid;
    while(left <= right){
        mid = (left + right) / 2;
        if(points[mid].x == xs) return mid;
        else if(points[mid].x < xs) left = mid + 1;
        else right = mid - 1;
    }
    return left;

}

/*
 * 计算 样条插值公式结果。
 *
 * 将解出的$M_j$代入下面的方程中，其中$x_j/x_{j+1}$表示区间端点，需要依次累加
 * \begin{equation}
 * \begin{aligned}
 * p_{j}(x) &= \frac{M_{j+1}}{6h_{j}}(x-x_j)^3
 *          &- \frac{M_{j}}{6h_{j}}(x-x_{j+1})^3 \\
 *          &+ \frac{1}{h_{j}}(y_{j+1} - \frac{M_{j+1}h_{j}^{2}}{6})(x-x_j)
 *          &- \frac{1}{h_{j}}(y_j-\frac{M_{j}h_{j}^2}{6})(x-x_{j+1}) \\
 *                              j=0, 1, \cdots, n-1
 * \end{aligned}
 * \end{equation}
*/
double compute(long n, struct Point *points, double *M, double xs, double *h, long location)
{
    // j 表示第j个
    //long j = ceil((xs - left) / h[0]);
    //long j = findlocation(n, points, xs);
    //if (-1 == j)
    //{
    //    return -1;
    //}else{
    //    printf("要找的元素在第 %ld个区间\n", j);
    //}
    long j = location-1;
    double xj = points[j].x;
    double xj1 = points[j + 1].x;
    double yj = points[j].y;
    double yj1 = points[j + 1].y;
    printf("要找的元素在第 %ld 个区间[%lf, %lf]\n", location, xj, xj1);
    return M[j] * pow(xj1 - xs, 3) / (6 * h[j])
           + M[j + 1] * pow(xs - xj, 3) / (6 * h[j])
           + (yj - M[j] * h[j] * h[j] / 6) * (xj1 - xs) / h[j]
           + (yj1 - M[j + 1] * h[j] * h[j] / 6) * (xs - xj) / h[j];
}

/*
 * 列主元高斯消去法 
 *  计算 AM=c 中的M 
*/
void ColEliminate(long n, double **A, double *b, double *x){
	for(long k = 0; k < n - 1; k++){
		long r = k;
		for(long i = k + 1; i < n; i++){
            // 找到第k列上 绝对值最大的行
			if(fabs(A[i][k]) > fabs(A[r][k])){
				r = i;
			}
		}

		if(r != k){
			swapRow(n, r, k, A, b);
		}

        // 消元
		for(long i = k + 1; i < n; i++){
			A[i][k] /= A[k][k];
			b[i] -= A[i][k] * b[k];
			for(long j = k + 1; j < n; j++){
				A[i][j] -= A[i][k] * A[k][j];
			}
			A[i][k] = 0;
		}
	}

	if( 0 == A[n - 1][n - 1]){
        printf("矩阵奇异，无法求解。\n");
        exit(0);
    }else{
        for(long i = n - 1; i >= 0; i--){
		    x[i] = 0;
		    for(long j = i + 1; j < n; j++){
			   x[i] += A[i][j] * x[j];
		    }
		    x[i] = (b[i] - x[i]) / A[i][i];
	    }
    }
}

/*
 * 交换矩阵 A 的第 r 行和第 k 行，
 * 向量 b 的第 r 个元素和第 k 个元素。
 */
void swapRow(long n, long r, long k, double **A, double *b){
	double tmp;

	for(long i = 0; i < n; i++){
		tmp = A[r][i];
		A[r][i] = A[k][i];
		A[k][i] = tmp;
	}

	tmp = b[r];
	b[r] = b[k];
	b[k] = tmp;

	return;
}

/*
 * 将 n + 1 个节点的横坐标存入数组 points 中。
 * 并计算相邻两个元素之差 h 的值。
 */
void partition(long n, struct Point *points, double *h){
    printf("请输入插值节点的横坐标和纵坐标(中间用' '隔开)\n");
    for(long i = 0; i < n; i++){
        printf("请输入第%d个节点的横坐标和纵坐标(x[%ld] y[%ld])：", i + 1, i , i );
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
    printf("排序前的结果：\n");
    print_points(n, points);
    // 对输入完的结果进行排序
    sort(n, points);
    printf("排序后的结果：\n");
    print_points(n, points);

    // 计算h的值
    for(long i = 0; i < n; i++){
        h[i] = points[i + 1].x - points[i].x;
    }
    print_array(n-1, h, "h");
    return;
}

void print_points(long n, struct Point *points){
    for(long i = 0; i < n; i++){
        printf("(%lf, %lf) ", points[i].x, points[i].y);
    }
    printf("\n");
}

void print_array(long n, double *array, char* name){
    for(long i = 0; i < n; i++){
        printf("%s[%ld] = %lf ",name, i, array[i]);
    }
    printf("\n");
}

void print_matrix(double **Matrix, long m, long n)
{
    long i, j;
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
            printf("  %lf ", Matrix[i][j]);
        printf("\n");
    }
}

// 以x为参考，从小到大排序
// 这里使用冒泡排序
void sort(long n, struct Point *points){
    for(long i = 0; i < n; i++){
        for(long j = i + 1; j < n; j++){
            if(points[i].x > points[j].x){
                struct Point tmp = points[i];
                points[i] = points[j];
                points[j] = tmp;
            }
        }
    }
}