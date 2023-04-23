/*  整数划分问题。将正整数 n 表示成一系列正整数之和：n=n1+n2+…+nj，其中
n1≥n2≥…≥nj≥1，j≥1。正整数 n 的这种表示称为正整数 n 的划分。求正整数 n 的不
同划分个数。 例如正整数 6 有如下 11 种不同的划分：
6；
5+1；
4+2，4+1+1；
3+3，3+2+1，3+1+1+1；
2+2+2，2+2+1+1，2+1+1+1+1；
1+1+1+1+1+1。
 */

#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string>
using namespace std;

/* 
1.采用减治递归算法，设置全局变量count
2.函数入口设置当前值和目标值
3.采用循环算法，从小到大
4.设置前置条件，每次循环次数小于等于目标值减当前值
5.没有达到当前值则递归，达到了当前值则停止递归，计数加一
6.避免因为元素个数种类相同，但因位置不同而重复计数
*每次重复元素只能大于等于当前值
 */

int count=0;

void Division(int goal,int current,int start)//目标数，当前总值，当前元素值
{
    int n=goal-current;

    for(int i=start;i<=n;i++)
    {
        if(current+i==goal)
        count++;
        else if(current+i<goal)
        Division(goal,current+i,i);
        else
        break;
    }
}

int main()
{
    Division(6,0,1);
    cout<<count<<endl;
    system("pause");
    return 0;
}