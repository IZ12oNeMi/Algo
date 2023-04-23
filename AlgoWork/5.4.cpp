/* 4. 利用动态规划法求 0-1 背包问题的最优背包价值。有 n = 20 个物品，背包最大可装载 M = 878 Kg。物品重量和
价值分别如下：
W = {92 ,4 ,43 ,83 ,84 ,68 ,92 ,82 ,6 ,44 ,32 ,18 ,56 ,83 ,25 ,96 ,70 ,48 ,14 ,58}, 
V = {44 ,46 ,90 ,72 ,91, 40 ,75 ,35 ,8 ,54 ,78 ,40 ,77 ,15 ,61 ,17 ,75 ,29 ,75 ,63}。 */

#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string>
#include <algorithm>//max函数的头文件
#include <ctime> //生成随机
using namespace std;

#define N 20  //物品数量
#define Max 1000

/* 
1.设立全局变量二维数组maxval[][]，用来记录前面i件物品在背包容量为j的情况下最优的装法
2.设立两个循环，外层循环次数为商品数量，表示将每个商品在每种背包大小的情况下都试一试
，内层循环为背包容量的大小，表示每种大小下，放入前i个商品的最优价值
3.放入的过程中有两个子问题
（1）当背包目前载重量j小于物品重量w（i）时，放不进去，maxval[i][j]=maxval[i-1][j]
（2）当背包目前载重量j大于等于物品重量w（i）时，考虑是否要装入：
a.装入，则maxval[i][j]=maxval[i-1][j-w(i)]+v(i)
b.不装入，则maxval[i][j]=maxval[i-1][j]
con:需要对这两种情况比较大小，确定是装入还是不装入，装入则表示对之前的装法进行了一些更换，不装入则是不换
4.回溯法获取每个装入物品的位置（从尾向前回溯），需要单独这里一个标签数组标记被取走的物品：
（1）输入最大物品数量以及背包最大载重量（i，j）
a.如果maxval[i][j]=maxval[i-1][j],那么表示这个物品没有被装入，标记为0，回溯到（i-1，j）这种情况
b.如果maxval[i][j]=maxval[i-1][j-w(i)]+v(i)，并且j>=w(i),那么表示这个物品有被装入，标记为1，回溯到（i-1，j-w(i)）这种情况
5.最后输出maxval[i][j]以及所装入物品序号
 */

int maxval[N+1][Max]={0};
int label[N];
int W[N]= {92 ,4 ,43 ,83 ,84 ,68 ,92 ,82 ,6 ,44 ,32 ,18 ,56 ,83 ,25 ,96 ,70 ,48 ,14 ,58};
int V[N]= {44 ,46 ,90 ,72 ,91, 40 ,75 ,35 ,8 ,54 ,78 ,40 ,77 ,15 ,61 ,17 ,75 ,29 ,75 ,63};

void IsPicked(int i,int j)
{
    if(i>0)
    {
        if(maxval[i][j] == maxval[i-1][j])
        {
            label[i-1]=0;
            IsPicked(i-1,j);
        }
        else if(j >= W[i-1] && maxval[i][j] == maxval[i-1][j-W[i-1]]+V[i-1])
        {
            label[i-1]=1;
            IsPicked(i-1,j-W[i-1]);
        }
    }
    else
        return;
}
int main(void)
{
    int TW = 878; //背包重质量

    //求出每种情况下的最优解
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=TW;j++)
        {
            if(j<W[i-1])
                maxval[i][j]=maxval[i-1][j];
            else
                maxval[i][j]=max(maxval[i-1][j],maxval[i-1][j-W[i-1]]+V[i-1]);
        }
    }

    //回溯法标记被取出物品
    IsPicked(N,TW);

    // 输出
    cout<<"the highest value is:"<<maxval[N][TW]<<endl;
    cout<<"Items picked from:";
    for(int i=0;i<N;i++)
    {
        if(label[i]==1)
            cout<<"["<<i+1<<"]"<<" ";
    }
    cout<<endl;

    system("pause");
    return 0;
}
