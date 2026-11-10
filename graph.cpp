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
        void kruskal();
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

void graph::prim(int x)
{
    int dist[101];
    int prev[101] = {0};
    bool known[101] = {false};
    int total = 0;

    // Initialize distances
    for(int i = 1; i <= vertice; i++)
        dist[i] = 999999;

    // Starting vertex
    dist[x] = 0;

    cout << "\nPrim: " << endl;

    while(true)
    {
        int v = 0;
        int smallest = 999999;

        // Find the unknown vertex with the smallest edge cost
        for(int i = 1; i <= vertice; i++)
        {
            if(!known[i] && dist[i] < smallest)
            {
                smallest = dist[i];
                v = i;
            }
        }

        // No more reachable vertices
        if(v == 0)
            break;

        // Add vertex to the tree
        known[v] = true;

        // Print selected edge
        if(prev[v] != 0)
        {
            cout << prev[v] << "-" << v
                 << " Cost: " << dist[v] << endl;

            total += dist[v];
        }

        // Update adjacent vertices
        for(int w = 1; w <= vertice; w++)
        {
            if(arr[v][w] && !known[w])
            {
                if(arr[v][w] < dist[w])
                {
                    dist[w] = arr[v][w];
                    prev[w] = v;
                }
            }
        }
    }
     cout << "Total cost: " << total << endl;
}
void graph::kruskal()
{
    int edgeStart[5000];
    int edgeEnd[5000];
    int edgeWeight[5000];
    int edges = 0;

    int parent[101];

    // Initialize parent array
    for(int i = 1; i <= vertice; i++)
        parent[i] = i;

    // Get all edges from adjacency matrix
    // i < j ensures smaller vertex comes first
    for(int i = 1; i <= vertice; i++)
    {
        for(int j = i + 1; j <= vertice; j++)
        {
            if(arr[i][j])
            {
                edgeStart[edges] = i;
                edgeEnd[edges] = j;
                edgeWeight[edges] = arr[i][j];
                edges++;
            }
        }
    }

    // Sort edges by weight (ascending)
    for(int i = 0; i < edges - 1; i++)
    {
        for(int j = 0; j < edges - i - 1; j++)
        {
            if(edgeWeight[j] > edgeWeight[j + 1])
            {
                int temp;

                temp = edgeWeight[j];
                edgeWeight[j] = edgeWeight[j + 1];
                edgeWeight[j + 1] = temp;

                temp = edgeStart[j];
                edgeStart[j] = edgeStart[j + 1];
                edgeStart[j + 1] = temp;

                temp = edgeEnd[j];
                edgeEnd[j] = edgeEnd[j + 1];
                edgeEnd[j + 1] = temp;
            }
        }
    }

    int total = 0;
    int selected = 0;

    cout << "\nKruskal:" << endl;

    // Process edges in increasing weight order
    for(int i = 0; i < edges; i++)
    {
        int a = edgeStart[i];
        int b = edgeEnd[i];

        // Find root of first vertex
        int rootA = a;

        while(parent[rootA] != rootA)
            rootA = parent[rootA];

        // Find root of second vertex
        int rootB = b;

        while(parent[rootB] != rootB)
            rootB = parent[rootB];

        // If roots are different, adding edge won't create a cycle
        if(rootA != rootB)
        {
            parent[rootB] = rootA;

            cout << a << "-" << b
                 << " Cost: " << edgeWeight[i] << endl;

            total += edgeWeight[i];
            selected++;

            if(selected == vertice - 1)
                break;
        }
    }
    cout << "Total MST cost: " << total << endl;
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
        g.prim(N);
        g.kruskal();
        return 0;
}
