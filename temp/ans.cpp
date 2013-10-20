#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;


int main(int argc,int * argv)
{
	int T;
	ifstream fcin("a.in");
	ofstream fcout("a.out");
	fcin >> T;
	int a[100][100];
	int n,m;
	for(int iCase=1; iCase <= T; ++iCase)
	{
		fcin >> n>>m;
		for(int i=0;i<n;++i)
		{
			for(int j=0;j<m;++j)
			{
				fcin >> a[i][j];
			}
		}
		if(n==1||m==1) fcout << "Case #" << iCase <<": YES" << endl;
		else
		{
			bool flag = true;
			int min;
			for(int i=0;i<n;++i)
			{
				for(int j=0;j<m;++j)
				{
					min = 0;
					for(int k=0; k < m;++k)
					{
						if(a[i][k] > a[i][j]) {min = 1;break;}
					}
					if(min == 0) continue;
					min = 0;
					for(int k=0; k < n;++k)
					{
						if(a[k][j] > a[i][j]) {min = 1;break;}
					}
					if(min == 1) flag =false;
				}
			}
			if(flag)
			fcout << "Case #" << iCase <<": YES" << endl;
			else fcout << "Case #" << iCase <<": NO" << endl;
		}
	}
    return 0;
}