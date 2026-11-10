#include <iostream>
#include <fstream>
#include <iomanip>
#include <stack>
#include <queue>
using namespace std;

class graph
{
    public:
        graph( ifstream& gfile );   // constructor
                                   // fill graph from data file
                                   // file is already open
        void bfs( int x );         // breadth-first node order
        void bfssp( int x );       // breadth-first spanning tree
        void dfs( int x );         // depth-first node order
        void dfssp( int x );       // depth-first spanning tree
        void mprint();             // print representation
                void dijkstra(int x);
                void prim(int x);
    private:
                int vertice;
                int lines;
                int arr[100][100] = {0};
};


graph::graph( ifstream& gfile )
{
//      fscanf(gfile, "%d ", &vertice);
//      fscanf(gfile, "%d ", &lines);
        gfile >> vertice;
        gfile >> lines;

        int a, b, val;

        for(int i = 0; i < lines; i++)
        {
//              fscanf(gfile, "%d %d %d", &a , &b, &val);
                gfile >> a >> b >> val;
                arr[a][b] = val;
                arr[b][a] = val;
        }
}

void graph::mprint()
{
        for(int i = 1; i < vertice + 1; i++)
        {
                for(int j = 1; j < vertice + 1; j++)
                {
                        cout << setw(3) << arr[i][j];
                }
                cout << endl;
        }
}

void graph::dfs(int x)
{
        stack<int> D;
        D.push(x);
        bool mark[101] = {false};

        cout << "DFS: ";
        while(!D.empty())
        {
                int v = D.top();
                D.pop();
                if(!mark[v])
                {
                        cout << v << " ";
                        mark[v] = true;
                }

                for(int i = vertice; i > 0; i--)
                {
                        if(arr[v][i] && !mark[i])

                                D.push(i);
                }
        }
        cout << endl;
}

void graph::dfssp(int x)
{
        stack<int> D;
        D.push(x);
        bool mark[101] = {false};
        int prev[101] = {0};

        cout << "DFSSP: ";
        while(!D.empty())
        {
                int v = D.top();
                D.pop();
                if(!mark[v])
                {
                        mark[v] = true;
                        if(prev[v] != 0)
                                cout << prev[v] << "-" << v << " ";
                }
                for(int i = vertice; i > 0; i--)
                {
                        if(arr[v][i] && !mark[i])
                        {
                                prev[i] = v;
                                D.push(i);
                        }
                }
        }
        cout << endl;
}

void graph::bfs(int x)
{
        queue<int> D;
        D.push(x);
        bool mark[101] = {false};

        cout << "BFS: ";
        while(!D.empty())
        {
                int v = D.front();
                D.pop();
                if(!mark[v])
                {
                        cout << v << " ";
                        mark[v] = true;
                }

                for(int i = 1; i <= vertice; i++)
                {
                        if(arr[v][i] && !mark[i])
                                D.push(i);
                }
        }
        cout << endl;
}

void graph::bfssp(int x)
{
        queue<int> D;
        D.push(x);
        bool mark[101] = {false};
        int prev[101] = {0};

        cout << "BFSSP: ";
        while(!D.empty())
        {
                int v = D.front();
                D.pop();
                if(mark[v] == false)
                {
                        mark[v] = true;
                        if(prev[v] != 0)
                                cout << prev[v] << "-" << v << " ";
                }

                for(int i = 1; i <= vertice; i++)
                {
                        if(arr[v][i] && mark[i] == false)
                        {
                                prev[i] = v;
                                D.push(i);
                        }
                }
        }
        cout << endl;
}

void graph::dijkstra(int x)
{
        int dist[101];
        bool known[101] = {false};

        for(int i = 1; i <= vertice; i++)
                dist[i] = 999999;

        dist[x] = 0;
        cout << "Dijkstra: " << endl;

        while(true)
        {
                int v = 0;
                int smallest = 9999999;

                for(int i = 1; i <= vertice; i++)
                {
                        if(!known[i] && dist[i] < smallest)
                        {
                                smallest = dist[i];
                                v = i;
                        }
                }

                if(v == 0)
                        break;

                known[v] = true;

                cout << "\nVertex " << v << " finalized:" << endl;
                for(int w = 1; w <= vertice; w++)
                {
                        if(arr[v][w] && !known[w])
                        {
                                if(dist[v] + arr[v][w] < dist[w])
                                        dist[w] = dist[v] + arr[v][w];
                        }
                }

                cout << "Distance list: ";
                for(int i = 1; i <= vertice; i++)
                {
                        if(dist[i]== 999999)
                                cout << "INF ";
                        else
                                cout << dist[i] << " ";
                }
                cout << endl;
        }
        cout << "Final shorterst " << endl;
                for(int i = 1; i <= vertice; i++)
                {
                        if(dist[i]== 999999)
                                cout << x << " to " << i << ": INF " << endl;
                        else
                                cout << x << " to " << i << ": " << dist[i] << endl;;
                }
}

int main( int argc, char *argv[] )
{
    ifstream ifp;

    //checking if file was entered on command line
    if ( argc != 2 )
    {
        cout << "File was not supplied\n";
        return 2;
    }

    ifp.open( argv[1] );

    // checking if file was opened successfully
    if( ! ifp.is_open() )
    {
        cout << "File could not be opened\n";
        return 3;
    }

    //create graph based on graph description file
    graph g( ifp );

    //print the matrix
    g.mprint();
    cout << endl << endl;


        int N;
        cout << "Enter your starting point: " ;
        cin >> N;

        g.dfs(N);
        g.bfs(N);
        g.dfssp(N);
        g.bfssp(N);
        g.dijkstra(N);
        return 0;
}
