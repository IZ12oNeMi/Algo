/* 利用分治法（或减治法）求一个序列的全排列（所给序列无重复元素）。
如 1,2,3 三个元素的全排列为：
 1,2,3 
 1,3,2 
 2,1,3 
 2,3,1 
 3,1,2 
 3,2,1 */

#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string>
using namespace std;

/* 
1.设置减治法递归解决问题
2.函数入口设置为待排序数组，待排序数组元素个数
3.每一层函数遍历当前待排序数组里面的所有数组
4.当待排序数组个数不为1时，继续遍历
5.为1时，输出储存的所有临时元素，一个排列完成
6.每一次递归的时候，去除掉当前元素，组成新的临时数组
7.设置一个全局变量数组和数组索引储存每一次排列的临时组合
 */

int *storage;
int Index=0;

void FullPermulation(int a[],int n)
{
    if(n==1)
    {
        storage[Index]=a[0];
        for(int i=0;i<=Index-1;i++)
            cout<<storage[i]<<",";
        cout<<storage[Index]<<endl;
    }
    else if(n>1)
    {
        for(int i=0;i<n;i++)
        {
            storage[Index++]=a[i];//记录当前元素

            int temp=a[i];
            int *a1=new int[n-1];//储存其他元素的临时数组，防止栈溢出，使用堆内存
            int k=0;//临时数组的计数器
            for(int j=0;j<n;j++)
            {
                if(a[j]!=temp)
                a1[k++]=a[j];
            }
            FullPermulation(a1,n-1);
            delete []a1;//释放空间
            Index--;//当前层数遍历完后索引退一位
        }
    }
    else
    return;
}

int main()
{
    int a[4]={2,4,6,8};
    storage=new int[4];
    FullPermulation(a,4);
    delete []storage;
    system("pause");
    return 0;
}