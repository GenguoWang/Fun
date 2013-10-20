#include<iostream>
#include<string>
using namespace std;
void Solve(string & s,string *list,int N,int M)
{
    int i,j,index1=0,index2=0,flag=0;
    string s2,word;
    for(i=0;i<N-1;i++)
    {
        for(;index1!=s.size()-1;)
        {
            index1=s.find(' ',index2);
            word=s.substr(index2,index1-index2);
            for(j=0;j<2*M;j+=2)
            {
                if(word==list[j])
                {
                    index2=index2+list[j].size()+1;
                    s2+=list[j+1];
                    s2+=' ';
                    flag=1;
                    break;
                }
            }
            if(flag!=1||index1==-1)
            {
                index2=index1+1;
                while(index2<s.size()&&s[index2]==' ')index2++;
                s2+=word;
                s2+=' ';
            }
            else
                flag=0;
        }
        index2=0;
        index1=0;
        s=s2;
        s2.clear();
    }
}
int main()
{
    string *list,*s;
    char ch;
    int T,N,M,i,j;
    cin>>T;
    s=new string[T];
    for(i=0;i<T;i++)
    {
        cin>>N>>M;
        list=new string[2*M];
        for(j=0;j<2*M;j++)
            cin>>list[j];
        cin.get(ch);
        getline(cin,s[i]);
        s[i]+=' ';
        Solve(s[i],list,N,M);
        s[i]=s[i].erase(s[i].size()-1);
        delete []list;
    }
    for(i=0;i<T;i++)
        cout<<"case #"<<i+1<<": "<<s[i]<<endl;
}

