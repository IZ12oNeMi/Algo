/* 在一个序列中出现次数最多的元素称为众数。请设计分治法寻找众数并分析
算法时间复杂度 */

#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string>
using namespace std;
#define MAX 15

void QuickSort(int *a,int l,int h)//快速排序，先将数组按大小有序化
{
    if(l<h)
    {
        int i=l,j=h,temp=a[l];
        while(i<j)
        {
            while(i<j && temp<a[j])
            j--;

            if(i<j)
            a[i++]=a[j];

            while(i<j && temp>a[i])
            i++;

            if(i<j)
            a[j--]=a[i];
        }
        a[i]=temp;
        QuickSort(a,l,i-1);
        QuickSort(a,i+1,h);
    }
}

int GetMed(int *a,int l,int h)//获取数组某一段的中位数
{
    return a[(l+h)/2];
}

void GetAmount(int *a,int med, int l, int h,int &l1,int &h1)//获取中位数的个数
{
    for(int i=0;i<=h;i++)//获得第一个中位数的位置
    {
        if(med!=a[l1])
        l1++;
        else
        break;
    }

    for(h1=l1+1;h1<=h+1;h1++)//获得最后一个中位数的位置
    {
        if(med!=a[h1])
        {
            h1--;
            break;
        }
    }
}

int mode[MAX]={0};//众数
int Index=0;//记录众数的索引
int amount=0;//众数的数量

void GetMode(int *a,int l,int h)//分治法获得众数
{
    int med=GetMed(a,l,h);
    int l1=0,h1=0;

    GetAmount(a,med,l,h,l1,h1);//取得当前第一个和最后一个中位数的位置

    if(amount==h1-l1+1)//如果当前众数数量比计算出的数量一致，则在众数表中添加当前中位数
    {
        mode[Index++]=med;
    }

    if(amount<h1-l1+1)//如果当前众数数量比计算出的数量少，则更新（索引归零，记录当前值）
    {
        amount=h1-l1+1;
        Index=0;
        mode[Index++]=med;
    }

    if(l1-l>=amount) //当前众数左边的数大于众数的个数，分治左边
        GetMode(a,l,l1-1);

    if(h-h1>=amount) //当前众数右边的数大于众数的个数，分治左边
        GetMode(a,h1+1,h);
}

int main(void)
{
    int a[15]={6,5,8,10,3,7,5,8,5,2,4,1,7,8,9};
    QuickSort(a,0,14);
    for(int i=0;i<15;i++)
    cout<<a[i]<<" ";
    cout<<endl;

    GetMode(a,0,14);
    cout<<"The Mode is: ";
    for(int i=0;i<Index;i++)
    cout<<mode[i]<<" ";
    cout<<endl;
    cout<<"Amount is: "<<amount<<endl;
    system("pause");
    return 0;
}