#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#define N 10000
#define M 10000
using namespace std;

struct memory
{
    int nextQuery; // 下一次访问此内存的时间
    int number;    // 此内存离散化后的序号

    // 重载操作符，比较两个块内存下次访问的早晚
    bool operator<(const memory that) const
    {
        return this->nextQuery < that.nextQuery;
    }
    bool operator>(const memory that) const
    {
        return this->nextQuery > that.nextQuery;
    }

    memory(int nextquery, int No) : nextQuery(nextquery), number(No) {}
};

int NextSameQuery[M + 1]; // 表示后一个对相同内存的访问，地址范围 0 - 10000
int NextQueryOf[M + 1];   // NextQueryOf[mem]表示后一次对mem的访问，下标是内存的离散化序号

int Query[M + 1];               // 离散化之后的内存访问请求
bool IfCached[M + 1];           // 这块内存是否已被缓存

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> Query[i];
        // Query[i] = Query_undiscretized[i];
    }

    // 初始化后一次访问在无穷远处
    memset(NextQueryOf, N + 1, sizeof(NextQueryOf));

    for (int i = n - 1; i >= 0; i--)
    {
        NextSameQuery[i] = NextQueryOf[Query[i]];
        NextQueryOf[Query[i]] = i;
    }

    int miss = 0;                                 // 丢失次数
    priority_queue<memory, vector<memory>> Cache; // 缓存，依据下一次访问时间维护的优先队列

    for (int i = 0; i < n; ++i)
    {
        if (!IfCached[Query[i]]) // 访问的数据未被缓存
        {
            miss++;                // 发生MISS
            if (Cache.size() == k) // Cache已满
            {
                IfCached[Cache.top().number] = false; // 从缓存中移除下次访问最迟的内存 1
                Cache.pop();
            }
            IfCached[Query[i]] = true; // 此次访问加入缓存 1
        }
        else // 访问的数据已被缓存
            k++;
        Cache.push(memory(NextSameQuery[i], Query[i]));
    }
    cout << miss;
    return 0;
}