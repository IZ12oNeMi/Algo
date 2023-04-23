//3. 利用动态规划算法求 X=abcbdb，Y=acbbabdbb 最长公共子序列问题。    

#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string>
#include <algorithm>//max函数的头文件
#include <ctime> //生成随机
using namespace std;

#define Max 100
/* 
1.设立一个全局变量二维数组longest[][]，用来储存A，B两个字符串到第i个和第j个的最长子序列
2.将第一个字符串的每一个位置分别与第二个字符串的每一个位置进行比较
（1）第i个等于第j个，longest[i][j]=longest[i-1][j-1]+1
（2）第i个不等于第j个，longest[i][j]=max(longest[i-1][j],longest[i][j-1])
（3）i或者j=0时,所对应的所有longest[][]值都为0
 */

int longest[Max][Max];
int label[Max]={0};

int main(void)
{
    string A="abcbdb";
    string B="acbbabdbb";

    for(int i=0;i<=A.length();i++)
        longest[i][0] = 0;
    for(int i=0;i<=B.length();i++)
        longest[0][i] = 0;

    for(int i=1;i<=A.length();i++)
    {
        for(int j=1;j<=B.length();j++)
        {
            if(A[i-1] == B[j-1])
            {
                longest[i][j] = longest[i-1][j-1] + 1;
                /* if(longest[i][j]>longest[i-1][j-1] && label[i-1] != 1)
                    label[i-1]=1; */
            }
                
            else
                longest[i][j] = max(longest[i-1][j], longest[i][j-1]);
        }
    }
    cout<<"The longest subsequence is:"<<longest[A.length()][B.length()]<<endl;


    system("pause");
    return 0;
}