#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
int main(int argc,char ** argv)
{
    int t,n,m;
    cin >>t;
    string preS[100],newS[100],startS,tempS;
    string result[100];
    for(int i=0;i < t; ++i)
    {
        cin >>n>>m;
        map<string,string> mymap;
        string s1,s2;
        for(int j=0; j < m; ++j)
        {
            cin >> s1 >> s2;
            mymap[s1] = s2;
        }
        getline(cin,startS);
        getline(cin,startS);
		//cout << "s:" << startS << endl;
        int pos =0,endpos=0;
        vector<string> words;
        while(endpos < startS.size() && pos < startS.size())
        {
            while(pos < startS.size() && startS[pos]==' ') pos++;
            endpos = pos;
            while(endpos < startS.size() && startS[endpos] != ' ')endpos++;
            tempS = startS.substr(pos,endpos-pos);
            if(tempS!="") words.push_back(tempS);
			pos = endpos;
        }
        for(int k=0;k<n-1;++k)
        {
			for(int t=0;t<words.size();++t)
            {
				if(mymap.count(words[t]))
				{
					words[t] = mymap[words[t]];
				}
            }
        }
		startS=words[0];
		for(int k=1;k<words.size();++k) startS = startS+" " + words[k];
        result[i] = startS;
    }
    for(int i=0;i<t;++i)
    {
        cout << "Case #" << i+1 << ": "<<result[i]<<endl;
    }
    return 0;
}