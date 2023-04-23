/* 3. 插入法调整堆。已知（k1, k2,…, kn）是堆，设计算法将（k1, k2, …, kn ,kn+1）调整为堆（假
设调整为大根堆）。 */
#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string>
#include <algorithm>
using namespace std;

/* 
1.原来的n个元素已经为大根堆，先将原来n个元素用调整的堆的方法置为大根堆
2.将待插入新的结点从根节点开始比较直到找到合适位置，插入，调整堆。
3.建立三个函数，分别为堆调整，堆建立，堆插入
4.堆调整，堆建立代码可参考堆排序算法，只需要简单的做下改变
5.堆插入算法，需要与结点比较，先插入到队尾，与父节点依次比较。
 */

void adjust(int a[],int n,int index)//堆调整算法
{
    int i=2*index+1;
    int j=2*index+2;//记录该结点的左右孩子
    int maxin=index;//先将该节点本身设为最大值结点

    if(i<n && a[i]>a[maxin])//当还有左右孩子且左右孩子比当前值大时，做调整
        maxin=i;
    if(j<n && a[j]>a[maxin])
        maxin=j;
    
    if(maxin!=index)
    {
        swap(a[index],a[maxin]);
        adjust(a,n,maxin);
    }
}

void buildheap(int a[],int n)//建堆算法
{
    for(int i=n/2-1;i>=0;i--)//从最后一个非叶子结点到根节点，依次调整堆
        adjust(a,n,i);
}

int* insertheap(int a[],int n,int num)//插入堆算法
{
    int *temp=new int[n+1];
    
    for(int i=0;i<n;i++)
        temp[i]=a[i];

    temp[n]=num;//将待插入数放至数组末尾

    int child=n;
    int parent=(n-1)/2;//记录当前结点和他的双亲结点

    while(child>0 && parent>=0)//孩子节点一定要有父节点，双亲结点一定不能小于0
    {
        if(temp[parent]>=num)//如果父节点已经大于等于num值，则num可以被插在这里
        break;
        else
        {
            temp[child]=temp[parent];//交换父亲孩子的位置
            child=parent;
            parent=(child-1)/2;
        }
    }
    temp[child]=num;//将num插入最后的孩子值处
    return temp;
}

int main()
{
    int a[10]={6,2,4,9,1,3,10,7,5,8};
    buildheap(a,10);
    for(int i=0;i<10;i++)
    cout<<a[i]<<" ";
    cout<<endl;
    int *b=insertheap(a,10,9);
    for(int i=0;i<=10;i++)
    cout<<b[i]<<" ";
    cout<<endl;
    delete []b;
    system("pause");
    return 0;
}