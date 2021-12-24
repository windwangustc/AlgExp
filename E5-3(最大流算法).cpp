#include <string.h>
#include <iostream>
#include <queue>
using namespace std;
#define arraysize 500
int maxData = 0x7fffffff;
int capacity[arraysize][arraysize];  //记录残留网络的容量
int flow[arraysize];  //标记从源点到当前节点实际还剩多少流量可用
int pre[arraysize];  //标记在这条路径上当前节点的前驱,同时标记该节点是否在队列中
int n, m;
queue<int> myqueue;
int BFS(int src, int des) {
    int i;
    while (!myqueue.empty())  //队列清空
        myqueue.pop();
    for (i = 1; i < m + 1; ++i) {
        pre[i] = -1;
    }
    pre[src] = 0;
    flow[src] = maxData;
    myqueue.push(src);
    while (!myqueue.empty()) {
        int index = myqueue.front();
        myqueue.pop();
        if (index == des)  //找到了增广路径
            break;
        for (i = 1; i < m + 1; ++i) {
            if (i != src && capacity[index][i] > 0 && pre[i] == -1) {
                pre[i] = index;                                  //记录前驱
                flow[i] = min(capacity[index][i], flow[index]);  //关键：迭代的找到增量
                myqueue.push(i);
            }
        }
    }
    if (pre[des] == -1)  //残留图中不再存在增广路径
        return -1;
    else
        return flow[des];
}
int maxFlow(int src, int des) {
    int increasement = 0;
    int sumflow = 0;
    while ((increasement = BFS(src, des)) != -1) {
        int k = des;  //利用前驱寻找路径
        while (k != src) {
            int last = pre[k];
            capacity[last][k] -= increasement;  //改变正向边的容量
            capacity[k][last] += increasement;  //改变反向边的容量
            k = last;
        }
        sumflow += increasement;
    }
    return sumflow;
}
int main() {
    int i;
    int start, end, ci;
    int S;  //起点
    int T;  //终点
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    cin>>m>>n>>S>>T;
    for (i = 0; i < n; ++i) {
        cin >> start >> end >> ci;
        //if (start == end)  //考虑起点终点相同的情况
            //continue;
        capacity[start][end] += ci;  //此处注意可能出现多条同一起点终点的情况
    }
    cout << maxFlow(S, T) << endl;
    return 0;
}
/*
 12 8
 1 2 5
 1 3 6
 2 3 2
 2 5 4
 2 4 3
 3 5 3
 4 5 1
 4 6 4
 4 7 5
 5 7 4
 7 8 5
 6 8 3
 */