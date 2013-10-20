
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
	string a[4];
	int tx,ty;
	int flag = 0;
	bool b1,b2,b3,b4;
	bool isend;
	for(int iCase=1; iCase <= T; ++iCase)
	{
		fcin >> a[0] >> a[1] >> a[2] >> a[3];
		//fcout << a[0] << endl << a[1] << endl << a[2] << endl << a[3] << endl;
		tx = -1; ty = -1;
		for(int i=0;i<4;++i)
		{
			for(int j=0;j<4;++j)
			{
				if(a[i][j] =='T')
				{
					tx = i;
					ty = j;
					break;
				}
			}
		}
		flag = 0;
		isend = true;
		b1 = false;b2=false;b3=true,b4=true;
		bool bb1,bb2;
		if(tx>=0 && ty>=0)
		{
			a[tx][ty] = 'X';
		}
		for(int i=0; i < 4; ++i)
		{
			bb1 = true;
			bb2 = true;
			for(int j=0; j < 4; ++j)
			{
				if(a[i][j] != 'X') bb1 = false;
				if(a[j][i] != 'X') bb2 = false;
				if(a[i][j] == '.') isend = false;
			}
			if(a[i][i] != 'X') b3 = false;
			if(a[i][3-i] != 'X') b4 = false;
			if(bb1) b1 = true;
			if(bb2) b2 = true;
		}
		if(b1||b2||b3||b4) flag = 1;
		b1 = false;b2=false;b3=true,b4=true;
		if(tx>=0 && ty>=0)
		{
			a[tx][ty] = 'O';
		}
		for(int i=0; i < 4; ++i)
		{
			bb1 = true;
			bb2 = true;
			for(int j=0; j < 4; ++j)
			{
				if(a[i][j] != 'O') bb1 = false;
				if(a[j][i] != 'O') bb2 = false;
			}
			if(a[i][i] != 'O') b3 = false;
			if(a[i][3-i] != 'O') b4 = false;
			if(bb1) b1 = true;
			if(bb2) b2 = true;
		}
		if(b1||b2||b3||b4) flag = -1;
		if(flag == 1)
		{
			fcout << "Case #" << iCase <<": X won" << endl;
		}
		else if(flag == -1)
		{
			fcout << "Case #" << iCase <<": O won" << endl;
		}
		else if(isend)
		{
			fcout << "Case #" << iCase <<": Draw" << endl;
		}
		else
		{
			fcout << "Case #" << iCase <<": Game has not completed" << endl;
		}
	}
    return 0;
}
