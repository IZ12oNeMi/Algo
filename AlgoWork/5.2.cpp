/* 2. 利用动态规划算法求解编辑距离问题。给定两个字符串，求由一个转成另一个所需的最少编辑操作次数。许可
的编辑操作包括将一个字符替换成另一个字符，插入一个字符，删除一个字符。例如将 kitten 一字转成 sitting：
1. sitten （k→s）
2. sittin （e→i）
3. sitting （→g） */

#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string>
#include <algorithm>//max函数的头文件
#include <ctime> //生成随机
using namespace std;

#define Max 100

/* 
1.设置一个全局变量，二维数组least[][]，用来储存A，B两个字符串第i个变到第j个所需的最少次数
2.每一次比较都可以用到前一次的基础
（1）如果第i个和第j个字符相等，least[i][j]=least[i-1][j-1]
（2）如果第i个和第j个字符不相等，least[i][j]=min(least[i-1][j-1]+1,least[i-1][j],least[i][j-1])
3.如果A，B两个字符串其中有一个长度为零，则最少变换次数另一个字符串的长度
 */

int least[Max][Max];

int main(void)
{
    string A="kitten";
    string B="sitting";

    //先分别各自设AB字符串为0，初始化
    for(int i=0; i<=A.length(); i++)
    least[i][0]=i;
    for(int i=0; i<=B.length(); i++)
    least[0][i]=i;

    //两层循环，分别遍历各自的长度，最后求出所需要的结果
    for(int i=1;i<=A.length();i++)
    {
        for(int j=1;j<=B.length();j++)
        {
            if(A[i-1] == B[j-1])
            {
                least[i][j] = least[i-1][j-1];
            }
            else
            {
                least[i][j]=min(least[i-1][j-1],min(least[i-1][j],least[i][j-1]))+1;
            }
        }
    }
    cout<<"The least change times is:"<<least[A.length()][B.length()]<<endl;

    system("pause");
    return 0;
}