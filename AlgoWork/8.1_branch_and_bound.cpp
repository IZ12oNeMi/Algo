/* 1. 利用分支限界法求 0-1 背包问题。有 n = 20 个物品，背包最大可装载 M = 878
Kg。物品重量和价值分别如下：
W = {92 ,4 ,43 ,83 ,84 ,68 ,92 ,82 ,6 ,44 ,32 ,18 ,56 ,83 ,25 ,96 ,70 ,48 ,14 ,58}, 
V = {44 ,46 ,90 ,72 ,91, 40 ,75 ,35 ,8 ,54 ,78 ,40 ,77 ,15 ,61 ,17 ,75 ,29 ,75 ,63}，
求最优背包价值。给出伪代码和结果截图。 */

#include <bits/stdc++.h>
using namespace std;

int W[] = {92 ,4 ,43 ,83 ,84 ,68 ,92 ,82 ,6 ,44 ,32 ,18 ,56 ,83 ,25 ,96 ,70 ,48 ,14 ,58};
int V[] = {44 ,46 ,90 ,72 ,91, 40 ,75 ,35 ,8 ,54 ,78 ,40 ,77 ,15 ,61 ,17 ,75 ,29 ,75 ,63};
#define N 20
#define M 878

/* 
1.先算出单位价值最大的物品依次排序，
2.问题下界：采用贪心法求出下届
3.问题上界：用背包容量乘以最大的单位价值作为上界
4.限界函数：对于前i个物品装入情况下，考虑当前价值+剩下其他物品能装多少是多少+最后装不下的空间*装不下的物品的单位价值，是则保留
5.根节点表示初始状态，左子树右子树分别表示放入或不放入。
6.采用广度优先搜索，创建一个队列，每遍历一层，处理一次队列，直至遍历到叶子节点
7.再建立一个处理队列，将每个可行的节点加入到其中，等待遍历完成后搜寻最优解
8.利用最优解节点向前搜索，找出所有放入背包的物品
 */
float max_unitValue = 0;
float upper;
int lower;
bool is_pick[N] = {0}; 
int most = 0;

struct object
{
    int index;
    int val;
    int weight;
    float unitValue;
}Goods[N];

class Node
{
    public:
    int cur_w;
    int cur_v;
    float res;
    int index;
    bool isleft;
    Node* father;

    Node(int w, int v, int index)
    {
        cur_w = w;
        cur_v = v;
        this->index = index;
    }

    void set_father(Node* f)
    {
        father = f;
    }
    
};


void quick_sort(object a[], int low, int high)
{
    if(low<high)
    {
        int i=low,j=high;
        float temp = a[low].unitValue;
        object teob = a[low];
        while(i<j)
        {
            while(a[j].unitValue<temp && i<j)
            j--;

            if(i<j)
            a[i++] = a[j];

            while(a[i].unitValue>temp && i<j)
            i++;

            if(i<j)
            a[j--] = a[i];
        }
        a[i] = teob;
        quick_sort(a,low,i-1);
        quick_sort(a,i+1,high);
    }
}
float upperBound()
{
    return max_unitValue*M;
}

int lowerBound()
{
    quick_sort(Goods,0,N-1);
    //for(int i=0;i<N;i++)
    //cout<<sortUnitValue[i].index+1<<"\t"<<sortUnitValue[i].unitValue<<endl; 
    int w = 0;
    int v = 0;
    int i = 0;
    while(w+Goods[i].weight <= M && i<N)
    {
        w += Goods[i].weight;
        v += Goods[i++].val;
    }

    return v;
} 
float Restrict(object ob[],int w,int i)
{
    float res = 0;
    int re_w = M-w;
    while(re_w!=0)
    {
        if(ob[i].weight <= re_w)
        {
            res += ob[i].val;
            re_w -= ob[i++].weight;
        }
        else{
            float a = re_w * ob[i].unitValue;
            res += a;
            re_w = 0;
        }
    }
    return res;
}
void print()
{
    cout<<"item Picked from: ";
    for(int i=0;i<N;i++)
    if(is_pick[i])
    cout<<"["<<Goods[i].index+1<<"] ";
    cout<<endl<<"Total Value is: "<<most<<endl;
}

void SearchSolution(object ob[])
{
    queue<Node*> nodelist, nodesolution;
    Node* a = new Node(0,0,0);
    a->res = Restrict(ob,0,0);
    a->father = NULL;
    nodelist.push(a);
    nodesolution.push(a);

    while(!nodelist.empty())
    {
        //取出队首元素
        Node* node = nodelist.front();
        nodelist.pop();

        if(node->res + node->cur_v > lower && node->index<N)
        {
            // 左节点
            int left_w = node->cur_w + ob[node->index].weight;
            int left_v = node->cur_v + ob[node->index].val;
            Node* left = new Node(left_w, left_v, node->index+1);

            left->set_father(node);
            left->isleft = true;
            left->res = Restrict(ob,left->cur_w,left->index);
            nodesolution.push(left);

            //左节点的重量小于等于背包的承重，且左节点的上界价值大于最优解
            if(left->cur_w < M && left->res + left->cur_v > lower)
            {
                nodelist.push(left);
                if(left->cur_v > most)
                {
                    most = left->cur_v;
                }
            }
            // 右节点
            Node* right = new Node(node->cur_w,node->cur_v,node->index+1);
            right->set_father(node);
            right->isleft = false;
            right->res  = Restrict(ob,right->cur_w,right->index);

            nodesolution.push(right);
            if(right->res + right->cur_v > lower)
            {
                nodelist.push(right);
            }
        }
    }
    Node* node = nodesolution.front();
    while(1)
    {
        nodesolution.pop();
        if(node->cur_v == most)
        {
            break;
        }
        node = nodesolution.front();
    }
    while(NULL != node->father)
    {
        if(node->isleft)
        {
            is_pick[node->index -1] = 1;
        }
        node = node->father;
    }

    print();
    
}

// 初始化函数
void init()
{
    for(int i=0;i<N;i++)
        Goods[i].index = i;
    for(int i=0;i<N;i++)
        Goods[i].val = V[i]; 
    for(int i=0;i<N;i++)
        Goods[i].weight = W[i]; 
    for(int i=0;i<N;i++)
        Goods[i].unitValue = (float)V[i]/W[i]; 
    for(int i=0;i<N;i++)
        if(Goods[i].unitValue > max_unitValue)
            max_unitValue = Goods[i].unitValue;
    upper = upperBound();
    lower = lowerBound();
    cout<<"The upper bound:"<<upper<<endl<<"The lower bound:"<<lower<<endl;
}

// 操作函数
void proceed()
{
    SearchSolution(Goods);
    system("pause");
}

// 主函数
int main(void)
{
    init();
    proceed();
    return 0;
}