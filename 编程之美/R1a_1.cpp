#include <iostream>
#include <string>
using namespace std;


int main(int argc,int * argv)
{
	int T;
	cin >> T;
	int n,a,b,k;
	int min,cnt;
	for(int iCase=1; iCase <= T; ++iCase)
	{
		cin >> n >> a >> b;
		k = n/2;
		if(n%2 == 1)
		{

			if(b/(k+1) > a/(k+1))
			{
				cout << "Case #" << iCase <<": " << -1 << endl;
			}
			else
			{
				cout << "Case #" << iCase <<": " << 1 << endl;
			}
		}
		else
		{
			if(a/(k+1) >= b/k)
			{
				cout << "Case #" << iCase <<": " << 1 << endl;
			}
			else if(b/(k+1) > a/k)
			{
				cout << "Case #" << iCase <<": " << -1 << endl;
			}
			else
			{
				cout << "Case #" << iCase <<": " << 0 << endl;
			}
		}
		
	}
    return 0;
}
