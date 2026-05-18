#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

class Node;

typedef set<Node *>::const_iterator node_iterator;

class Node
{
    string name;
    set<Node *> neighbours;
    // Храним веса рёбер: для каждого соседа — вес ребра до него
    map<Node *, int> weights;

    void addNeighbour(Node *neighbour, int weight = 1);
    void removeNeighbour(Node *neighbour);

public:
    Node(const string &aname) : name(aname) {}
    const string &getName() const { return name; }

    // Получить вес ребра до указанного соседа
    int getWeight(Node *neighbour) const;

    node_iterator nb_begin() const
    {
        return neighbours.begin();
    }
    node_iterator nb_end() const
    {
        return neighbours.end();
    }

    friend class Graph;
    friend class Dijkstra;
};

class Graph
{
    set<Node *> nodes;

public:
    void addNode(Node *node);
    void removeNode(Node *node);
    void addEdge(Node *begin, Node *end, int weight = 1);
    void removeEdge(Node *begin, Node *end);
    node_iterator begin() const
    {
        return nodes.begin();
    }
    node_iterator end() const { return nodes.end(); }
};

class BFS
{
    const Graph &graph;

public:
    BFS(const Graph &agraph) : graph(agraph) {}
    bool connected(Node *begin, Node *end);
};

class DFS
{
    const Graph &graph;
    set<Node *> visited;
    bool connected(Node *begin, Node *end, int depth);

public:
    DFS(const Graph &agraph) : graph(agraph) {}
    bool connected(Node *begin, Node *end);
};

struct MarkedNode
{
    Node *node;
    int mark;
    Node *prev;
    MarkedNode(Node *anode = 0, int amark = 0, Node *aprev = 0)
        : node(anode), mark(amark), prev(aprev) {}
};

class PriorityQueue
{
    vector<MarkedNode> nodes;

public:
    MarkedNode pop();
    void push(Node *node, int mark, Node *prev);
    bool empty() const { return nodes.empty(); }
};

struct Way
{
    vector<Node *> nodes;
    int length;
    Way() : length(-1) {}
};

class Dijkstra
{
    const Graph &graph;

public:
    Dijkstra(const Graph &agraph) : graph(agraph) {}
    Way shortestWay(Node *begin, Node *end);
};

Way unroll(map<Node *, MarkedNode> visited, Node *begin, Node *curr);