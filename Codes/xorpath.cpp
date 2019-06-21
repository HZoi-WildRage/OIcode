#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
struct edge{
    int END,next;
    bool b[32];
}v[30005];
int first[105],p,t[105],du[105];
double f[105][35][2];
double a[105][105],x[105];
void add(int a,int b,int c){
    int i=1;
    du[a]++;
    while(c){
        v[p].b[i]=c&1;
        i++;c>>=1;
    }
    v[p].END=b;v[p].next=first[a];
    first[a]=p++;
}
int n,m;
void gauss(){
    int im,num=1;
    for(int k=1;k<=n;k++,num++){
        im=k;
        for(int i=k+1;i<=n;i++){
            if(fabs(a[i][k])>fabs(a[im][k]))
                im=i;
        }
        if(im!=k){
            for(int i=k;i<=n+1;i++){
                swap(a[num][i],a[im][i]);
            }
        }
        if(!a[num][k]){
            num--;continue;
        }
        for(int i=num+1;i<=n;i++){
            if(!a[num][k])continue;
            long double t=a[i][k]/a[num][k];
            for(int j=k;j<=n+1;j++){
                a[i][j]-=t*a[k][j];
            }
        }
    }
    for(int i=n;i>=1;i--){
        for(int j=n;j>=i+1;j--){
            a[i][n+1]-=a[i][j]*x[j];
        }
        x[i]=a[i][n+1]/a[i][i];
    }
}
int main()
{
    //freopen("xorpath.in", "r", stdin);
    //freopen("xorpath.out", "w", stdout);
    memset(first,-1,sizeof(first));
    scanf("%d%d",&n,&m);
    for(int a1,b,c,i=1;i<=m;i++){
        scanf("%d%d%d",&a1,&b,&c);
        add(a1,b,c);
        if(a1!=b) add(b,a1,c);
    }
    //for(int i=first[n];i!=-1;i=v[i].next)
     //   rdu[v[i].END]--;
    long double ans=0;
    for(int k=1;k<=31;k++){
        memset(a,0,sizeof(a));
        a[1][n+1]=-1;
        //a[1][1]=-1;
        for(int i=2;i<=n;i++){
            a[i][i]=-1;
            memset(t,0,sizeof(t));
            for(int j=first[i];j!=-1;j=v[j].next){
                //if(v[j].END==n)continue;
                if(v[j].b[k]) a[i][v[j].END]-=double(1)/du[v[j].END],a[i][n+1]-=(double)1/du[v[j].END];
                else a[i][v[j].END]+=double(1)/du[v[j].END];
            }
        }
        //a[n][n]=1;
        gauss();
        ans+=x[n]*(1<<(k-1));
    }
    printf("%.3lf",(double)ans);
}
