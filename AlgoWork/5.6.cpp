/* 利用动态规划法求将正整数 n 无序拆分成最大数为 k（称为 n 的 k 拆分）的拆分方案个数，要求所有的拆分方
案不重复。例如，设 n=5，k=5，对应的拆分方案有：
① 5=5
② 5=4+1
③ 5=3+2
④ 5=3+1+1
⑤ 5=2+2+1
⑥ 5=2+1+1+1
⑦ 5=1+1+1+1+1*/

#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string>
#include <algorithm>//max函数的头文件
#include <ctime> //生成随机

using namespace std;

#define N 10

/* 
1.设置一个二维的全局变量Sum[n][k],用于记录正整数n的最大拆分数为k的拆分方案
2.对于所有的Sum[][]都有
（1）n为0或k为0，值为0
（2）n为1或k为1，值为1
（3）k>n,Sum[n][k] = Sum[n][n]
（4）k=n,Sum[n][k] = Sum[n][k-1] + 1
（5）对于其他情况，Sum[n][k] = Sum[n-k][k] + Sum[n][k-1] 可以简单理解为包含k在内的拆分方案和k不在内的拆分方案
3.采用两层递归填满数组
 */

int Sum[N+1][N+1];

int main()
{
    //初始化边界
    for(int i=0;i<=N;i++)
        Sum[i][0]=0;
    for(int i=0;i<=N;i++)
        Sum[0][i]=0;
    for(int i=1;i<=N;i++)
        Sum[i][1]=1;
    for(int i=1;i<=N;i++)
        Sum[1][i]=1;

    int n = 5;

    for(int i=2;i<=n;i++)
    {
        for(int k=2;k<=n;k++)
        {
            if(k<i)
                Sum[i][k]=Sum[i-k][k] + Sum[i][k-1];
            else if(k==i)
                Sum[i][k]=Sum[i][k-1]+1;
            else
                Sum[i][k]=Sum[i][i];
        }
    }
    cout<<"n=5,k=5,the number of means is:"<<Sum[n][n]<<endl;
    system("pause");
    return 0;
}