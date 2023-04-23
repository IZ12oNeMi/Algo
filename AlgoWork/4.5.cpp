/* 5. 桌子上有 n 根火柴。两个玩家轮流拿走火柴，一人一次可以拿 1 根、2 根、3 根或者 4
根火柴。最后清零桌上火柴的玩家为获胜方。请为先走的玩家设计一个制胜的策略（如
果该策略存在）。 */

#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string>
#include <ctime>
using namespace std;
/* 
1.前面任意取都没有问题
2.要确保自己胜利，剩余的火柴数必须在最后轮到自己的时候剩余1-4根
3.所以向前推，对手最后一轮剩余的火柴数必须在5-8根
4.由于对手和我们有相同的思考方式，他会尽力避免最后轮到我们时火柴数仅剩余1-4根
5.但是每次最少会拿1根，所以倒数第二轮还剩5根火柴的人必输
6.所以我们最终的问题转化为了怎么避免轮到自己拿火柴的时候仅剩下5根火柴
7.由于每次最多也只能拿4根，所以当轮到你还剩余6-9根的时候你一定赢
8.同理当轮到你还剩10根的时候，对手一定会赢
9.由此类推，当轮到对手时，此时剩下的火柴的个数恰好为5的倍数时，无论他怎么拿火柴，你一定有方法获胜
10.所以最终情况分为两种：
（1）火柴的初始值为5的倍数时，先拿火柴的人一定输.
（2）火柴初始数量不为5的倍数时，先拿火柴的人一定赢。
11.获胜的方法：在你能赢的前提下，你只需要保持每一次拿取火柴后留给对手的火柴数量为5的倍数
 */

int count=0;//记录比赛进行次数

void GetMatch(int n)//取火柴算法，n为剩余火柴数量
{
    if(n>=5 && n%5==0)//n为5的倍数的时候,随机取走火柴
    {
        count++;
        int get=rand()%4+1;
        GetMatch(n-get);
    }
    else if(n>5 && n%5!=0)//n不为5的倍数时，将其取成5的倍数
    {
        count++;
        int get=n%5;
        GetMatch(n-get);
    }
    else//n小于5时，取最后一次
    {
        count++;
    }
}

int main()
{
    srand((int)time(NULL));
    int total=rand()%200+1;//初始火柴的数量在1-200中随机生成
    cout<<"The total number of matches is:"<<total<<endl;
    GetMatch(total);
    if(count%2==0)//如果总拿取次数为偶数，则后手胜利
    cout<<"The defensive position wins!"<<endl;
    else//为奇数，则先手胜利
    cout<<"The offensive position wins!"<<endl;
    system("pause");
    return 0;
}