#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void pswap(int *x, int *y) {
    int temp = *y;
    *y = *x;
    *x = temp;
}

int selectRandPivot(int A[],int p,int r){
    int i = rand()%(r-p+1)+p;
    pswap(&A[r],&A[i]);
    return A[r];
}

int RandomPartition(int A[],int p,int r){
    int x = selectRandPivot(A,p,r);
    int i = p-1;
    for(int j=p;j<=r-1;j++){
        if(A[j]<=x){
            i = i+1;
            pswap(&A[i],&A[j]);
        }
    }
    pswap(&A[i+1],&A[r]);
    return i+1;
}

void quicksort(int A[],int p,int r){
    while(p<r){
        int q = RandomPartition(A,p,r);
        quicksort(A,p,q-1);
        p = q+1;
    }
/*    if (p>=r) return;
    int q = partition(A,p,r);
    quicksort(A,p,q-1);
    quicksort(A,q+1,r);*/
}

int RandomSelect(int A[],int p,int r,int i){
    if(p==r)    return A[p];
    int q = RandomPartition(A,p,r);
    int k = q-p+1;
    if(i==k)
        return A[q];
    else if(i<k)
        return RandomSelect(A,p,q-1,i);
    else
        return RandomSelect(A,q+1,r,i-k);
}

int main() {
    srand((int)time(0));
    int T;
    scanf("%d",&T);
    while(T--){
        int n;      //total number
        int k;      //the first k
        scanf("%d%d",&n,&k);
        int *array=(int *) malloc(n*sizeof(int));
        for(int i=0;i<n;i++){
            scanf("%d",&array[i]);
        }
        //quicksort(array,0,n-1);
        printf("%d\n",RandomSelect(array,0,n-1,k));
        free(array);
    }
    return 0;
}