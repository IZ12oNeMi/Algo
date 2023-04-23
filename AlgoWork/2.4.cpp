/* 假设在文本“ababcabccabcacbab”中查找模式“abcac”, 写出分别采用 BF 算法
和 KMP 算法编写程序来观察串匹配过程 */
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string>
using namespace std;

int nextval[255]={0};//定义nextval数组

int BF(string S,string Q)//BF算法
{
    int i=0,j=0;//分别为主串和子串的比较位置
    while(i<S.length() && j<Q.length())
    {
        if(S[i]==Q[j])
        {
            i++;
            j++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }

    if(j>=Q.length())
    return i-Q.length()+1;
    else
    return 0;
}

void GetNextval(string Q, int nextval[])//获取nextval数组的值
{
    int i=1;//待比较位置
    int j=0;//被比较位置
    nextval[1]=0;

    while(i<=Q.length())
    {
        if(j==0 || Q[i-1]==Q[j-1])
        {
            i++;
            j++;
            if(Q[i-1]==Q[j-1])
            {
                nextval[i]=nextval[j];
            }
            else
            nextval[i]=j;
        }
        else
        j=nextval[j];
    }
}

int KMP(string S, string Q)//KMP算法
{
    int i=1,j=1;//分别对应主串和子串的位置；
    while(i<=S.length() && j<= Q.length())
    {
        if(j==0 || S[i-1]==Q[j-1])
        {
            i++;
            j++;
        }
        else
        j=nextval[j];
    }
    if(j>Q.length())
    return i-Q.length();
    else
    return 0;
}


int main()
{
    string S="ababcabccabcacbab";
    string Q="abcac";
    GetNextval(Q,nextval);
    cout<<KMP(S,Q)<<endl;
    cout<<BF(S,Q)<<endl;
    system("pause");
    return 0;
}