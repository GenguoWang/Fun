#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <iomanip>
using namespace std;
#define fcin cin
#define fcout cout

int main(int argc,int * argv)
{
	//ifstream fcin("a.in");
	//ofstream fcout("a.out");
	double x[50],y[50];
	int T,N;
	fcin >> T;
	double minX,maxX,oldV,newV,maxS,dist;
	int index;
	for(int iCase=1; iCase <= T; ++iCase)
	{
		fcin >> N;
		minX = 10001;
		maxX = -10001;
		for(int i=0; i< N; ++i)
		{
			fcin >> x[i] >> y[i];
			if(x[i] < minX) minX = x[i];
			if(x[i] > maxX) maxX = x[i];
		}
		while(maxX-minX > 1e-8)
		{
			maxS = -1;
			index = -1;
			oldV = (minX+maxX)/2;
			for(int i = 0; i < N;++i)
			{
				dist = y[i]*y[i]+(x[i]-oldV)*(x[i]-oldV);
				if(dist>maxS)
				{
					maxS = dist;
					index = i;
				}
			}
			if(x[index]>oldV)
			{
				newV = (oldV+maxX)/2;
				minX = oldV;
			}
			else
			{
				newV=(oldV+minX)/2;
				maxX = oldV;
			}
		}
		oldV = (minX+maxX)/2;
		fcout << "Case #" << iCase <<": "<< fixed << setprecision(6) << oldV << endl;
	}
    return 0;
}
