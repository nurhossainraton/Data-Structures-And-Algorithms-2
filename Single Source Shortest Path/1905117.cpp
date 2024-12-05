#include <bits/stdc++.h>
using namespace std;
int V,E,d;

class Edge
{
public:
    int source,dest;
    double weight;
};

void getPrintParent(int *parent,int n)
{

    if(parent[n]==n)
        cout<<n<<"-> ";
    else
    {
        getPrintParent(parent,parent[n]);
        if(n==d)
        cout<<n;
        else
            cout<<n<<"-> ";
    }
}
void printShortestPath(int cost[],int dest,int parent[])
{
    cout<<"Shortest path cost: "<<cost[dest]<<endl;
    getPrintParent(parent,dest);
}
int findParent(int *parent,int n)
{
    if(parent[n]==n)
        return n;
    return findParent(parent,parent[n]);
}

int minCost(int cost[],bool sp[],int parent[])
{
    int minval=INT_MAX,min_index;

    for(int i=0; i<V; i++)
    {
        if(cost[i]<= minval && sp[i]==false)
        {
            min_index=i;
            minval=cost[i];

        }

    }

    return min_index;

}
void bellmanFord(Edge *input,int source,int dest)
{
    int cost[V],parent[V];
    int check;
    for(int i=0; i<V; i++)
    {
        cost[i]=INT_MAX;
        parent[i]=i;
    }
    cost[source]=0;

    for(int i=0; i<V-1; i++)
    {
        check=0;
      for(int j=0;j<E;j++)
      {
          int u,v,w;
          u=input[j].source,v=input[j].dest,w=input[j].weight;
          if(cost[u]!= INT_MAX  && cost[v]>cost[u]+w)

          {
              parent[v]=u;
              check=1;
              cost[v]= cost[u]+w;
          }
      }
    if(check==0)
    {
        break;
    }

    }
    for(int i=0;i<E;i++)
    {
        if(check==1)
        {
            int u,v,w;
          u=input[i].source,v=input[i].dest,w=input[i].weight;
          if(cost[u]!= INT_MAX  && cost[v]>cost[u]+w)
          {
              cout<<"The graph contains a negative cycle"<<endl;
              return;
          }
        }
    }

    printShortestPath(cost,dest,parent);

}
void dijkstra(int **adjMatrix,int source,int dest)
{
    int cost[V],parent[V];
    bool sp[V];
    for(int i=0; i<V; i++)
    {
        cost[i]=INT_MAX;
        sp[i]=false;
        parent[i]=i;
    }
    cost[source]=0;
    for(int i=0; i<V; i++)
    {
        int u=minCost(cost,sp,parent);
        sp[u]=true;
        for(int v=0; v<V; v++)
        {
            if(sp[v]==false  && adjMatrix[u][v]!=0 && cost[v]> cost[u]+adjMatrix[u][v])
            {
                parent[v]=u;
                cost[v]=cost[u]+adjMatrix[u][v];
            }

        }

    }
    printShortestPath(cost,dest,parent);
}
int main()
{

    cin>>V>>E;
    int **adjMatrix=new int*[V];
    Edge *input=new Edge[E];
    for(int i=0; i<V; i++)
    {

        adjMatrix[i]=new int[V];
        for(int j=0; j<V; j++)
        {
            adjMatrix[i][j]=0;
        }
    }
    for(int i=0; i<E; i++)
    {
        int s,d,w;
        cin>>s>>d>>w;
        adjMatrix[s][d]=w;
        input[i].source=s;
        input[i].dest=d;
        input[i].weight=w;

    }

    int src,dest;
    cin>>src>>dest;
    d=dest;
    //dijkstra(adjMatrix,src,dest);
    bellmanFord(input,src,dest);


}
