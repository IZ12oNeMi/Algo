/* 1. 利用回溯法求八皇后问题，找出所有解。给出伪代码和结果截图。
八皇后：八个皇后象棋均不能在同一行同一列同一斜线上
 */

#include <bits/stdc++.h>
using namespace std;

/* 
1.设置一个一维数组x[n],其中n为皇后的个数，这个数组记录每一行皇后摆放的位置
2.利用循环，每次循环处理一行（一个皇后）的摆放问题：
（1）当全部皇后没有摆放完整时，继续下一行的拜访，如果下一行每个位置都不满足条件则回到上一行重新调整
（2）当全部皇后都摆放完成后输出一次结果，从当前点回溯探索其他的可能性。
3.用全局变量Count记录总共的摆法
4.设置一个位置判断函数is_right_place,判断当前点位置是否冲突
5.求解函数需要使用递归的形式，参数设置为当前行数row,当前列数col
6.设置一个打印函数，每满足条件进行一次
 */
#define N 8
int x[N] = {-1,-1,-1,-1,-1,-1,-1,-1}; //起始位置都设为-1
int Count = 0;

// 打印函数
void print()  
{
    cout<<"(";
    for(int i=0;i<N-1;i++)
    cout<<x[i]+1<<",";
    cout<<x[N-1]+1<<")"<<"\t";
}

// 位置判断函数
bool is_right_place(int row, int col) // row行，col列
{
    for(int i=0;i<row;i++)
    {
        if(x[i] == col || abs(row-i) == abs(col-x[i]))
        return false;
    }
    return true;
}

// 求解函数
void Queen(int row, int col, bool label) // row代表行数，col代表上一行的位置，label 为1表示正常地向下搜寻，label为0表示回溯过后需要调整
{
    int k = row;
    if(label)
    {
        bool flag = false; //判断当前行是否可以摆放皇后
        for(int i=0;i<N;i++) //一行的每个位置进行遍历
        {
            if(is_right_place(k,i)) //判断当前位置是否可以摆放
            {
                flag = true;
                x[k++] = i;
                if(k<N) //还没有摆放完时，继续递归到下一行
                {
                    Queen(k,i,true);
                }
                else //摆放完整，输出一次摆放结果,并向前回溯
                {
                    Count++;
                    print();
                    x[--k] = -1;
                    Queen(--k,col,false);
                }
            }
        }
        if(!flag) //需要回溯到上一行
        {
            x[k] = -1;
            Queen(--k,col,false);
        }
    }
    else
    {
        if(k==0 && col==N-1) //已经考虑过所有情况了
        {
            cout<<endl<<"Total num is:"<<Count<<endl;
            system("pause");
            exit(0);
        }
        
        else
        {
            bool flag = false; //判断当前行是否可以摆放皇后
            //从记录的col位置开始向后探索还有无其他情况
            for(int i=col+1;i<N;i++)
            {
                if(is_right_place(k,i)) //判断当前位置是否可以摆放,如果可以从当前位置进入下一行
                {
                    flag = true;
                    x[k++] = i;
                    Queen(k,i,true);
                }
            }
            if(!flag) //需要回溯到上一行
            {
                x[k--] = -1;
                Queen(k,x[k],false);
            }
        }
    }
    
    
}

// 初始化函数
void init()
{

}

// 操作函数
void proceed()
{
    Queen(0,-1,true);
}

// 主函数
int main(void)
{
    init();
    proceed();
    return 0;
}