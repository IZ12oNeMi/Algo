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
1.进阶版不采用一般的二分法，而是三分法，这样效率将会更高
2.三分法需要将硬币分为三堆，前两堆个数分别为n/3个，剩下的硬币为第三堆
3.取出前两堆进行比较，将会有三种情况，其中有两种情况可以先暂时合并
（1）两堆一样重，则假币在第三堆里面
（2）两堆不一样重，则需继续进行下一步
4.对于两堆不一样重的情况解法如下
（1）将两堆分别在分为原来个数的三分之一，即a,b,c,d,e,f四堆，即a,b,c来自原来的第一堆，d,e,f来自原来的第二堆
（2）将c,f两堆拿出来，交换b,e堆，即a,e放在一边称，d,b放在另一边称
（3）这时又分为了三种情况
1）两堆一样重，则假币在c,f堆里，将c,f堆各自再分成三份，递归。
2）两堆的重量关系没有发生变化，则假币在a,d堆里，后与上条同理。
3）两堆的重量关系发生了变化，则假币在b,e堆里，后与上条同理。
5.对于3的两种情况，当确定假币所在的堆数仍大于等于6时，都可以采用上面的方法进行递归
6.n<5时
（1）n=4时，分为1，1，2，两次比较，获知假币
（2）n=2时，一次比较，获知假币
7.需要设置全局变量：find，记录假币位置；real，记录一枚真币的位置；Count记录称重总次数
8.四个个函数，两个不同的称重函数，入口需要数组，起始点和终止点；寻找函数，入口需要数组，假币个数，起始点和终止点；
假币在前两堆的小函数，与假币在第三堆的函数不同.
9.对于一直在第三堆的情况，设置在总函数里：
（1）当n=2时，单独讨论，可以继续递归到n=1的情况
（2）当n=1时，假币就是它，让他与一枚真币比较输出轻重情况
10.使用随机生成函数生成假币的位置和重量，并打印
 */

int Find=-1;//用于查找假币位置
int real=0;//记录一枚真币的位置
int Count=0;//用于记录一共比较的次数

int weigh_1(int a[],int l,int r)//第一步称重量，如果前两坨质量相等则返回1，否则返回0,
{
    int trisector1 =l+(r-l+1)/3;//三等分点1
    int trisector2 =l+(r-l+1)/3+(r-l+1)/3;//三等分点2
    int Count1=0,Count2=0;
    for(int i=l;i<trisector1;i++)
    Count1+=a[i];
    for(int i=trisector1;i<trisector2;i++)
    Count2+=a[i];
    if(Count1>Count2)
    return 1;
    else if(Count1<Count2)
    return -1;
    else
    return 0;
    
}

int weigh_2(int a[],int l1,int r1,int l2,int r2)//第二步称重量，当第一步称重量称出两坨不相等时，交换部分再称一次,分别输入两次的开头和结尾
{

    int tri1_1=l1+(r1-l1+1)/3;
    int tri1_2=l1+(r1-l1+1)/3+(r1-l1+1)/3;
    int tri2_1=l2+(r2-l2+1)/3;
    int tri2_2=l2+(r2-l2+1)/3+(r2-l2+1)/3;
    int Count1=0,Count2=0;

    if(l1!=r1 || l2!=r2)
    {
        for(int i=l1;i<tri1_1;i++)//统计交换后A和D区域的和
        Count1+=a[i];
        for(int i=tri2_1;i<tri2_2;i++)
        Count1+=a[i];

        for(int i=tri1_1;i<tri1_2;i++)//统计交换后B和C区域的和
        Count2+=a[i];
        for(int i=l2;i<tri2_1;i++)
        Count2+=a[i];
    }
    else
    {
        Count1=a[l1];
        Count2=a[l2];
    }

    if(Count1>Count2)
    return 1;
    else if(Count1<Count2)
    return -1;
    else
    return 0;
}

