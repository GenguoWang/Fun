#include <iostream>
#include <vector>
#include <string>
#include <list>
using namespace std;
#define MaxInt 0x1fffffff;
#define SIZE 101
void floyd(int* matrix,int number,int * path)
{
	
	for(int i=0;i < number; ++i)
	{
		for(int x=0;x<number;++x)
		{
			for(int y=0;y<number;++y)
			{
				if(matrix[x*SIZE+y]>matrix[x*SIZE+i]+matrix[i*SIZE+y])
				{
					matrix[x*SIZE+y] = matrix[x*SIZE+i]+matrix[i*SIZE+y];
					if(path != NULL) path[x*SIZE+y] = i;
				}
			}
		}
	}
}
void getPath(int * path,int ss,int ee,int number,list<int>&result)
{
	if(path[ss*SIZE+ee]!=-1 && path[ss*SIZE+ee] != ss && path[ss*SIZE+ee] !=ee)
	{
		getPath(path,ss,path[ss*SIZE+ee],number,result);
		getPath(path,path[ss*SIZE+ee],ee,number,result);
	}
	else
	{
		result.push_back(ee);
	}
}
void qsort(int * a,int left,int right)
{
    if(left >= right) return;
    int l=left,r=right,temp;
    while(l<r)
    {
        while(l<r&&a[l]<=a[r])l++;
        temp=a[l];a[l]=a[r];a[r]=temp;
        while(l<r&&a[l]<=a[r])r--;
        temp=a[l];a[l]=a[r];a[r]=temp;
    }
    qsort(a,left,l-1);
    qsort(a,l+1,right);
}
int main(int argc,char ** argv)
{
	
	int T,N,M;
	int len;
	int matrix[SIZE*SIZE];
	int path[SIZE*SIZE];
	int t1,t2;
	int lenList[200];
	cin >> T;
	for(int iCase = 1; iCase <= T; ++iCase)
	{
		cin >> N;
		
		for(int x=0;x<N;++x)
		{
			for(int y=0; y <N;++y)
			{
				matrix[x*SIZE+y] = MaxInt;
				if(x==y) matrix[x*SIZE+x] = 0;
				if(path !=NULL) path[x*SIZE+y] = -1;
			}
		}
		for(int iN=0;iN<N-1;++iN)
		{
			cin >> t1 >> t2 >> len;
			matrix[(t1-1)*SIZE+t2-1] = len;
			matrix[(t2-1)*SIZE+t1-1] = len;
		}
		cin >> M;
		floyd((int*)matrix,N,(int*)path);
		
		cout << "Case #"<<iCase<<":"<<endl;
		for(int iM=0;iM<M;iM++)
		{
			cin >> t1 >> t2;
			list<int> res;
			getPath((int*)path,t1-1,t2-1,N,res);
			int ls=0,startP = t1-1;
			for(list<int>::iterator it=res.begin();it != res.end(); it++)
			{
				lenList[ls++] = matrix[startP*SIZE+*it];
				startP = *it;
			}
			bool flag = false;
            if(ls>=3)
            {
                qsort(lenList,0,ls-1);
                for(int i=ls-3;i>=0;--i)
                {
                    if(lenList[i]+lenList[i+1] > lenList[i+2])
                    {
                        flag=true;
                    }
                }
            }
            if(flag) cout << "YES" << endl;
            else cout << "NO" << endl;
		}
	}
    return 0;
}

