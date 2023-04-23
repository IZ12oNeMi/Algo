/* 4. 120 个硬币中有一枚是假币，不知其比真币轻还是重。你需要几次，能用天平将该假币
找出来？ */

#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string>
#include <algorithm>
#include <ctime> //生成随机
using namespace std;

/* 
1.采用分治法，每次将还需要继续比较的堆均分成两份，遇到奇数则拿出一个，
将剩下两堆进行比较，若剩下两堆重量相等，则单独拿出来那个为假币，若不等，则假币在其中的某一堆里
2.若最后剩下的两堆分别只有一枚币，则需标记其中一枚币，将它与任意一个确定不是假币的币在进行一次比较，若重量还是不相等则它为假币
3.使用随机数生成位置未知，重量未知的一枚假币。
 */

int Find=-1;//用于查找假币位置
int real=0;//记录一枚真币的位置
int Count=0;//用于记录一共比较的次数
int weigh(int a[],int l,int r)//称重量，如果两坨质量相等则返回1，否则返回0
{
    if(Find==-1)
    Count++;

    int mid =l+(r-l)/2;
    int Count1=0,Count2=0;
    for(int i=l;i<=mid;i++)
    Count1+=a[i];
    for(int i=mid+1;i<=r;i++)
    Count2+=a[i];
    if(Count1==Count2)
    return 1;
    else
    return 0;
}

void SearchFakeCoin(int a[],int n,int l,int r)//寻找假币
{
    if(n%2==1 && n>=5)//n为奇数时，先拿掉一个，再分堆比较，n只剩3枚币的时候单独计算
    {
        if(weigh(a,l,r-1))//如果质量相等,且如果任取其中一枚与假币质量相比不相等时，则被拿出来的那个币为假币，否则全部为真币
        {
            if(Find==-1)
            Count++;
            if(a[r]!=a[r-1])
                Find=r;//记录假币位置
        }
        else//质量不等，则假币在其中，将其分成两堆继续搜索
        {
            real=r;
            int mid=l+(r-1-l)/2;
            SearchFakeCoin(a,(n-1)/2,l,mid);
            SearchFakeCoin(a,(n-1)/2,mid+1,r-1);
        }
    }
    else if(n%2==0 && n>=4)//n为偶数且n为2枚的时候单独计算
    {
        if(weigh(a,l,r))//如果质量相等,则假币不在这一堆里
        {
            real=r;
        }
            
        else//质量不等，则假币在其中，将其分成两堆继续搜索
        {
            int mid=l+(r-l)/2;
            SearchFakeCoin(a,n/2,l,mid);
            SearchFakeCoin(a,n/2,mid+1,r);
        }
    }
    else if(n==3)
    {
        int i1=weigh(a,l,l+1);
        int i2=weigh(a,l+1,r);
        if(i1 && i2)//如果三个质量均相等，则都为真
        return;
        else if(!i1 && !i2) //中间和两边质量均不相等，则中间为假
        Find=l+1;
        else if(i1 && !i2)//中间和前面质量相等，则后面为假
        Find=r;
        else //否则，前面的为假
        Find=l;
    }
    else if(n==2)
    {
        if(weigh(a,l,r))//如果两个质量相等，则都为真
        return;
        else
        {
            if(Find==-1)
            Count++;
            if(a[r]==a[real])//则说明r为真币
            Find=l;
            else
            Find=r;
        }
    }

}

int main()
{
    int a[120]={0};
    for(int i=0;i<120;i++)
    a[i]=2;
    srand((int)time(NULL));
    int loc=rand()%120;//随机生成假币位置
    int b=rand()%2;//随机生成假币重量或为1或为3
    int wei;
    if(b==1)
    wei=3;
    else
    wei=1;

    a[loc]=wei;//将loc位置假币重置质量

    SearchFakeCoin(a,120,0,119);
    cout<<"The preset location is:"<<loc<<endl;
    cout<<"The found location is:"<<Find<<endl;
    if(Find==loc)//匹配成功则输出成功信息
    cout<<"Find the coin!"<<endl;
    else
    cout<<"failed";
    cout<<"Total times:"<<Count-1<<endl; 
    system("pause");
    return 0;
}