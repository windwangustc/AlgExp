#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int findMax(int A[], int n){
    int max=-1;
    for (int i = 0; i < n; i++){
        if (A[i]>max)
            max=A[i];
    }
    return max;
}

//计数排序算法这里直接百度拉了一个
void countingSort(int A[], int n, int k){
    int *c, *b;
    int i;
    c = (int *)malloc(sizeof(int)*k);/*临时数组,注意它的大小是待排序序列中值最大的那个。如假定该排序序列中最大值为1000000，则该数组需要1000000*sizeof(int)个存储单元*/
    b = (int *)malloc(sizeof(int)*n);  /*存放排序结果的数组*/
    for (i = 0; i < k; i++)
        c[i] = 0;                       /*初始化*/
    for (i = 0; i < n; i++)
        c[A[i]] += 1;                   /*统计数组A中每个值为i的元素出现的次数*/
    for (i = 1; i < k; i++)
        c[i] = c[i - 1] + c[i];         /*确定值为i的元素在数组c中出现的位置*/
    for (i = n - 1; i >= 0; i--)
    {
        b[c[A[i]] - 1] = A[i];       /*对A数组，从后向前确定每个元素所在的最终位置;*/
        c[A[i]] -= 1;
    }
    for (i = 0; i < n; i++)
        A[i] = b[i];                /*这个目的是返回A数组作为有序序列*/
    free(c);
    free(b);
}

int main(){
    int N;
    char T;
    //输入
    scanf("%d %c",&N,&T);
    char *s1=(char*) malloc(sizeof(char)*(N+1));
    scanf("%s",s1);
    const char sep[2] ={T,'\0'};
    int *a1=(int*) malloc(sizeof(int)*(N));
    memset(a1,0,N);

    char *p;
    int cntSize=0;
    p = strtok(s1, sep);
    while(p){
        a1[cntSize]=atoi((const char*)p);
        cntSize++;
        //printf("%s ", p);
        p = strtok(NULL, sep);
    }
    //找到数组最大元素
    int k = findMax(a1,cntSize);
    //找到后用计数排序，计数排序用空间换时间
    countingSort(a1,cntSize,k+1);

    for(int j=0;j<cntSize;j++)
        printf("%d ",a1[j]);

    free(a1);
    free(s1);
    return 0;
}