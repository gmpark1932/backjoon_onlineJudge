// Problem Number: 6549						 
// URL: https://www.acmicpc.net/problem/6549 
// Date: 2017.07.07							 
// Purpose: 1) D&C Algorithm
//			2) Using Segment Tree
//			3) How to divide


#include <iostream>
#include <math.h>
#include <vector>
#include <stdio.h>

typedef long long LL;
using namespace std;
void init(vector<LL> &arr, vector<LL> &tree,int node,int start,int end){
	if(start == end){
		tree[node] = start;
	}else{
		int mid = (start + end)/2;
		init(arr,tree,node*2,start,mid);
		init(arr,tree,node*2+1,mid+1,end);

		if(arr[tree[node*2]] <= arr[tree[node*2+1]]){
			tree[node] = tree[node*2];
		}else{
			tree[node] = tree[node*2+1];
		}
	}
}

/* start ~ end: 노드가 담당하는 구간 */
/* left ~ right: 구해야 하는 범위의 구간 */

int findMinHeightIndex(vector<LL> &arr,vector<LL> &tree,int node,int start,int end, int left,int right){
	if(left > end || right < start) // 겹치지 않을 경우
		return -1;

	if(left <= start && end <= right){ //찾아야 하는 구간이 노드가 담당하는 구간을 완전히 포함할 때
		return tree[node];
	}

	int mid = (start + end) / 2;
	int m1 = findMinHeightIndex(arr,tree,node*2,start,mid,left,right);
	int m2 = findMinHeightIndex(arr,tree,node*2+1,mid+1,end,left,right);

	if(m1 == -1)
		return m2;
	else if (m2 == -1)
		return m1;

	else{
		if(arr[m1] <= arr[m2])
			return m1;
		else
			return m2;
	}
}

LL getMax(vector<LL> &arr,vector<LL> &tree,int start,int end){
	int n = arr.size();
	int m = findMinHeightIndex(arr,tree,1,0,n-1,start,end);

	LL area = (LL)(end-start+1) *(LL)arr[m];

	if(start <= m-1){
		LL tmp = getMax(arr,tree,start,m-1);

		if(area < tmp)
			area = tmp;
	}

	if(m+1 <= end)
	{
		LL tmp = getMax(arr,tree,m+1,end);
		if(area < tmp)
			area  = tmp;
	}

	return area;
}

int main(void){
	while(true){
		int n;

		scanf("%d",&n);

		if(n == 0)
			break;

		vector<LL> arr(n);

		for(int i=0;i<n;i++)
			scanf("%lld",&arr[i]);
		
		int h = (int)(ceil(log2(n))+1e-9);
		int tree_size = (1<<(h+1));

		vector<LL> tree(tree_size);

		init(arr,tree,1,0,n-1);

		printf("%lld\n",getMax(arr,tree,0,n-1));
	}

	return 0;
}
