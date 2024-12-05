#include <bits/stdc++.h>
using namespace std;
int V,E;
int** Extended_Shortest_Path(int **l,int **adjMatrix)
{
    int **lq=new int*[V];

    for(int i=0;i<V;i++)
    {
        lq[i]=new int[V];
        for(int j=0;j<V;j++)
        {
            lq[i][j]=100000000;
            for(int k=0;k<V;k++)
            {
                lq[i][j]=min(lq[i][j],l[i][k]+adjMatrix[k][j]);
            }
        }
    }
    return lq;

}
void PrintAllPair(int **adjMatrix)
{
    cout<<"Shortest distance matrix:"<<endl;
    for(int i=0;i<V;i++)
    {

        for(int j=0;j<V;j++)
    {
        if(adjMatrix[i][j]==100000000)
            cout<<"INF"<<" ";
        else
        cout<<adjMatrix[i][j]<<" ";
    }
    cout<<endl;
    }
}
void matrixMultiplication(int **adjMatrix)
{
    int **ad=new int*[V];
    //int **adjMatrix=new int*[V];
    for(int i=0; i<V; i++)
    {

        ad[i]=new int[V];
        for(int j=0; j<V; j++)
        {
            if(i==j)
            ad[i][j]=0;
            else
            ad[i][j]=100000000;
        }
    }
    for(int i=0;i<V-1;i++)
    {
         ad=Extended_Shortest_Path(ad,adjMatrix);

    }
    PrintAllPair(ad);

}
void floyd(int **adjMatrix)
{
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
        {
            for(int k=0;k<V;k++)
            {
                if((j!=i || k!=i) && j!=k)
                {
                   if(adjMatrix[j][k]> adjMatrix[j][i]+adjMatrix[i][k])
                    adjMatrix[j][k]= adjMatrix[j][i]+adjMatrix[i][k];
                }


            }
        }
    }
    PrintAllPair(adjMatrix);

}
int main()
{

    cin>>V>>E;
    int **adjMatrix=new int*[V];
    for(int i=0; i<V; i++)
    {

        adjMatrix[i]=new int[V];
        for(int j=0; j<V; j++)
        {
            if(i==j)
            adjMatrix[i][j]=0;
            else
            adjMatrix[i][j]=100000000;
        }
    }
    for(int i=0; i<E; i++)
    {
        int s,d,w;
        cin>>s>>d>>w;
        adjMatrix[s-1][d-1]=w;


    }
    floyd(adjMatrix);

    matrixMultiplication(adjMatrix);
}
