#include <vector>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class Graph
{
    public:
        Graph(int cnt);

        virtual void add_edge(int source, int destination, int cost);
        virtual void add_edge(int source, int destination);
        virtual void add_bi_edge(int source, int destination, int cost);
        virtual void add_bi_edge(int source, int destinatino);
        virtual void print();

        // Stack based implementation of DFS
        virtual void DFSStack();
        // Recursion based implementation of DFS
        virtual void DFSRecursion();

        // Queue based implementation of BFS
        virtual void BFS();
        virtual void BFSQueue(int index, vector<int>& visited);
    private:
        struct Edge
        {
            int source;
            int destination;
            int cost;
            Edge* next;

            Edge(int src, int des, int cst);
        };
        
        struct AdjList
        {
            Edge* head;
        };

        int count;

        vector<AdjList*> ListVector;

        class EdgeComparator
        {
            public:
                bool operator()(Edge* x, Edge* y);
        };
};

Graph::Edge::Edge(int src, int dst, int cst = 1)
    : source(src), destination(dst), cost(cst=1), next(nullptr)
{
}

Graph::Graph(int cnt)
{
    count = cnt;
    ListVector = vector<AdjList*>(cnt);
    for(int i = 0; i < cnt; ++i)
    {
        ListVector[i] = new AdjList();
        ListVector[i]->head = nullptr;
    }
}

void Graph::add_edge(int source, int destination, int cost)
{
    Edge* edge = new Edge(source, destination, cost);
    // all new edge is inserted at the beginning of AdjList
    edge->next = ListVector[source]->head;
    ListVector[source]->head = edge;
}

void Graph::add_edge(int source, int destination)
{
    add_edge(source, destination, 1);
}

void Graph::add_bi_edge(int source, int destination, int cost)
{
    add_edge(source, destination, cost);
    add_edge(destination, source, cost);
}

void Graph::add_bi_edge(int source, int destination)
{
    add_bi_edge(source, destination, 1);
}

void Graph::print()
{
    Edge* ad;
    for(int i = 0; i < count; ++i)
    {
        ad = ListVector[i]->head;
        if(ad != nullptr)
        {
            cout << "Vertex: " << i << " is connected to: ";
            while (ad != nullptr)
            {
                cout << ad->destination << " ";
                ad = ad->next;
            }
            cout << endl;
        }
    }
}

bool Graph::EdgeComparator::operator()(Edge* x, Edge* y)
{
    if(x->cost <= y->cost)
    {
        return false;
    }
    return true;
}

void Graph::DFSStack()
{
    vector<int> visited(count);
    for(int i = 0; i < count; ++i)
        visited[i] = 0;

    int curr;
    stack<int> stk;

    // push the starting node into stack.
    visited[0] = 1;
    stk.push(0);

    while (!stk.empty())
    {
        curr = stk.top();
        stk.pop();

        Edge* head = ListVector[curr]->head;

        // traverse an AdjList->Edge->Edge->Edge... linkedlist.
        while (head != nullptr)
        {
            // push all unvisited child into queue
            if(visited[head->destination] == 0)
            {
                visited[head->destination] = 1;
                stk.push(head->destination);
            }
            head = head->next;
        }
    }
}

void Graph::BFS()
{
    vector<int> visited(count);
    for(int i = 0; i < count; ++i)
        visited[i] = 0;

    for(int i = 0; i < count; ++i)
    {
        // if node has not been visited
        if(visited[i] == 0)
        {
            BFSQueue(i, visited);
        }
    }
}

void Graph::BFSQueue(int index, vector<int>& visited)
{
    int curr;
    queue<int> que;

    visited[0] = 1;
    // push first AdjList element within ListVector
    que.push(index);

    // traverse an AdjList->Edge->Edge->Edge... linkedlist.
    while (!que.empty())
    {
        curr = que.front();
        que.pop();
        Edge* head = ListVector[curr]->head;
        while (head != nullptr)
        {
            // push all unvisited child into queue
            if(visited[head->destination] == 0)
            {
                visited[head->destination] = 1;
                que.push(head->destination);
            }
            head = head->next;
        }
        
    }
    
}

int main()
{
    Graph g(4);

    g.add_edge(1,2);
    g.add_edge(1,3);
    g.add_edge(1,4);

    g.add_edge(2,2);
    g.add_edge(2,3);

    g.add_edge(3,4);
    g.add_edge(3,2);

    g.print();
}