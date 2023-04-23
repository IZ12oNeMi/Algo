/* （ TSP 问题）有 8 个城市 C1 ， C2, …, C8, 它 们 的 坐 标 分 别 为
{41,94},{37,84},{54,67},{25,62},{7,64},{2,99},{68,58},{71,44}。从 C1 出发，请找到
一条遍历这 8 个城市、最终回到起点的最短走法 */
#include<iostream>
#include<stdio.h>
#include<math.h>
using namespace std;

struct City
{
    int x;
    int y;
};

#define Max 16
int n;//城市数量
City a[Max];//储存城市
double Dis[Max][Max];//对应城市间距离的邻接矩阵
int Ncity=1;//已经走过城市的数量
int path[Max+1];//储存每一次的路线；
int visited[Max]={0};//城市访问标记，若为1则已访问
int start;//记录出发城市的编号
double min_r=999.0;//记录最短路线的长度
int M_path[Max+1];//记录最短路径；


int DFS(int index)//遍历算法
{
    if(Ncity!=n)//城市还没有走完时
    {
        for(int i=0;i<n;i++)
        {
            if(visited[i]==0)
            {
            visited[i]=1;
            path[Ncity-1]=index;
            Ncity++;
            DFS(i);

            Ncity--;
            visited[i]=0;
            }
        }
    }

    else
    {
        path[Ncity-1]=index;
        path[Ncity]=start;

        double temp=0;
        for(int i=0;i<=n;i++)
        {
            temp+=Dis[path[i]][path[i+1]];
        }
        if(temp<min_r)
        {
            min_r=temp;
            for(int i=0;i<=n;i++)
            {
                M_path[i]=path[i];
            }
        }

    }
    return 0;
}

int main()
{
    cout<<"Please enter the total number of city:";

    cin>>n;

    for(int i=0;i<n;i++)
    {
        cout<<"Enter the No."<<i+1<<" City's x and y location:"<<endl;
        cin>>a[i].x>>a[i].y;
    }


    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            double temp=sqrt((a[i].x-a[j].x)*(a[i].x-a[j].x)+(a[i].y-a[j].y)*(a[i].y-a[j].y));
            Dis[i][j]=temp;
        }
    }

    for(int i=0;i<n;i++)
    {
        start=i;
        visited[start]=1;
        DFS(start);
        visited[start]=0;
    }
    cout<<"The shortest distance is:";
    cout<<min_r<<endl;
    cout<<"The shortest route:"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<M_path[i]+1<<"-->";
    }
    cout<<M_path[n]+1<<endl;
    system("pause");
    return 0;
}
