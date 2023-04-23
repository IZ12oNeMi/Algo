/* 1. 随机生成一高 20 层的数塔，分别用枚举法和动态规划法求解最大路径和，比较两种方法消耗时间的差异。
 */
#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string>
#include <algorithm>//max函数的头文件
#include <ctime> //生成随机
using namespace std;

/* 
1.数塔的生成：需要一个二维数组，数组大小为层数，随机生成使用rand（）函数生成每个位置的数字
2.生成过程需要两层循环，每一层循环生成当前循环层数的次数
3.蛮力法求解：
（1）每一层的每个节点对应的下一层都有两个分支，采用递归的方式
（2）需要四个全局变量，一个记录当前路径值，一个记录所有的路径值，另两个待一层线路完成后记录当前最大值层数的索引和最大值
4.动态规划法：
（1）从数塔底部向上选择，为上一层的每一个结点选择一个最大的子节点，依次类推，直到顶点。
（2）需要设立一个与数塔规模一致的数组，记录各个位置的结点到数塔尾部的最大值
（3）当每个点都记录完成后，从上至下输出，需要比较下一层的两个点哪一个点加上它自身的值等于当前层所记录的最大节点值
 */
#define maxlay 20  //层数
#define maxroute 524589 //路线最大值,必须大于等于2^(层数减一)
int Data[maxlay][maxlay];//记储存数塔
int maxnum[maxlay][maxlay];//动态规划法储存最大值

void Dynamic()
{
    cout<<"This is the Dynamic method!"<<endl;
    //先为maxnum数组赋值
    for(int i=0;i<maxlay;i++)//先给最后一层附上初值
        maxnum[maxlay-1][i]=Data[maxlay-1][i];

    for(int i=maxlay-2;i>=0;i--)//给从第一层到倒数第二层附上最大值
        for(int j=0;j<=i;j++)
            maxnum[i][j]=max(maxnum[i+1][j],maxnum[i+1][j+1])+Data[i][j];//从下层和他相邻的两个数中选一个更大的值

    //根据赋值的情况进行输出
    cout<<"the biggest sum is:"<<maxnum[0][0]<<endl;
    cout<<"the path is:";
    cout<<Data[0][0]<<"->";
    int row=0,col=0;
    while(row<maxlay-2)
    {
        if(maxnum[row][col] == Data[row][col] + maxnum[row+1][col])
        {
            cout<<Data[row+1][col]<<"->";
            row++;
        }
        else
        {
            cout<<Data[row+1][col+1]<<"->";
            row++;
            col++;
        }
    }
    if(maxnum[row][col] == Data[row][col] + maxnum[row+1][col])
            cout<<Data[row+1][col];

    else
        cout<<Data[row+1][col+1];
    
    cout<<endl;
}

int current[maxlay];//记录目前路径
int Paths[maxroute][maxlay];//记录全部路径
int Max=0;//记录最大值
int Index=0;//记录当前值索引
int Maxin=0;//记录最大值索引

void Brute_Force(int row, int col,int value)
{
    if(row<maxlay-1)//当还没有递归到最后一行时
    {
        //对当前数字加值，记录路径
        value += Data[row][col];
        current[row] = Data[row][col];

        //对下行两个数值进行递归
        Brute_Force(row+1,col,value);
        Brute_Force(row+1,col+1,value);

    }
    else //已经递归到最后一行
    {
        //先记录数值和路径
        value += Data[row][col];
        current[row] = Data[row][col];

        for(int i=0;i<maxlay;i++)
            Paths[Index][i]=current[i];

        //与目前最长路径作比较
        if(value > Max)
        {
            Max = value;
            Maxin = Index;
        }

        Index++;//记录全部路径索引+1
    }
}

int main(void)
{
    clock_t start_time1, end_time1,start_time2, end_time2;
    
    srand((int)(time(NULL)));
    for(int i=0;i<maxlay;i++)
        for(int j=0;j<=i;j++)
            Data[i][j]=rand()%15+1;//设置每个数最大值为15

    cout<<"print the number tower:"<<endl;
    
    for(int i=0;i<maxlay;i++)
    {
        for(int j=0;j<=i;j++)
        {
            cout<<Data[i][j]<<"\t";
        }
        cout<<endl;
    }
    //动态法的时间
    start_time1 = clock();   //获取开始执行时间
    Dynamic(); 
    end_time1 = clock();     //获取结束时间
    double Times1 = (double)(end_time1 - start_time1) / CLOCKS_PER_SEC;
    cout<<"Toatl time1:"<<Times1<<endl;

    //蛮力法的时间
    cout<<"This is the Brute Force method!"<<endl;
    start_time2 = clock();   //获取开始执行时间
    Brute_Force(0,0,0);
    cout<<"the biggest sum is:"<<Max<<endl;
    cout<<"the path is:";
    for(int i=0;i<maxlay-1;i++)
    cout<<Paths[Maxin][i]<<"->";
    cout<<Paths[Maxin][maxlay-1]<<endl;
    end_time2 = clock();     //获取结束时间
    double Times2 = (double)(end_time2 - start_time2) / CLOCKS_PER_SEC;
    cout<<"Toatl time:"<<Times2<<endl;
    system("pause");
    return 0;
}