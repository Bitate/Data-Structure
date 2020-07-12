#include <vector>
#include <iostream>

class Graph
{
    public:
        Graph(int cnt);

        virtual void add_edge(int source, int destination, int cost);
        virtual void add_edge(int source, int destination);
        virtual void add_bi_edge(int source, int destination, int cost);
        virtual void add_bi_edge(int source, int destinatino);
        virtual void print();

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

        std::vector<AdjList*> ListVector;

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
    ListVector = std::vector<AdjList*>(cnt);
    for(int i = 0; i < cnt; ++i)
    {
        ListVector[i] = new AdjList();
        ListVector[i]->head = nullptr;
    }
}

void Graph::add_edge(int source, int destination, int cost)
{
    Edge* edge = new Edge(source, destination, cost);
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
            std::cout << "Vertex: " << i << " is connected to: ";
            while (ad != nullptr)
            {
                std::cout << ad->destination << " ";
                ad = ad->next;
            }
            std::cout << std::endl;
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