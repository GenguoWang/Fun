#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;
struct level
{
	int s1,s2;
	int flag;
};

int N;
int status;
int cnt,mincnt;
int opened;
void work(level plel[])
{
	level lel[10];
	for(int i = 0; i < N;++i)
	{
		lel[i] = plel[i];
	}
	int oldstatus = status;
	int oldcnt = cnt;
	int oldopened = opened;
	bool flag = true;
	while(flag)
	{
		flag = false;
		for(int i = 0; i < N; ++i)
		{
			if(lel[i].flag != 2 && status >= lel[i].s2)
			{
				status += (2-lel[i].flag);
				lel[i].flag = 2;
				cnt++;
				opened++;
				flag = true;
			}
		}
	}
	if(opened == N)
	{
		if(cnt < mincnt) mincnt = cnt;
		opened = oldopened;
		status = oldstatus;
		cnt = oldcnt;
		return;
	}
	for(int i = 0; i < N; ++i)
	{
		if(lel[i].flag == 0 && status >= lel[i].s1)
		{
			lel[i].flag = 1;
			status++;
			cnt++;
			work(lel);
			lel[i].flag = 0;
			status--;
			cnt--;
		}
	}
	opened = oldopened;
	status = oldstatus;
	cnt = oldcnt;
}
//#define fcin cin
//#define fcout cout

int main(int argc,int * argv)
{
	ifstream fcin("a.in");
	ofstream fcout("a.out");
	level lel[1000];
	int T,index;
	fcin >> T;
	for(int iCase=1; iCase <= T; ++iCase)
	{
		fcin >>N;
		for(int i=0;i<N;++i)
		{
			fcin >> lel[i].s1 >> lel[i].s2;
			lel[i].flag = 0;
		}
		status = 0;
		cnt = 0;
		opened = 0;
		mincnt = 99999;
		//work(lel);
		bool flag = true;
		while(true)
		{
			flag = true;
			while(flag)
			{
				flag = false;
				for(int i = 0; i < N; ++i)
				{
					if(lel[i].flag != 2 && status >= lel[i].s2)
					{
						status += (2-lel[i].flag);
						lel[i].flag = 2;
						cnt++;
						opened++;
						flag = true;
					}
				}
			}
			if(opened == N)
			{
				if(cnt < mincnt) mincnt = cnt;
				break;
			}
			index = -1;
			for(int i = 0; i < N; ++i)
			{
				if(lel[i].flag == 0 && status >= lel[i].s1)
				{
					if(index >=0)
					{
						if(lel[i].s2 > lel[index].s2)index = i;
					}
					else
					{
						index = i;
					}
				}
			}
			if(index == -1) break;
			lel[index].flag = 1;
			status++;
			cnt++;
		}
		if(mincnt != 99999)
		{
			fcout << "Case #" << iCase <<": "<< mincnt << endl;
		}
		else fcout << "Case #" << iCase <<": Too Bad" << endl;
	}
    return 0;
}