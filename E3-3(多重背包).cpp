#include <algorithm>
#include <iostream>

using namespace std;

int dp[10000];
int main()
{
    int n,m,a,b,c;
    cin >> n >> m;
    for(int i=0;i<n;++i){
        cin >> a >> b >> c;
        for(int i=1;i<=c;++i){ //c遍 01背包就可以了
            for(int j=m;j>=a*i;--j){
                dp[j]=max(dp[j],dp[j-a]+b);
            }
        }
    }
    cout << dp[m];
    return 0;
}