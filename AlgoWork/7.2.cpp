/* . 2. 利用回溯法求 0-1 背包问题。有 n = 20 个物品，背包最大可装载 M = 878 Kg。
W = {92 ,4 ,43 ,83 ,84 ,68 ,92 ,82 ,6 ,44 ,32 ,18 ,56 ,83 ,25 ,96 ,70 ,48 ,14 ,58}, 
V = {44 ,46 ,90 ,72 ,91, 40 ,75 ,35 ,8 ,54 ,78 ,40 ,77 ,15 ,61 ,17 ,75 ,29 ,75 ,63}??
 */

#include <bits/stdc++.h>
using namespace std;
#define N 20
#define M 878

int W[] = {92 ,4 ,43 ,83 ,84 ,68 ,92 ,82 ,6 ,44 ,32 ,18 ,56 ,83 ,25 ,96 ,70 ,48 ,14 ,58};
int V[] = {44 ,46 ,90 ,72 ,91, 40 ,75 ,35 ,8 ,54 ,78 ,40 ,77 ,15 ,61 ,17 ,75 ,29 ,75 ,63};

/* 
1.使用解空间树的方式构造可能的解。
2.需要设置全局变量
（1）cur[ ]记录当前选择情况
（2）pick[ ]记录目前（最终）选择情况，共20个物品。其中1表示挑选该物品，0表示不挑选该物品
（3）maxv目前（最终）最大价值量
3.以第一个物品为根节点，其选与不选构成两个分支，后面物品类似思路，直到20个物品选择完毕
4.因为解空间树过大，需要合理的剪枝
（1）对于左子树的剪枝，当加入下一件物品重量当前重量超过最大载重量剪去
（2）对于右子树的剪枝，如果当前价值加上剩下所有物品的价值都没有当前最大价值量的数量大剪去
5.当遍历了所有枝叶时，输出maxv和pick[ ]

 */

bool cur[N];
bool pick[N];
int maxv=0;

void print()  //???????????
{
    cout<<"???????????"<<endl<<"????????????"<<"{";
    for(int i=0;i<N;i++)
    {
        if(pick[i]==1)
            cout<<i+1<<",";
    }
    cout<<"}"<<endl;
    cout<<"??????????????"<<maxv<<endl;
}

//????????????????,???????????????????????????��?????????????????????????
void search_best_solution(int index, int cv, int cw)  
{
    // ??????��???????????
    if(index < N)
    {
        // ???????��?
        if(cw+W[index] <= M)
        {
            cur[index] = 1;
            search_best_solution(index+1,cv+V[index],cw+W[index]);
        }
        else //???????????????????????
        {
            cur[index] = 0;
            // ?��??????????????????
            if(cv > maxv)
            {
                maxv = cv;
                for(int i=0;i<=index;i++)
                    pick[i] = cur[i];
                for(int i=index+1; i<N;i++)
                    pick[i] = 0;
            }
        }

        //???????��?
        int predict = cv;  //???????????????????????
        for(int i=index+1;i<N;i++)
            predict += V[i];
        if(predict > maxv)  //????????????????????????????????
        {
            cur[index] = 0;
            search_best_solution(index+1,cv,cw);
        }
        else  // ??????????????????????
            return ;

    }
    // ???????????????????????
    else  
    {
        // ?????????????????�I?????
        if(cw <= M && cv > maxv)
        {
            maxv = cv;
            for(int i=0;i<index;i++)
                pick[i] = cur[i];
        }
    }
    

}

// ?????????
void init()
{

}

// ????????
void proceed()
{
    search_best_solution(0,0,0);
    print();
    system("pause");
}

// ??????
int main(void)
{
    init();
    proceed();
    return 0;
}

