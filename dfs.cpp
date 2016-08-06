/*
Instituto Superior Tecnico - LEIC - ASA - Projeto 1
Goncalo Ribeiro 82303
Andre Mendonca 82304
AL009
*/

#include <iostream> //inputs outputs (cin, cout)
#include <list>
#define NIL -1

using namespace std; //With this line, instead of write for example "std::cout" we just write "cout"

class Graph{
    int n_vertices; // Nr of vertices that will be in graph
    list<int> *adj; // A dynamic array of adjacency lists
    void findAP(int vertice, bool visited[], int discovery_time[], int low[], int parent[], bool ap[]);
    public: Graph(int n_vertices);
    public: void addEdge(int u, int v);
    public: void DFS();
};

Graph::Graph(int n_vertices){
    this->n_vertices = n_vertices;
    adj = new list<int>[n_vertices];
}

void Graph::addEdge(int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// A recursive function that find articulation points using DFS traversal
// vertice: vertice to check
// visited: visited vertices
// discovery_time: discovery times of visited vertices
// parent: parent vertices in DFS graph
// ap: articulation points
void Graph::findAP(int vertice, bool visited[], int discovery_time[], int low[], int parent[], bool ap[]){
    static int time = 0;
    int children = 0; //Counter of DFS Graph childrens
    visited[vertice] = true; //Define the current vertice as visited
    discovery_time[vertice] = low[vertice] = ++time; //Initialize vertice discovery time and low value

    //Run adjacent vertices (begin(): points to the first list element ////// end(): points to the position next to last element
    list<int>::iterator i;
    for (i=adj[vertice].begin(); i!=adj[vertice].end(); ++i){
        int vertice_adjacent = *i;

        if (!visited[vertice_adjacent]){ //If vertice adjacent is not visited
            children++; //vertice adjacent is a children
            parent[vertice_adjacent] = vertice; //vertice is father of vertice_adjacent
            findAP(vertice_adjacent, visited, discovery_time, low, parent, ap); //Recursive call for vertice adjacent
            low[vertice] = min(low[vertice], low[vertice_adjacent]);

            if ((parent[vertice]==NIL && children>1) || (parent[vertice]!=NIL && low[vertice_adjacent]>=discovery_time[vertice]))
                ap[vertice] = true;

        } else if (vertice_adjacent != parent[vertice]) { //If vertice was visited update its low value
            low[vertice] = min(low[vertice], discovery_time[vertice_adjacent]);
        }
    }
}

void Graph::DFS(){
    bool *visited = new bool[n_vertices]; //Define all the vertices as not visited
    int *discovery_time = new int[n_vertices];
    int *low = new int[n_vertices];
    int *parent = new int[n_vertices];
    bool *ap = new bool[n_vertices]; //articulation points
    int nr_ap = 0; //number of articulation points
    int max_ap = 0;
    int min_ap = n_vertices;

    // Initialize parent, visited, and ap(articulation point) arrays
    for (int i=0; i<n_vertices; i++){
        parent[i] = NIL;
        visited[i] = false;
        ap[i] = false;
    }

    for (int i=0; i<n_vertices; i++)
        if (visited[i] == false) //if vertice was not visited
            findAP(i, visited, discovery_time, low, parent, ap); //find articulation points with i as root

    for (int i=0; i<n_vertices; i++){
        if (ap[i] == true){ //if i is an articulation point
            nr_ap++; //Increment number of articulation points
            if (i<min_ap) //Compare if its minor than current smallest articulation point
                min_ap = i;

            if (i>max_ap) //Compare if its bigger than current biggest articulation point
                max_ap = i;
        }
    }

    if (nr_ap==0){ //If have no articulation points
        min_ap = NIL; //Define as -1
        max_ap = NIL; //Define as -1
    }

    cout << nr_ap << "\n"; //Print number of articulation points
    cout << min_ap << " " << max_ap << "\n"; //Print the smallest and the biggest articulation point
}

int main(){
    int n_people, n_connections, u, v; //n_people=N, n_connections=L

    cin >> n_people >> n_connections;

    Graph graph(n_people+1);
    for (int i=0; i<n_connections; i++){ //Ask for the connection many times as needed
        cin >> u >> v;
        graph.addEdge(u, v); //Add edge to the graph
    }
    graph.DFS(); //Run DFS algorithm
    return 0;
}
