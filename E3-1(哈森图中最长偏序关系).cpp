#include <stdio.h>
#include <stdlib.h>
typedef struct coordinate{
    int x;
    int y;
}coordinate;

//判断是否a,b 是否呈<=的偏序关系，是返回1，否则返回0
int isPianXu(coordinate a,coordinate b){
    if (a.x<=b.x && a.y<=b.y)
        return 1;
    else
        return 0;
}

int main(){
    int n;
    scanf("%d",&n);
    int dp[n];
    coordinate* R=(coordinate*) malloc(n*sizeof(coordinate));
    //输入
    for(int i=0;i<n;i++){
        scanf("%d%d",&R[i].x,&R[i].y);
    }
    //先按偏序进行排序
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(isPianXu(R[j],R[i])) {
                coordinate tmp;
                tmp.x=R[i].x;
                tmp.y=R[i].y;
                R[i].x=R[j].x;
                R[i].y=R[j].y;
                R[j].x=tmp.x;
                R[j].y=tmp.y;
            }
        }
    }

    dp[0]=1;
    for(int i=1;i<n;i++){
        dp[i]=1;
        for(int j=0;j<i;j++){
            if(isPianXu(R[j],R[i]) && dp[j]+1>dp[i])
                dp[i]=dp[j]+1;
        }
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(dp[i]>ans)
            ans=dp[i];
    }
    printf("%d\n",ans);
    free(R);
    return 0;
}