void exchange_weigh(int a[],int l1,int r1,int l2 ,int r2,int prere)
{
    cout<<"The range of two piles is from "<<l1<<" to "<<r1<<" and from " <<l2<<" to "<<r2<<endl;
    int re=weigh_2(a,l1,r1,l2,r2);//记录第两次称重的结果
    if(Find==-1)
        Count++;
    int n=r1-l1+1;//计算现在剩余单堆的个数
    if(n>=3)//当n还大于等于3时，可以继续细分
    {
        if(re==0)//假币在第一或第二堆的第三部分里
        {
            int start1=l1+(r1-l1+1)/3+(r1-l1+1)/3;
            int end1=r1;
            int start2=l2+(r2-l2+1)/3+(r2-l2+1)/3;
            int end2=r2;
            cout<<"["<<Count<<"]"<<"The fake coin is in the third section."<<endl;
            exchange_weigh(a,start1,end1,start2,end2,prere);
        }
        else if(re==prere)//假币在第一或第二堆的第一部分里
        {
            int start1=l1;
            int end1=l1+(r1-l1+1)/3-1;
            int start2=l2;
            int end2=l2+(r2-l2+1)/3-1;
            cout<<"["<<Count<<"]"<<"The fake coin is in the first section."<<endl;
            exchange_weigh(a,start1,end1,start2,end2,re);
        }
        else//假币在第一或第二堆的第二部分里
        {
            int start1=l1+(r1-l1+1)/3;
            int end1=l1+(r1-l1+1)/3+(r1-l1+1)/3-1;
            int start2=l2+(r2-l2+1)/3;
            int end2=l2+(r2-l2+1)/3+(r2-l2+1)/3-1;
            cout<<"["<<Count<<"]"<<"The fake coin is in the second section."<<endl;
            if(re==1)
            re=-1;
            else if(re==-1)
            re=1;
            exchange_weigh(a,start1,end1,start2,end2,re);
        }
    }
    else if(n==2)//只剩两枚币的时候不能再继续划分
    {
        if(a[l1]==a[l2])
        {
            cout<<"["<<Count<<"]"<<"The fake coin is in the second section."<<endl;
            exchange_weigh(a,r1,r1,r2,r2,prere);
        }
        else
        {
            cout<<"["<<Count<<"]"<<"The fake coin is in the first section."<<endl;
            exchange_weigh(a,l1,l1,l2,l2,prere);
        }
    }
    else
    {
        if(a[l1]==a[real])
        {
            cout<<"["<<Count<<"]"<<"the loc of fake coin is "<<l2;
            Find = l2;
            if(prere==1)
            cout<<" lighter!"<<endl;
            else
            cout<<" heavier!"<<endl;
        }
        else
        {
            cout<<"["<<Count<<"]"<<"the loc of fake coin is "<<l1;
            Find = l1;
            if(a[l1]>a[real])
            cout<<" heavier!"<<endl;
            else
            cout<<" lighter!"<<endl;
        }
    }
    
}

void SearchFakeCoin(int a[],int l,int r)//寻找假币
{
    int n=r-l+1;//计算当前剩余钱币个数，如果小于等于九，则不能做简单的递归，需要分情况
    if(n>2)//n大于2时,前两堆还可以交换
    {
        if(weigh_1(a,l,r)==0)//如果前两堆质量相等,则假币在第三堆里
        {
            if(Find==-1)
            Count++;

            real=l;//任意标记一枚真币
            cout<<"["<<Count<<"]"<<"The fake coin is in the third pile."<<endl;
            cout<<"The range of this pile is from "<<l+(r-l+1)/3+(r-l+1)/3<<" to "<<r<<endl;
            SearchFakeCoin(a,l+(r-l+1)/3+(r-l+1)/3,r);
        }
            
        else//前两堆质量不等，则假币在其中，用weigh_2方法对前两堆继续比重
        {
            int start1=l;
            int end1=l+(r-l+1)/3-1;//第一堆的结束点
            int start2=end1+1;
            int end2=l+(r-l+1)/3+(r-l+1)/3-1;//前两堆的结束点

            if(Find==-1)
            Count++;   

            real=r;//记录一枚真币的位置
            cout<<"["<<Count<<"]"<<"The fake coin is in the first or second pile."<<endl;
            int re1=weigh_1(a,l,r);
            exchange_weigh(a,start1,end1,start2,end2,re1);
        }
    }
    else if(n==2)
    {
        if(a[l]==a[real])
        {
            if(Find==-1)
            Count++;
            SearchFakeCoin(a,r,r);
        }
        else
        {
            if(Find==-1)
            Count++;
            if(a[l]>a[real])
            {
                Find=l;
                cout<<"["<<Count<<"]"<<"the loc of fake coin is "<<l;
                cout<<" heavier!"<<endl;
            }    
            if(a[l]<a[real])
            {
                Find=l;
                cout<<"["<<Count<<"]"<<"the loc of fake coin is "<<l;
                cout<<" lighter!"<<endl;
            }
        }
    }
    else//n只有一枚时
    {
        if(Find==-1)
        Count++;
        Find=l;
        cout<<"["<<Count-1<<"]"<<"["<<Count<<"]"<<"the loc of fake coin is "<<l;
        if(a[l]>a[real])
        cout<<" heavier!"<<endl;
        else
        cout<<" lighter!"<<endl;
    }

}

int main()
{
    int a[120]={0};
    for(int i=0;i<120;i++)
    a[i]=2;
    srand((int)time(NULL));
    int loc=rand()%120;//rand()%120;//随机生成假币位置
    int b=rand()%2;//随机生成假币重量或为1或为3
    int wei;
    if(b==1)
    wei=3;
    else
    wei=1;

    a[loc]=wei;//将loc位置假币重置质量

    SearchFakeCoin(a,0,119);
    cout<<"The preset location is:"<<loc<<endl;
    if(wei==3)
    cout<<"The preset weight is heavier"<<endl;
    else
    cout<<"The preset weight is lighter"<<endl;
    if(Find==loc)//匹配成功则输出成功信息
    cout<<"Find the coin!"<<endl;
    else
    cout<<"failed"<<endl;
    cout<<"Total times:"<<Count<<endl; 
    system("pause");
    return 0;
}