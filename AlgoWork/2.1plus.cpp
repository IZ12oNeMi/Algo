/* 给定一个包含数字 1，2，3 的数组：{2，3，1，2，3，3，2，2，1，1，3，
2，1，3，1}，请把数字 1 放在数组左边，数字 3 放到数组右边，数字 2 位于
数组中间。 要求设计一个空间复杂度为 O(1)、时间复杂度为 O(n)的算法 */
#include <iostream>
using namespace std;

void Swap(int *arr,int i,int j)
{
    int temp=arr[i];//一个暂时储存的媒介
    arr[i]=arr[j];
    arr[j]=temp;
}

int main()
{
    int a[15]={2,3,1,2,3,3,2,2,1,1,3,2,1,3,1};
    int index=0;
    for(int i=0;i<15;i++)
    {
        if(a[i]==1)
        {
            Swap(a,index,i);
            index++;
        }   
    }
    for(int i=index;i<15;i++)
    {
        if(a[i]==2)
        {
            Swap(a,index,i);
            index++;
        }   
    }
    cout<<'{';
    for(int i=0;i<14;i++)
    cout<<a[i]<<",";
    cout<<a[14]<<'}';
    cout<<endl;
    system("pause");
    return 0;
}