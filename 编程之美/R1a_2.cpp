#include <iostream>
#include <string>
using namespace std;


int main(int argc,int * argv)
{
	int T;
	cin >> T;
	string s1,s2;
	int min,cnt;
	for(int iCase=1; iCase <= T; ++iCase)
	{
		cin >> s1 >> s2;
		min = 99999999;
		for(int i=0; i <= s1.size() - s2.size(); ++i)
		{
			cnt = 0;
			for(int j=0; j < s2.size(); ++j)
			{
				if(s1[i+j] != s2[j]) cnt++;
			}
			if(cnt < min) min = cnt;
		}
		cout << "Case #" << iCase <<": " << min << endl;
	}
    return 0;
}
