/* 3. 给定一个整数集合和一个整数，利用回溯法从集合中找出元素之和等于给定整数的所有
子集。例如，有集合{2, 3, 4, 7, 9, 10, 12, 15, 18}，给定数为 20，那么满足条件的子集为
{2，18}、{2，3，15}。 给出伪代码和结果截图。 */

#include <bits/stdc++.h>
using namespace std;

#define N 9
#define Value 20
int a[] = {2, 3, 4, 7, 9, 10, 12, 15, 18};

/* 
1.使用解空间树搜索满足解情况的解
2.设置全局变量pick[]和cur[]分别记录全局解和当前记录情况
3.以第一个数为根节点，选与不选作为左右分支，后续类似
4.剪枝：加上下一个数大于Value（20），左右两个分支都可以剪去（按从小到大排序）
5.当刚好为value（20）时，输出一种情况，一个递归出口
 */

bool pick[N];
bool cur[N];
int Count = 0;

void print()
{
    cout<<"["<<Count<<"] "<<" {";
    for(int i=0;i<N;i++)
    {
        if(pick[i])
            cout<<a[i]<<",";
    }
    cout<<"}"<<endl;
}

// 寻找解,两个参数表示当前考虑数下标，当前值
void search_solution(int index, int val)
{
    
    if(index<N) //当还没有考虑完集合中所有数时
    {
        //左子树考虑
        if(val+a[index]>Value)
        return;
        else if(val+a[index]<Value)
        {
            cur[index] = 1;
            search_solution(index+1,val+a[index]);
        }
        else //输出一种解情况
        {
            cur[index] = 1;
            for(int i=0;i<=index;i++)
                pick[i] = cur[i];
            for(int i=index+1;i<N;i++)
                pick[i] = 0;
            Count++;
            print();
        }

        //右子树考虑
        cur[index] = 0;
        search_solution(index+1,val);
    }
    else
        return;
}

// 初始化函数
void init()
{

}

// 操作函数
void proceed()
{
    search_solution(0,0);
    system("pause");
}

// 主函数
int main(void)
{
    init();
    proceed();
    return 0;
}