#include <bits/stdc++.h>
using namespace std;
int V,E;
class Edge
{
public:
    int source,dest;
    double weight;
};
int findParent(int *parent,int n)
{
    if(parent[n]==n)
        return n;
    return findParent(parent,parent[n]);
}
bool compare(Edge e1,Edge e2)
{
    return e1.weight<e2.weight;
}
void printTree(Edge *output,int v)
{
    double cost=0;
    for(int i=0;i<v-1;i++)
    {
        cost+=output[i].weight;
    }

    cout<<"List of edges selected by Kruskal's:";
    cout<<"{";
    for(int i=0;i<v-1;i++)
    {
        if(i!=v-2)
        cout<<"("<<output[i].source<<","<<output[i].dest<<")"<<",";
        else
            cout<<"("<<output[i].source<<","<<output[i].dest<<")";
    }
    cout<<"}"<<endl;
}
int minIndex(bool visited[],double weight[])
{
    int min_index=-1;
    double minVal=INT_MAX;
    for(int i=0;i<V;i++)
    {
        if(visited[i]==false && weight[i]<minVal)
        {
            minVal=weight[i];
            min_index=i;
        }
    }
    return min_index;
}
void printPrims(int parent[],double weight[],int ara[])
{
    double cost=0.0;
    for(int i=0;i<V;i++)
    {
        cost+=weight[i];
    }
    cout<<"Cost of the minimum spanning tree :"<<cost<<endl;
    cout<<"List of edges selected by Prim's:";
    cout<<"{";
    for(int i=1;i<V;i++)
    {
        if(i!=V-1)
        cout<<"("<<parent[ara[i]]<<","<<ara[i]<<")"<<",";
        else
            cout<<"("<<parent[ara[i]]<<","<<ara[i]<<")";
    }
    cout<<"}"<<endl;
}
void primsAlgo(int n,double **adj)
{
    int *parent=new int[n];
    Edge *output =new Edge[n-1];
    bool *visited=new bool[n];
    double *weight=new double[n];
    for(int i=0;i<n;i++)
    {
        parent[i]=-1;
        weight[i]=INT_MAX;
        visited[i]=false;
    }
    int count=0;
    weight[0]=0;
    int ara[n];
    for(int i=0;i<n;i++)
    {
        int j=minIndex(visited,weight);
        ara[i]=j;
        visited[j]=true;
        for(int k=0;k<n;k++)
        {
            if(adj[j][k]!=0 && visited[k]==false && adj[j][k]<weight[k])
            {
                weight[k]=adj[j][k];
                parent[k]=j;

            }
        }

    }
    printPrims(parent,weight,ara);
}
void kruskalsAlgo(Edge *input,int n,int E)
{
    sort(input,input+E,compare);
    int *parent=new int[n];
    Edge *output =new Edge[n-1];
    for(int i=0;i<n;i++)
    {
        parent[i]=i;
    }
    int count=0,i=0;

    while(count!=n-1)
    {
        Edge currentEdge=input[i];
        int srcParent=findParent(parent,currentEdge.source);
        int destParent=findParent(parent,currentEdge.dest);
        if(srcParent!=destParent)
        {
            output[count++]=currentEdge;
            parent[srcParent]=destParent;

        }
        i++;
    }
    printTree(output,n);
}

int main()
{
   freopen("mst.txt","r",stdin);

    cin>>V>>E;
     Edge * input=new Edge[E];
    double **adj=new double*[V];
    for(int i=0;i<V;i++)
    {
        adj[i]=new double[V];
        for(int j=0;j<V;j++)
        {
            adj[i][j]=0;
        }
    }
    for(int i=0;i<E;i++)
    {
        int s,d;
        double w;
        cin>>s>>d>>w;
        input[i].source=s;
        input[i].dest=d;
        input[i].weight=w;
        adj[s][d]=w;
        adj[d][s]=w;
    }
    primsAlgo(V,adj);
    kruskalsAlgo(input,V,E);

}
