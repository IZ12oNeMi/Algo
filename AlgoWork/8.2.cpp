/* 2. （TSP 问题）若有 16 个城市，C1，C2，…, C16，它们的坐标分别为
{41,94},{37,84},{54,67},{25,62},{7,64},{2,99},{68,58},{71,44},{54,62},{83,69},{64,60
},{18,54},{22,60},{83,46},{91,38},{25,38}。大家尝试一下，看能否用分枝限界法
在合适的时间内，找到一条从 C1 出发、遍历这 16 个城市、最终回到起点的
最短走法。给出伪代码和结果截图。 */

#include <bits/stdc++.h>
using namespace std;

int X[] = {41,37,54,25,7,2,68,71,54,83,64,18,22,83,91,25};
int Y[] = {94,84,67,62,64,99,58,44,62,69,60,54,60,46,38,38};
#define N 16

/* 
1.先创建邻接矩阵表示各个城市间的距离
2.问题上界：利用贪心法
3.问题下界：利用每行最短距离之和的二分之一相加向上取整得到
4.限界条件：包含解路径点的最小距离之和的2倍+首尾两点除路径外最短的距离加和+没有在路径上的点的最小两个距离之和。总体再除以2
5.构造待处理队列和解空间队列，当待处理队列为空时，在解空间队列中搜寻路径最短的解
6.需要设置节点储存当前路径点，当前距离，当前已走过的城市数量，上一个节点，限界值。
 */

float dis[N][N] = {0};
float lower;
float upper;

class Node
{
    public:
    int city;
    float cur_d;
    int index;
    int *path;
    int res;
    bool is_leaf = 0;

    Node(int city,float cur_d, int cn)
    {
        this->city = city;
        this->cur_d = cur_d;
        this->index = cn;
    }
    ~Node()
    {
        delete[] path;
    }
};

float upper_bound()
{
    int visited[N] = {0};
    visited[0] = 1;
    float total = 0;
    int i = 0;
    int times = 0;
    int last = 0;
    for(int times = 1;times<N;times++)
    {
        float temp = 9999;
        int index = 0;
        for(int j=0;j<N;j++)
        {
            if(dis[i][j] != 0 && visited[j] == 0 && dis[i][j] < temp)
            {
                temp = dis[i][j];
                index = j;
            }
        }
        total += temp;
        visited[index] = 1;
        i = index;
        if(times == N-1)
        last = index;
    }
    total += dis[0][last];
    return total;
}

float lower_bound()
{
    float total = 0;
    for(int i=0;i<N;i++)
    {
        float l1 = 9999;
        float l2 = 9999;
        for(int j=0 ;j<N;j++)
        {
            if(dis[i][j] < l2 && dis[i][j] !=0)
            {
                l2 = dis[i][j];
                if(dis[i][j] < l1)
                {
                    l2 = l1;
                    l1 = dis[i][j];
                }
            }
        }
        total += (l1+l2)/2;
    }
    return total;
} 

float restricted(Node* n)
{
    float total = 0 ;
    for(int i = 0;i<n->city-1;i++)
    {
        total += 2 * dis[n->path[i]][n->path[i+1]];
    }


    float temp1 = 9999;
    for(int j = 0;j<N;j++)
    {
        if(dis[n->path[0]][j] < temp1 && dis[n->path[0]][j] != 0 && j !=n->path[1])
        temp1 = dis[n->path[0]][j];
    }
    total += temp1;

    float temp2 = 9999;
    for(int j = 0;j<N;j++)
    {
        if(dis[n->path[n->city-1]][j] < temp2 && dis[n->path[n->city-1]][j] != 0 && j !=n->path[n->city-2])
        temp2 = dis[n->path[n->city-1]][j];
    }
    total += temp2;

    bool city[N]= {0};
    for(int i = 0; i<n->city; i++)
    {
        city[n->path[i]] = 1;
    }
    for(int i = 0;i<N;i++)
    {
        if(!city[i])
        {
            float l1 = 9999;
            float l2 = 9999;
            for(int j=0 ;j<N;j++)
            {
                if(dis[i][j] < l2 && dis[i][j] !=0)
                {
                    l2 = dis[i][j];
                    if(dis[i][j] < l1)
                    {
                        l2 = l1;
                        l1 = dis[i][j];
                    }
                }
            }
            total += l1+l2;
        }
    }

    return total/2.0;
}

void print(Node* node)
{
    cout<<"The shortest dis is : "<<node->cur_d<<endl<<"The path is: ";
    for(int i=0;i<N-1;i++)
    cout<<node->path[i]+1<<" -> ";
    cout<<node->path[N-1]+1<<endl;
}

void SearchSolution()
{
    queue<Node*>  nodelist, nodesolution;
    Node *a = new Node(1,0,0);
    a->path = new int[a->city];
    a->path[0]=0;
    a->res = restricted(a);
    nodelist.push(a);

    while(!nodelist.empty())
    {
        //取出队首元素
        Node* node = nodelist.front();
        nodelist.pop();

        bool is_visited[N] = {0};
        for(int j=0; j < node->city;j++)
        is_visited[node->path[j]] = 1;

        for(int i=0;i<N;i++)
        {
            if(!is_visited[i])
            {
                int index = i;
                float d = node->cur_d + dis[index][node->path[node->city-1]];
                Node* New = new Node(node->city+1,d,index);
                New->path = new int[New->city];
                for(int i = 0;i<node->city;i++)
                New->path[i] = node->path[i];
                New->path[New->city-1]=New->index;


                if(New->city == N)
                New->is_leaf = 1;
                New->res = restricted(New);

                if(!New->is_leaf && New->res < upper)
                {
                nodelist.push(New);
                for(int i = 0;i<New->city;i++)
                cout<<New->path[i]<<" ";
                cout<<endl;
                }

                else if(New->is_leaf)
                {
                    New->cur_d += dis[New->path[N-1]][0]; 
                    nodesolution.push(New);
                }
            }
        }
        delete node;
    }

    Node* ans = new Node(N,9999,0);
    while(!nodesolution.empty())
    {
        Node *node = nodesolution.front();
        nodesolution.pop();

        if(node->cur_d < ans->cur_d)
        ans = node;
    }

    print(ans);
}

// 初始化函数
void init()
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            dis[i][j] = sqrt((X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]));

    upper = upper_bound();
    lower = lower_bound();
    cout<<"The upper bound:"<<upper<<endl<<"The lower bound:"<<lower<<endl;
}


// 操作函数
void proceed()
{
    SearchSolution();
    system("pause");
}

// 主函数
int main(void)
{
    init();
    proceed();
    return 0;
}