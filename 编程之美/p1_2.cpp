#include <iostream>
using namespace std;
int main(int argc, char ** argv)
{
    int t,n,m,k,temp;
    unsigned long long p,q;
    unsigned long long max;
    cin >> t;
    for(int j = 0; j < t; ++j)
    {
        max = 0;
        cin >> n >> m >> k;
        if(n>m){
            temp = n;n=m;m=temp;
        }
        for(int i=2;i <= n; ++i)
        {
            p = k/i;
            if(p>=m)
            {
                q=0;
                p=m;
            }
            else
            {
                q=k%i;
            }
            p = p*(p-1)*i*(i-1)/4+p*q*(q-1)/2;
            //cout << "i="<<i<<";p=:"<<p<<endl;
            if(p >max) max=p;
        }
        cout <<"Case #" << j+1 <<": "<< max << endl;
    }
    return 0;
}
