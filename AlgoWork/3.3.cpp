/*  一个射击运动员打靶，靶一共有 10 环，连开 6 枪打中 45 环的可能性有多少种? 注意，
每一枪最高 10 环，最低 0 环。 */

#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string>
using namespace std;

/* 
1.递归法，设置一个全局变量记录一共的次数
2.设置一个开枪计数器，每次递归时加一次，超过六次后停止递归，也放在形参入口
3.对于每一次循环，共有十一种情况，对于每一种情况都要向后参与递归
（可以设置一个判断条件，对于明显不能达成条件的情况可以提前结束）
4.设计一个计算目前总分的参数，放在形参入口，对于有形参+（<=10）的数=45时，次数+1
5.设置一个目标总分，放在形参入口
6.每次循环开始先判断条件，条件符合再继续往下执行
*额外的判断条件：当剩余次数*10<目标分数-目前分值时，提前结束。
 */

int count = 0;

void TargetPractice(int goal,int n,int score)//分别对应总分，剩余次数，目前分值
{
    if( n>0 && score<goal)//当剩余次数大于0且总分还小于目标分数时继续进行
    {
        if(n*10 < goal-score)//当剩余次数*10<目标分数-目前分值时，提前结束
            return;

        for(int i=0;i<=10;i++)//每一种情况遍历
        {
            if(i+score<goal)//当这次的成绩加上已有的分数仍小于目标成绩时，递归
                TargetPractice(goal,n-1,score+i);

            else if(i+score==goal)//正好相等则总次数纪录加一
                count++;
            
            else   //超过目标分数则停止循环
                break;
        }
    }
}

int main()
{
    TargetPractice(45,6,0);
    cout<<count<<endl;
    system("pause");
    return 0;
}