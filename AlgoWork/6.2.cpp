/* 2. 设有 10 个顾客在一个银行窗口排队，他们各自业务所需的服务时间分别为{8,
13, 6, 9, 7, 4, 22, 3, 12, 15}分钟。应如何安排这 10 个顾客的服务次序，才能使
顾客总的等待时间最小？最小等待时间为多少？请给出算法思想、算法伪代
码及结果截图。
 */

#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string>
#include <algorithm>//max函数的头文件
#include <ctime> //生成随机
using namespace std;

/* 
1.让时间少的顾客排前面，排序问题
2.计算总等待时长
 */
#define N 10
int TiMe[N] = {8,13, 6, 9, 7, 4, 22, 3, 12, 15};

void quicksort(int a[], int l, int r)
{
    if(l<r)
    {
        int i = l, j = r;
        int temp = a[l];
        while(i<j)
        {
            while(i<j && a[j] > temp)
            j--;

            if(i<j)
            a[i++] = a[j];

            while(i<j && a[i] < temp)
            i++;

            if(i<j)
            a[j--] = a[i];
        }
        a[i] = temp;
        quicksort(a,l,i-1);
        quicksort(a,i+1,r);
    }
}

void init()
{
    quicksort(TiMe,0,9);
}

void proceed()
{
    int totalTiMe = 0;
    for(int i=0;i<N-1;i++)
        totalTiMe += TiMe[i]*(N-i-1);
    cout<<"The minimum of waiting TiMe is:"<<totalTiMe<<endl;
}

int main(void)
{
    init();
    proceed();
    system("pause");
    return 0;
}
