#include <vector>
#include <iostream>

using namespace std;

class union_find
{
private:
    vector<int> root;
    vector<int> size;
    vector<int> rank;
public:
    union_find(/* args */);
    ~union_find();
public:
    int get_root(int n);
    bool find_opt(int v, int u);
    void add_node(int n);
    void union_opt(int v, int u);
    int do_union_find_opt(vector<vector<int>>& original_vector, int n);
};

union_find::union_find()
{
}

union_find::~union_find()
{
}

int union_find::get_root(int n)
{
    while (n != root[n])
    {
        n = root[n];
    }
    return n;
}

bool union_find::find_opt(int v, int u)
{
    return get_root(v) == get_root(u);
}

void union_find::union_opt(int v, int u)
{
    root[u] = root[v];
}

int union_find::do_union_find_opt(vector<vector<int>>& original_vector, int n)
{
    root.resize(n);
    for(int i = 0; i < n; ++i)
        root[i] = i;
    for(auto edge : original_vector)
    {
        if(!find_opt(edge[0], edge[1]))
        {
            union_opt(edge[0], edge[1]);
        }
    }

    int cc = 0;
    for(int i = 0; i < root.size(); ++i)
    {
        cc += (root[i] == i);
    }
    return cc;
}


int main()
{
    vector<vector<int>> setA = { {0,1}, {0,2}, {1,2}, {3,4}, {4,5}};
    vector<vector<int>> setB = {{0,1},{0,2},{3,4},{2,3}};
    union_find u;
    cout << "setA has " << u.do_union_find_opt(setA, 6) << " component(s)" << endl;
    cout << "setB has " << u.do_union_find_opt(setB, 5) << " component(s)" << endl;
}