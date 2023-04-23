/* 设 a1, a2,…, an 是集合{1, 2, …, n}的一个排列，如果 i<j 且 ai>aj，则序偶
(ai, aj)称为该排列的一个逆序。例如，2, 3, 1 有两个逆序：(3, 1)和(2, 1)。设计
分治算法，统计给定排列 {8, 5, 7, 2, 1, 9, 6, 3, 4} 中逆序的个数，输出所有逆
序。 */

#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string>
using namespace std;

int Reserved_ex(int *a,int n)//穷举法求逆序,O(n^2)
{
    int count=0;

    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(a[i]>a[j])
            {
                count++;
                cout<<"("<<a[i]<<","<<a[j]<<")\t";
            }
            
        }
    }
    cout<<endl;
    return count;
}

void Merge(int *a,int l,int mid,int h,int &count)//合并目前区域
{
    int i=l,j=mid+1;

    int *temp=new int[h-l+1];
    int k=0;//为temp数组的计数器

    while(i<=mid && j<=h)
    {
        if(a[i]<=a[j])
        temp[k++]=a[i++];
        else
        {
            count+=mid-i+1;
            for(int m=i;m<=mid;m++)
            cout<<"("<<a[m]<<","<<a[j]<<")\t";
            temp[k++]=a[j++];
        }
    }
    while(i<=mid)
    temp[k++]=a[i++];
    while(j<=h)
    temp[k++]=a[j++];

    for(int i=l,k=0;i<=h;i++,k++)
        a[i]=temp[k];

    delete []temp;

}

void Reserved_Merge(int *a,int l,int h,int &count)//归并算法求逆序及个数
{
    if(l>=h)
    return;
    int mid=l+(h-l)/2;
    Reserved_Merge(a,l,mid,count);
    Reserved_Merge(a,mid+1,h,count);
    Merge(a,l,mid,h,count);
}

int main()
{
    int a[9]={8, 5, 7, 2, 1, 9, 6, 3, 4};
    //int n=Reserved_ex(a,9);
    //cout<<"Total: "<<n<<endl;
    int count=0;
    Reserved_Merge(a,0,8,count);
    cout<<endl;
/*     for(int i=0;i<9;i++)
    cout<<a[i]<<" ";
    cout<<endl; */
    cout<<"Total: "<<count<<endl;
    system("pause");
    return 0;
}