#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;
struct cell
{
	int type;
	bool opened;
	int kNum;
	int key[400];
};
int key[201];
int keyPath[21][201];
cell room[200];
int K,N;
int path[200];
int pc;
bool avail(int index)
{
	int a[201];
	memset((void*)a,0,201*sizeof(int));
	for(int i = 0; i < room[index].kNum; ++i) a[room[index].key[i]]++;
	for(int i=0; i < N;++i)
	{
		if(!room[i].opened && a[room[i].type] > 0) return true;
	}
	return false;
}
bool selfOpen(int index)
{
	for(int i = 0; i < room[index].kNum; ++i) if(room[index].key[i] == room[index].type) return true;
	return false;
}
bool workthree(int number)
{
	if(number == N) return true;
	int max,ind;
	for(int i = 0; i < N; ++i)
	{
		if(!room[i].opened)
		{
			ind = -1;
			max = -1;
			for(int j = pc-1; j>=0; --j)
			{
				if(path[j] > i)
				{
					if(keyPath[j][room[i].type] > 0)
					{
						ind = j;
					}
					break;
				}
				else
				{
					if(path[j] > max && keyPath[j][room[i].type] > 0)
					{
						max = path[j];
						ind = j;
					}
				}
			}
			if(ind >=0)
			{
				keyPath[ind][room[i].type]--;
				room[i].opened = true;
				memset((void*)(keyPath[pc]),0,201*sizeof(int));
				for(int j = 0; j < room[i].kNum; ++j) keyPath[pc][room[i].key[j]]++;
				path[pc++] = i;
				if (workthree(number+1)) return true;
				pc--;
				room[i].opened = false;
				keyPath[ind][room[i].type]++;
			}
		}
	}
	return false;
}
bool worktwo(int number,int pre)
{
	if(number == N) return true;
	int a[201];
	memset((void*)a,0,201*sizeof(int));
	if(pre>=0){for(int i = 0; i < room[pre].kNum; ++i) a[room[pre].key[i]]++;}
	for(int i = 0; i < pre; ++i)
	{
		if(!room[i].opened && a[room[i].type] >0 )
		{
			key[room[i].type]--;
			room[i].opened = true;
			for(int j = 0; j < room[i].kNum; ++j) key[room[i].key[j]]++;
			path[pc++] = i;
			if (worktwo(number+1,i)) return true;
			pc--;
			for(int j = 0; j < room[i].kNum; ++j) key[room[i].key[j]]--;
			room[i].opened = false;
			key[room[i].type]++;
		}
	}
	for(int i = pre+1; i < N; ++i)
	{
		if(!room[i].opened && key[room[i].type] >0)
		{
			key[room[i].type]--;
			room[i].opened = true;
			for(int j = 0; j < room[i].kNum; ++j) key[room[i].key[j]]++;
			path[pc++] = i;
			if (worktwo(number+1,i)) return true;
			pc--;
			for(int j = 0; j < room[i].kNum; ++j) key[room[i].key[j]]--;
			room[i].opened = false;
			key[room[i].type]++;
		}
	}
	return false;
}
bool work(int number)
{
	if(number == N) return true;
	for(int i = 0; i < N; ++i)
	{
		if(!room[i].opened && key[room[i].type] >0 )//&& avail(i))
		{
			key[room[i].type]--;
			room[i].opened = true;
			for(int j = 0; j < room[i].kNum; ++j) key[room[i].key[j]]++;
			path[pc++] = i;
			if (work(number+1)) return true;
			pc--;
			for(int j = 0; j < room[i].kNum; ++j) key[room[i].key[j]]--;
			room[i].opened = false;
			key[room[i].type]++;
		}
	}
	/*
	for(int i = 0; i < N; ++i)
	{
		if(!room[i].opened && key[room[i].type] > 0&& !avail(i))
		{
			key[room[i].type]--;
			room[i].opened = true;
			for(int j = 0; j < room[i].kNum; ++j) key[room[i].key[j]]++;
			path[pc++] = i;
			number++;
			//if (work(number+1)) return true;
			//pc--;
			//for(int j = 0; j < room[i].kNum; ++j) key[room[i].key[j]]--;
			//room[i].opened = false;
			//key[room[i].type]++;
		}
	}
	*/
	if(number == N) return true;
	else return false;
}
int main(int argc,int * argv)
{
	int T;
	ifstream fcin("a.in");
	ofstream fcout("a.out");
	fcin >> T;
	int temp,temp1;
	for(int iCase=1; iCase <= T; ++iCase)
	{
		fcin >> K>>N;
		memset((void*)key,0,201*sizeof(int));
		memset((void*)(keyPath[0]),0,201*sizeof(int));
		for(int i=0;i<K;++i)
		{
			fcin >> temp;
			key[temp]++;
			keyPath[0][temp]++;
		}
		
		for(int i=0; i < N; ++i)
		{
			fcin >> room[i].type >> room[i].kNum;
			room[i].opened = false;
			for(int j=0; j < room[i].kNum; ++ j)
			{
				fcin >> room[i].key[j];
			}
		}
		pc = 0;
		/*
		int openedNumber =0,oldNumber=0;
		while(true)
		{
			oldNumber = openedNumber;
			for(int i=0; i < N; ++i)
			{
				if(!room[i].opened && key[room[i].type] >0 && selfOpen(i))
				{
					key[room[i].type]--;
					room[i].opened = true;
					for(int j = 0; j < room[i].kNum; ++j) key[room[i].key[j]]++;
					path[pc++] = i;
					oldNumber++;
				}
			}
			if(oldNumber > openedNumber) openedNumber = oldNumber;
			else break;
		}*/
		path[pc++] = 9999;
		if(workthree(0))
		{
			fcout << "Case #" << iCase <<":";
			for(int i=1; i < pc; ++i) fcout << " " << path[i]+1;
			fcout << endl;
		}
		else fcout << "Case #" << iCase <<": IMPOSSIBLE" << endl;
	}
    return 0;
}
