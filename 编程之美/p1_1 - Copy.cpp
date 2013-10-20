#include <iostream>
#include <string>
using namespace std;
int main(int argc,char ** argv)
{
    /*
    string a,b;
    cin >> a >> b;
    //cout << "a:" << a << endl<< "b:" << b << endl;
    return 0;
    */
    int t,n,m;
    cin >>t;
    string preS[100],newS[100],startS,tempS;
    string result[100];
    for(int i=0;i < t; ++i)
    {
        cin >>n>>m;
        for(int j=0; j < m; ++j)
        {
            cin >> preS[j] >> newS[j];
            //cout <<"word:" << preS[j] << " " << newS[j] << endl;
        }
        getline(cin,startS);
        getline(cin,startS);
        //cout <<"sten:" << startS << endl;
        int pos =0,endpos=0;
        int size = startS.size();
        while(endpos < startS.size() && pos < startS.size())
        {
            while(pos < startS.size() && startS[pos]==' ') pos++;
            endpos = pos;
            while(endpos < startS.size() && startS[endpos] != ' ')endpos++;
            //cout <<"p:"<<pos<<"ed:" << endpos << endl << "sw:" << startS.substr(pos,endpos-pos) <<"wgg" << endl;
            tempS = startS.substr(pos,endpos-pos);
            for(int k = 0; k < n-1; k++)
            {
                for(int j=0;j < m; ++j)
                {
                    if(tempS.compare(preS[j])==0)
                    {
                        tempS = newS[j];
                        break;
                    }
                }
            }
            startS.replace(pos,endpos-pos,tempS);
            //cout << "aw:" << startS << endl;
            //cout <<"os:" << endpos-pos <<"ns:" << tempS.size() << endl;
            pos = endpos+(tempS.size()-(endpos-pos));
        }
        //cout << "Case #" << i+1 << ": "<<startS<<endl;
        result[i] = startS;
    }
    for(int i=0;i<t;++i)
    {
        cout << "Case #" << i+1 << ": "<<result[i]<<endl;
    }
    return 0;
}
