#include<iostream>
#include<stdio.h>
#include<map>
#include<string>
using namespace std;

int main()
{
    int T;
    cin>>T;
    if(T<1||T>100)
        return 0;
    string result[100];
    int N,M;
    map<string,string> mapstring;
    for(int k=0;k<T;++k){
        cin>>N>>M;
        if(N<2||N>10||M<0||M>10)
            return 0;
        string s1,s2,str[1000];
        mapstring.clear();
        for(int i=0;i<M;++i){
            cin>>s1>>s2;
            if(s1.size()>20||s2.size()>20)
                return 0;
            mapstring.insert(pair <string,string>( s1, s2 ));
        }
        int itr=0;
         string ss;
        getchar();
        getline(cin,ss);
        string::iterator p=ss.begin();
        while(p!=ss.end()){
            if(*p==' ')
                ++itr;
            else
                str[itr].push_back(*p);
            ++p;
        }
        itr=0;
        map<string, string>::iterator iter;
        while(str[itr]!=""){
            for(int i=0;i<N-1;++i){
                iter=mapstring.find(str[itr]);
                if(iter!=mapstring.end())
                    str[itr]=iter->second;
                else
                    break;
            }
            itr++;
        }
        if(str[itr]=="")
            if(itr>100)
                return 0;
        else
            if(itr>99)
                return 0;
        itr=0;
        while(str[itr]!=""){
            string tmp=str[itr]+" ";
            result[k]+=tmp;
            itr++;
        }
        result[k]=result[k].substr(0,result[k].length()-1);
    }
    for(int i=0;i<T;++i)
        cout<<"Case #"<<i+1<<": "<<result[i]<<endl;
    return 0;
}