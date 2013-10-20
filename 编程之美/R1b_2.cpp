#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <iomanip>
using namespace std;
#define fcin cin
#define fcout cout
int K;
double value[100001][11];
bool flag[100001][11];
double f(int n,int p,bool flaged)
{
	if(flag[n][p]) return value[n][p];
	if(K==1) return 6*n-4;
	if(flaged) return f(n-1,p-2,false)+2;
	if(p < 0) return 0;
	if(n==1) return 2;
	if(p>n) return f(n-1,p-2,false)+2;
	if(p==n&&p < K) return f(n-1,p-1,false)+2;
	double t1,t2,t3,t4;
	//保证下面公式的每一项都乘法的都大于等于0，除法的都大于0
	if(p <= K-2)
	{
		t1 = double(p) / (2*n-p) * f(n-1,p-1,false);
		t2 = double(p)*f(n,p+2,true);
		t3 = double(2*n-2*p-2)*f(n,p+2,false);
		t4 = f(n-1,p,false);
		value[n][p] = t1+(t2+t3+t4)*(2*n-2*p)/(2*n-p)/(2*n-p-1) + 2;
		flag[n][p] = true;
		return value[n][p];
	}
	else if(p == K-1)
	{
		t1 = double(p) / (2*n-p) * f(n-1,p-1,false);
		t2 = double(p-1)*f(n,p+1,true);
		t3 = double(2*n-2*p-1)*f(n,p+1,false);
		t4 = f(n-1,p-1,false);
		value[n][p] = t1+(t2+t3+t4)*(2*n-2*p)/(2*n-p)/(2*n-p-1) + 2;
		flag[n][p] = true;
		return value[n][p];
	}
	else
	{
		t1 = double(p-1) / (2*n-p) * f(n-1,p-2,false);
		t2 = double(p-2)*f(n,p,true);
		t3 = double(2*n-2*p+1);//*f(n,p,false);
		t4 = f(n-1,p-2,false);
		value[n][p] = (t1+(t2+t4)*(2*n-2*p+1)/(2*n-p)/(2*n-p) + 2)/(1-t3*(2*n-2*p+1)/(2*n-p)/(2*n-p));
		flag[n][p] = true;
		return value[n][p];
	}
}
int main(int argc,int * argv)
{
	//ifstream fcin("a.in");
	//ofstream fcout("a.out");
	//K = 3;
	//double a = f(2,0,0);
	//cout << a;
	//return 0;
	/*
	for(int i=1; i <=3; ++i)
	{
		for(int j=0; j<=3; ++j)
		{
			cout << i << ' ' << j << " 0: " << f(i,j,0) << endl; 
			if(j>=2)cout << i << ' ' << j << " 1: " << f(i,j,1) << endl; 
		}
	}*/
	/*
	cout << "2,3,1: "<<f(2,3,1) << endl
		<< "2,1,0: "<<f(2,1,0) << endl 
		<< "3,3,1: " << f(3,3,1) << endl 
		<< "3,3,0: " <<f(3,3,0) << endl
		<< "3,0,0: " <<f(3,0,0) << endl;
		*/
	//return 0;
	int T,N;
	fcin >> T;
	double res,t1,t2,t3,t4;
	for(int iCase=1; iCase <= T; ++iCase)
	{
		fcin >> N >> K;
		if(K==1) 
		{
			fcout << "Case #" << iCase <<": "<< fixed << setprecision(6) << (double)(6*N-4) << endl;
			continue;
		}
		for(int n = 1; n <= N;++n)
		{
			for(int p=K; p >= 0; --p)
			{
				if(n==1)
				{
					value[n][p] = 2;
					continue;
				}
				//value[n][p][1] = value[n-1][p-2][0]+2;
				if(p>n) value[n][p] = value[n-1][p-2]+2;
				else if(p==n&&p < K) value[n][p] = value[n-1][p-1]+2;
				else
				{
					if(p <= K-2)
					{
						t1 = double(p) / (2*n-p) * value[n-1][p-1];
						t2 = double(p)*(value[n-1][p]+2);
						t3 = double(2*n-2*p-2)*value[n][p+2];
						t4 = value[n-1][p];
						value[n][p] = t1+(t2+t3+t4)*(2*n-2*p)/(2*n-p)/(2*n-p-1) + 2;
					}
					else if(p == K-1)
					{
						t1 = double(p) / (2*n-p) * value[n-1][p-1];
						t2 = double(p-1)*(value[n-1][p-1]+2);
						t3 = double(2*n-2*p-1)*value[n][p+1];
						t4 = value[n-1][p-1];
						value[n][p] = t1+(t2+t3+t4)*(2*n-2*p)/(2*n-p)/(2*n-p-1) + 2;
					}
					else
					{
						t1 = double(p-1) / (2*n-p) * value[n-1][p-2];
						t2 = double(p-2)*(value[n-1][p-2]+2);
						t3 = double(2*n-2*p+1);//*f(n,p,false);
						t4 = value[n-1][p-2];
						value[n][p] = (t1+(t2+t4)*(2*n-2*p+1)/(2*n-p)/(2*n-p) + 2)/(1-t3*(2*n-2*p+1)/(2*n-p)/(2*n-p));
					}
				}
			}
		}
		/*
		for(int n = 1; n <= N;++n)
		{
			for(int p=0; p <= K; ++p)
			{
				cout << n << ' ' << p << " :" << value[n][p] << endl;
			}
		}*/
		//res = f(N,0,false);
		fcout << "Case #" << iCase <<": "<< fixed << setprecision(6) << value[N][0] << endl;
	}
    return 0;
}
