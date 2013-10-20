// beautifulcode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//start
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <map>
using namespace std;
char r[10][10];
int xnum[10][10];
int N,M;
int pathx[100];
int pathy[100];
map<unsigned long long,int*> cnt;
//unsigned cnt[65][300];
int path;
int now;
unsigned long long setnow;
ifstream fin("a.in");
int cal()
{
	int temp[10][10];
	memset((void*)temp,0,sizeof(temp));
	int x,y;
	int res=0;
	for(int i=0;i<path;++i)
	{
		x=pathx[i];
		y=pathy[i];
		if(temp[x-1][y]==0)res++;
		else res--;
		if(temp[x+1][y]==0)res++;
		else res--;
		if(temp[x][y-1]==0)res++;
		else res--;
		if(temp[x][y+1]==0)res++;
		else res--;
		temp[x][y] = 1;
	}
	return res;
}
void dfs(int x,int y)
{
	char old = r[x][y];
	unsigned long long oldset = setnow;
	r[x][y] = 'T';
	pathx[path] = x;
	pathy[path] = y;
	path++;
	int ct = cal();
	if(cnt.find(setnow) == cnt.end())
	{
		cnt[setnow] = new int[300];
		memset((void*)cnt[setnow],0,sizeof(int)*300);
	}
	map<unsigned long long,int*>::iterator it = cnt.find(setnow);
	it->second[ct] = (it->second[ct]+1) % 100000007;
	if(r[x-1][y]!='T')
	{
		if(r[x-1][y]=='X')
		{
			setnow = setnow | (unsigned long long)1<<xnum[x-1][y];
		}
		dfs(x-1,y);
		setnow = oldset;
	}
	if(r[x+1][y]!='T')
	{
		if(r[x+1][y]=='X')
		{
			setnow = setnow | (unsigned long long)1<<xnum[x+1][y];
		}
		dfs(x+1,y);
		setnow = oldset;
	}
	if(r[x][y-1]!='T')
	{
		if(r[x][y-1]=='X')
		{
			setnow = setnow | (unsigned long long)1<<xnum[x][y-1];
		}
		dfs(x,y-1);
		setnow = oldset;
	}
	if(r[x][y+1]!='T')
	{
		if(r[x][y+1]=='X')
		{
			setnow = setnow | (unsigned long long)1<<xnum[x][y+1];
		}
		dfs(x,y+1);
		setnow = oldset;
	}
	path--;
	setnow = oldset;
	r[x][y] = old;
}
int main(int argc, char* argv[])
{
	int T;
	fin >> T;
	vector<int> x,y;
	int total[3000];
	for(int iCase = 1; iCase <= T;++iCase)
	{
		fin >> N >> M;
		x.clear();
		y.clear();
		cnt.clear();
		int pp=0;
		for(int i=1; i<=N;++i)
		{
			for(int j=1; j<=M;++j)
			{
				fin >> r[i][j];
				if(r[i][j]=='X')
				{
					x.push_back(i);
					y.push_back(j);
					pp++;
					xnum[i][j] = pp;
				}
			}
		}
		for(int i=1;i<=N;++i)
		{
			r[i][0] = 'T';
			r[i][M+1] = 'T';
		}
		for(int j=1; j<=M; ++j)
		{
			r[0][j] = 'T';
			r[N+1][j] = 'T';
		}
		//memset((void*)cnt,0,sizeof(cnt));
		for(now=0; now < x.size();++now)
		{
			path = 0;
			setnow = 1<<xnum[x[now]][y[now]];
			dfs(x[now],y[now]);
			r[x[now]][y[now]] = 'T';
		}
		memset((void*)total,0,sizeof(total));
		for(map<unsigned long long,int*>::iterator it = cnt.begin(); it != cnt.end();++it)
		{
			for(int i=0; i < 300; ++i)
			{
				total[i] = (total[i] + it->second[i])%100000007;
			}
		}
		cout << "Case #" << iCase <<":"<<endl; //记得冒号后面的空格
		for(int i=0; i < 3000;++i)
		{
			if(total[i]>0)
			{
				cout << i << " " << total[i] << endl;
			}
		}
		//cout << " " << total << " " <<total1<< endl;
	}
	return 0;
}

