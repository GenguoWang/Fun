#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int N=20;
const int INF=0x3f3f3f3f;
int s[N][N];//��¼ͼ���ڽӾ���
int d[N];//��¼ͼ�и���Ĳ��
int n,m;
int min(int a,int b)
{
	return a<b?a:b;
}
bool bfs()
{
	queue<int>Q;
	memset(d,-1,sizeof(d));//�˴���ʼ��Ҫ�ر�ע�⣬���ϰ汾�ĳ�ʼ���ʹ��ںܴ�����
	d[1]=0;//����������ͺ�������ѭ��
	Q.push(1);
	while(!Q.empty()){
		int v=Q.front();Q.pop();
		for(int i=1;i<=n;i++){
			if(d[i]==-1&&s[v][i]){//�˴�Ӧ��s[v][i]!=0,���������ϰ汾�е�s[v][i]>0,��Ϊdfs�ǿ��ܻ��ߴ��������Զ������������
				d[i]=d[v]+1;
				Q.push(i);
			}
		}
	}
	return d[n]!=-1;
}
int dfs(int v,int cur_flow)
{
	int dt=cur_flow;
	if(v==n)return cur_flow;
	for(int i=1;i<=n;i++){
		if(s[v][i]>0&&d[v]+1==d[i]){
			int flow=dfs(i,min(dt,s[v][i]));
			s[v][i]-=flow;
			s[i][v]+=flow;
			dt-=flow;
		}
	}
	return cur_flow-dt;
}
int dinic()
{
	int cur_flow,ans=0;
	while(bfs()){//һ��bfs�����ҵ���������·
		while(cur_flow=dfs(1,INF))
			ans+=cur_flow;
	}
	return ans;
}
int main()
{
	int t,i,cas=0,u,v,w,newF;
	scanf("%d",&t);
	while(t--){
		memset(s,0,sizeof(s));
		scanf("%d %d",&n,&m);
		printf("Case %d:\n",++cas);
		for(i=1;i<=m;i++){
			scanf("%d %d %d",&u,&v,&w);
			if(u==v)continue;
			s[u][v]+=w;
			s[v][u]+=w;
			newF = dinic();   //ÿ��ִ�еĻ���������һ�εĻ���������������������ȫ���¼��㣬����newF��������
			if(newF > 0)printf("%d %d\n",i,newF);
		}
		//printf("\n");
	}
	return 0;
}
 