#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAMELEN 6

typedef struct {
    char name[NAMELEN];
    int color;
}nameinfo;

int SumArray(int a[],int size){
    int retVal=0;
    for(int i=0;i<size;i++)
        retVal+=a[i];
    return retVal;
}
int main() {
    int result=0;
    int n, k;
    scanf("%d %d", &n, &k);
    nameinfo names[n];
    //赋值并染色
    int initColor=1;
    for (int i = 0; i < n; i++) {
        scanf("%s", names[i].name);
        names[i].color = initColor++;
        for(int j=0;j<i;j++){
            if(strcmp(names[i].name,names[j].name)==0){
                names[i].color = names[j].color;
                initColor--;
                break;
            }
        }
    }
    //统计共有多少种不同的颜色
    int totalcolor = initColor-1;
    //printf("共有%d颜色\n",totalcolor);

    //设置初始滑窗
    int initWindow=k;
    //设置初始判别数组
    int *array=(int *) malloc(sizeof(int)*n);

    for (int i = 0; i <= n-k; i++) {
        memset(array,0,n*sizeof(int));
        //从第一个名字开始遍历
        int j = i;
        int tmp=0;
        while(tmp!=k&&j<n){
            if(n-j+tmp<k)
                break;
            if(array[names[j].color-1]==0){
                array[names[j].color-1]=1;
                tmp++;
            }
            j++;
        }
        if(tmp==k){
            result++;
            //再往下找一个，直到有不一样的为止
            while(j<n){
                if(array[names[j].color-1]==1){
                    result++;
                    j++;
                }
                else
                    break;
            }
        }
    }

    printf("%d\n",result);
    free(array);
    return 0;
}

