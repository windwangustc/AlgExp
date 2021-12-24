#include <algorithm>
#include <iostream>
#define MAX 2000
using namespace std;
int matrix[MAX][MAX];
int dp[MAX][MAX];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>matrix[i][j];
            if(matrix[i][j]==0)
                matrix[i][j]=1;
            else
                matrix[i][j]=0;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(matrix[i][j]==1)
                dp[i][j]=1;
            else
                dp[i][j]=0;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i>=1 && j>=1 && matrix[i][j]==1){
                //分别向上和向左搜索dp[i-1][j-1]个单位
                for(int k=1;k<=dp[i-1][j-1];k++){
                    if(matrix[i-k][j]==1&&matrix[i][j-k]==1)
                        dp[i][j]++;
                    else
                        break;
                }
            }
        }
    }
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            ans+=dp[i][j];
        }
    }
    cout<<ans;
    return 0;
}