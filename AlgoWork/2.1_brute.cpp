#include <iostream>
using namespace std;

void Swap(int *arr,int i,int j);

int main()
{
    int a[15]={2,3,1,2,3,3,2,2,1,1,3,2,1,3,1};
    //设置两个数组索引指针一个在开头，一个在结尾
    int i=0,j=14;
    int flag1=0,flag2=0; //设置前后调用完成标志

    while(i<j && !flag1 && !flag2 )//当开头指针小于结尾指针的时候进行循环,默认结束的时候中间已有一个2
    {
        while(a[i]==2)//将2放到中间
        {
            if(a[i+1]==2 && a[i+2]==2)//后两位均为2，默认为2都已经放到中间了
            {
                flag1=1;
                break;
            }
            else if(a[i+1]==2)//如果前后均为2，则与后两位数进行交换
                Swap(a,i,i+2);
            else
                Swap(a,i,i+1);//都不满足，则将2向后移动
        }

        while(a[i]==1)//当前指针所指元素已经为1了，则头指针向后移动一位
            i++;

        while(i<j && a[j]==2)//将2放在中间，道理同前
        {
            if(a[j-1]==2 && a[j-2]==2)//如果前后均为2，则与后两位数进行交换
            {
                flag2=1;
                break;
            }
            else if(a[j-1]==2)//前两位均为2，默认为2都已经放到中间了
                Swap(a,j,j-2);
            else
                Swap(a,j,j-1);//都不满足，则将2向前移动
        }

        while(a[j]==3 && i<j-1)//当前指针所指元素已经为3了，则头指针向前移动一位
            j--;

        if( i<j && a[i]!=2 && a[j]!=2 && !flag1 && !flag2)//当满足条件且头尾指针指向元素均不为2时，交换这两个元素
            Swap(a,i,j);
        //当其中一边已经完成排序另一边还没有完成时，将一边的2与另一边的值互换
        else if(i<j && flag1) 
        {
            Swap(a,i,j);
            i++;
        }
        else if(i<j && flag2)
        {
            Swap(a,i,j);
            j--;
        }
    }
    for(int i=0;i<15;i++)
    cout<<a[i]<<" ";
    cout<<endl;
    system("pause");
    return 0;
}

void Swap(int *arr,int i,int j)//交换数组中元素的算法
{
    int temp=arr[i];//一个暂时储存的媒介
    arr[i]=arr[j];
    arr[j]=temp;
}