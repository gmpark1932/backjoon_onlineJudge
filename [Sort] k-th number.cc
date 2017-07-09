// Problem Number: 11004						 
// URL: https://www.acmicpc.net/problem/11004 
// Date: 2017.07.08							 
// Purpose: 1) Using stl sort

#include <stdio.h>
#include <algorithm>

int arr[5000001];

int main(void){
    int n,k;
    
    scanf("%d %d",&n,&k);
    
    for(unsigned int i = 0;i<n;i++){
        scanf("%d",arr+i);
    }
    
    std::sort(arr,arr+n);
    
    printf("%d\n",arr[k-1]);
    
    return 0;
}