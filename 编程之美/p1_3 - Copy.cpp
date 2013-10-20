#include <iostream>
using namespace std;
struct node
{
    int number;
    struct node * pnext;
    unsigned long len;
};
void qsort(unsigned long * a,int left,int right)
{
    if(left >= right) return;
    int l=left,r=right,temp;
    //int rd = rand()%(right-left)+left;
    //cout << "l:" << left << " rd:"<<rd<<" right:" << right << endl;
    //temp=a[rd];a[rd]=a[r];a[r]=temp;
    while(l<r)
    {
        while(l<r&&a[l]<=a[r])l++;
        temp=a[l];a[l]=a[r];a[r]=temp;
        while(l<r&&a[l]<=a[r])r--;
        temp=a[l];a[l]=a[r];a[r]=temp;
    }
    qsort(a,left,l-1);
    qsort(a,l+1,right);
}
int main(int argc,char ** argv)
{
    int t,n,m,t1,t2,ss,tt;
    unsigned long len;
    unsigned long *lenList = new unsigned long[100001];
    unsigned long ls;
    cin >> t;
    typedef struct node *   PNODE;
    PNODE pnode;
    PNODE * myn = new PNODE[100001];
    int *visited = new int[100001],*queue=new int[100001];
    unsigned long *minPath = new unsigned long[100001];
    int qs,qe,qnow,qold;
    for(int ii=0; ii < t;++ii)
    {
        cin >> n;
        //cout << "n:" << n << endl;
        for(int i=1; i < n+1;++i)
        {
            myn[i] = NULL;
            visited[i] = 0;
        }
        for(int i=0; i < n-1;++i)
        {
            cin >> t1 >> t2 >> len;
            //cout << t1 << ' ' << t2 << ' ' << len << endl;
            pnode = new node;
            pnode->number = t1;
            pnode->len = len;
            pnode->pnext = myn[t2];
            myn[t2] = pnode;
            pnode = new node;
            pnode->number = t2;
            pnode->len = len;
            pnode->pnext = myn[t1];
            myn[t1] = pnode;
        }
        for(int i=1;i<n+1;++i)
        {
            pnode = myn[i];
            //cout << i;
            while(pnode != NULL)
            {
                //cout <<"->"<<pnode->number;
                pnode = pnode->pnext;
            }
            //cout << endl;
        }
        cin >> m;
        cout << "Case #"<< ii+1 <<":"<<endl; 
        for(int i=0;i<m;++i)
        {
            cin >> ss >> tt;
            /*
            for(int it=1;it < n+1;++it) minPath[it] = 0xffffffff;
            for(int kk=1;kk < n+1; ++kk)
            {
                visited[kk] = 0;
            }
            minPath[ss] = 0;
            unsigned long templong;
            int index;
            for(int it=0;it < n; ++it)
            {
                templong = 0xffffffff;
                for(int it=1;it < n+1;++it)
                {
                    if(visited[it]==0 && minPath[it] < templong)
                    {
                        index = it;
                        templong = minPath[it];
                    }
                }

            }
            */
            /*Dijkstra*/
            
            qs = 0;
            qe = 0;
            ls = 0;
            unsigned long tempMax=0xffffff,templong;
            for(int kk=1;kk < n+1; ++kk)
            {
                visited[kk] = 0;
            }
            queue[qe++] = ss;
            visited[ss] = ss;
            while(qs<qe)
            {
                qnow = queue[qs++];
                //cout <<"visite " << qnow << endl;
                if(qnow == tt) 
                {
                    templong = 0;
                    cout << "path:";
                    while(qnow != ss)
                    {
                        qold = visited[qnow];
                        pnode = myn[qold];
                        while(pnode != NULL)
                        {
                            if(pnode->number == qnow)
                            {
                                templong += pnode->len;
                                break;
                            }
                            pnode = pnode->pnext;
                        }
                        cout << qnow << "->";
                        qnow = qold;
                    }
                    cout << "len: " << templong << endl;
                    if(templong < tempMax) tempMax;
                    else continue;
                    ls=0;
                    cout << "pathNew:";
                    qnow = tt;
                    while(qnow != ss)
                    {
                        qold = visited[qnow];
                        pnode = myn[qold];
                        while(pnode != NULL)
                        {
                            if(pnode->number == qnow)
                            {
                                lenList[ls++] = pnode->len;
                                break;
                            }
                            pnode = pnode->pnext;
                        }
                        cout << qnow <<" " << lenList[ls-1] << "->";
                        qnow = qold;
                    }
                    cout << endl;
                    //break;
                    continue;
                }
                pnode = myn[qnow];
                while(pnode != NULL)
                {
                    if(visited[pnode->number] == 0||pnode->number == tt)
                    {
                        queue[qe++] = pnode->number;
                        visited[pnode->number] = qnow;
                    }
                    pnode = pnode->pnext;
                }
            }
            
            //cout << "bq"<<endl;
            bool flag = false;
            if(ls>=3)
            {
                qsort(lenList,0,ls-1);
                cout << "qsort:";
                for(int ky=0;ky<ls;ky++) cout <<lenList[ky] << ' ';
                cout << endl;
                for(int i=ls-3;i>=0;--i)
                {
                    if(lenList[i]+lenList[i+1] > lenList[i+2])
                    {
                        flag=true;
                    }
                }
            }
            if(flag) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
    return 0;
}
