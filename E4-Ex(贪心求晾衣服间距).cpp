#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int N,M;
    cin>>N>>M;
    int x[N];
    for(int i=0;i<N;i++){
        cin>>x[i];
    }
    sort(x,x+N);
    int res=1;
    int flag = 1;
    while(flag==1){
        int lastClothes = x[0];        // 当前已晾的衣服坐标
        int clothNum = 1;              // 已在衣架上的衣服数，第一件衣服已晾
        for (int i = 1; i < N; i++){
            // 间距比d大就晾上去
            if (x[i] - lastClothes >= res){
                clothNum++;
                lastClothes = x[i];
            }
        }
        //如果晾的下，说明可能d还可以更大
        if(clothNum>=N-M){
            flag = 1;
            res++;
        }
        else
            flag = 0;
    }
    cout << res-1;
    return 0;
}