/* 1. 利用贪心法求解 30 个城市的 TSP 问题。给出算法思想、算法伪代码和结果
截图。城市坐标如下：
{41,94},{37,84},{54,67},{25,62},{7,64},{2,99},{68,58},{71,44},{54,62},{83,69} ，
{64,60},{18,54},{22,60},{83,46},{91,38},{25,38},{24,42},{58,69},{71,71},{74,78} ，
{87,76},{18,40},{13,40},{82,7},{62,32},{58,35},{45,21},{41,26},{44,35},{4,50} */

#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string>
#include <algorithm>//max函数的头文件
#include <ctime> //生成随机
using namespace std;

/* 
1. 建立一个全局的二维数组储存每两个城市间的距离 dis[][]（需要将城市坐标进行转换）
2. 设置一个标记数组，走过的城市标记为1，没有走过的城市标记为0，visit[]
3. 贪心思想：每次从一个城市出发选择在没有标记的城市里离它最近的一个城市
4. 设置一个一维全局变量path[]保存路径，length记录路径长度
5. 优化方案：可以从每一个城市开头做一次贪心法的运算，选择长度最短的路径总长，这时，path变为二维数组，length变为一维数组
 */
# define cnum 30

double dis[cnum][cnum];  // 储存两个城市间的距离
int visited[cnum] = {0}; // 标记数组
int path[cnum+1] = {0}; // 标记路径
int length = 0; // 路径总长
int N = 1;  //记录走过的城市 

void init() // 初始函数
{
    int X[cnum] = {41,37,54,25,7,2,68,71,54,83,64,18,22,83,91,25,24,58,71,74,87,18,13,82,62,58,45,41,44,4};
    int Y[cnum] = {94,84,67,62,64,99,58,44,62,69,60,54,60,46,38,38,42,69,71,78,76,40,40,7,32,35,21,26,35,50};

    for(int i=0;i<cnum;i++)
    {
        for(int j=0;j<cnum;j++)
        {
            dis[i][j] = sqrt((X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]));
        }
    }
}

void greedy_DFS(int start, int i) //贪心遍历
{
    if(N != cnum)
    {
        int min = 99999;
        int index = 0;
        for(int j = 0; j< cnum;j++)
        {
            if(visited[j] == 1)
            continue;
            else if(visited[j] == 0)
            {
                if(dis[i][j] < min)
                {
                    min = dis[i][j];
                    index = j;
                }
            }
        }
        path[N++] = index;
        length += min;
        visited[index] = 1;
        greedy_DFS(start, index);
    }
    else
    {
        path[cnum] = start;
        length += dis[i][start];
    }
}

void proceed()
{
    path[0] = 0;
    visited[0] = 1;
    greedy_DFS(0,0);
    cout<<"The path is:"<<endl;
    for(int i=0;i<cnum;i++)
    {
        cout<<path[i]<<"->";
    }
    cout<<path[cnum]<<endl;
    cout<<"The minimum length is :"<<length<<endl;
}

int main(void)
{
    init();
    proceed();
    system("pause");
    return 0;
}