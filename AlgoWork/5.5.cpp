/* 给定一个有 n（n≥1）个整数的序列，利用动态规划法求其中最大连续子序列的和。 例如序列（-2，11，-4，13，
-5，-2）的最大子序列和为 20 */

#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string>
#include <algorithm>//max函数的头文件
#include <ctime> //生成随机
#include <vector>
using namespace std;

/* 
1.设置一个一维的全局变量maxsum[],他代表前面i个连续子序列和的最大值
2.设置一个全局变量MAX记录当前以自己结尾的连续子序列的最大和，Index记录连续子序列的最大和的末尾索引
3.子问题(第一个数的maxsum值为他自己)
（1）最大值为他自己
（2）最大值为它自己和上一序列的和
4.获取连续子序列，从末尾索引开始，用最大和依次减去前一个数的值，直到恰好为0停止向前
 */

#define N 20 
int maxsum[N]; //他代表前面i个连续子序列和的最大值
int MAX=0; //记录当前连续子序列的最大和
int Index=0;  //Index记录连续子序列的最大和的末尾索引

int main(void)
{
    int seq[6] = {-2,11,-4,13,-5,-2};
    maxsum[0]=seq[0];
    MAX=maxsum[0];

    //求前面i个连续子序列和的最大值
    for(int i=1;i<6;i++)
    {
        maxsum[i]=max(seq[i],maxsum[i-1]+seq[i]);
        if(maxsum[i]>MAX)
        {
            MAX=maxsum[i];
            Index=i;
        }
    }


    // 输出
    cout<<"the highest value of subsequence is:"<<MAX<<endl;
    
    vector<int> h;
    int total=MAX;
    for(int i=Index;i>=0;i--)
    {
        h.insert(h.begin(),seq[i]);
        total -= seq[i];
        if(total == 0)
            break;
    }
    cout<<"{";
    for(int it=0;it<h.size()-1;it++)
        cout<<h[it]<<",";
    cout<<h[h.size()-1];
    cout<<"}"<<endl;
    system("pause");
    return 0;
}