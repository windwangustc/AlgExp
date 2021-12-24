#include <iostream>
#include <vector>
using namespace std;

int cnt=0;
int MAX=10000007;

vector<int> merge(vector<int> a,vector<int> b){
    vector<int> tmp;
    int i=0,j=0;
    while(i<a.size() && j<b.size()){
        if(a[i]<=b[j]){
            tmp.push_back(a[i++]);
        }
        else{
            tmp.push_back(b[j++]);
            //每次归并插入更新逆序数
            //元素移动的单位和就是逆序对的个数
            cnt=(cnt+a.size()-i)%MAX;
        }
    }
    if(i==a.size()){
        while(j<b.size()){
            tmp.push_back(b[j++]);
        }
    }else if(j==b.size()){
        while(i<a.size()){
            tmp.push_back(a[i++]);
        }
    }
    return tmp;
}

vector<int> sort(vector<int>& init,int start,int end){
    if(start==end){
        return vector<int>(1,init[start]);
    }
    int mid=(start+end)/2;
    vector<int> a=sort(init,start,mid);
    vector<int> b=sort(init,mid+1,end);
    return merge(a,b);
}

// 采用归并排序，其交换次数就是逆序对的个数
int InversePairs(vector<int> data) {
    sort(data,0,data.size()-1);
    return cnt;
}

int main(){
    int N;
    scanf("%d",&N);
    vector<int> a;
    for(int i=0;i<N;i++){
        int t;
        cin>>t;
        a.push_back(t);
    }
    printf("%d\n", InversePairs(a));
}