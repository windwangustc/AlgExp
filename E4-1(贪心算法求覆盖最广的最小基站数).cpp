#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int N,R;
    cin>>N>>R;
    int x[N];
    for(int i=0;i<N;i++){
        cin>>x[i];
    }
    sort(x,x+N);

    int stationNum=0;
    int nowPoint=0;
    int farthestPoint=0;    //当前最远基站
    int unCovered = x[0];   //当前未被覆盖到的为位置
    for (int i = 1; i < N; i++)
    {
        // 贪心寻找一个最远位置基站进行放置
        for (i; (unCovered >= x[i] - R) && i < N; i++)
            ;
        stationNum++;
        farthestPoint = x[i - 1];
        // 找出当前未被覆盖的最近的村
        for (i; (x[i] <= farthestPoint + R) && i < N; i++)
            ;
        unCovered = x[i];
    }
    if (x[N - 1] > farthestPoint + R)
        stationNum++;
    cout << stationNum;
    return 0;
}