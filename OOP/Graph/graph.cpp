#include <iostream>
#include "graph.h"
#include <set>
#include <queue>
#include <map>
using namespace std;

// NODE
void Node::addNeighbour(Node *neighbour, int weight)
{
    neighbours.insert(neighbour);
    weights[neighbour] = weight;
}

void Node::removeNeighbour(Node *neighbour)
{
    neighbours.erase(neighbour);
    weights.erase(neighbour);
}

int Node::getWeight(Node *neighbour) const
{
    auto it = weights.find(neighbour);
    if (it != weights.end())
        return it->second;
    return -1; // ребро не найдено
}

// GRAPH
void Graph::addNode(Node *node)
{
    nodes.insert(node);
}

void Graph::removeNode(Node *node)
{
    nodes.erase(node);
    // Remove also from all neighbours list
    for (set<Node *>::iterator it = nodes.begin();
         it != nodes.end(); it++)
    {
        (*it)->removeNeighbour(node);
    }
}

void Graph::addEdge(Node *begin, Node *end, int weight)
{
    if (nodes.find(begin) == nodes.end())
        return;
    if (nodes.find(end) == nodes.end())
        return;
    begin->addNeighbour(end, weight);
    end->addNeighbour(begin, weight);
}

void Graph::removeEdge(Node *begin, Node *end)
{
    if (nodes.find(begin) == nodes.end() || nodes.find(end) == nodes.end())
        return;
    begin->removeNeighbour(end);
    end->removeNeighbour(begin);
}

// BFS
bool BFS::connected(Node *begin, Node *end)
{
    if (begin == end)
        return true;

    queue<Node *> nodes;
    nodes.push(begin);
    set<Node *> visited;

    while (!nodes.empty())
    {
        Node *next = nodes.front();
        nodes.pop();

        if (end == next)
            return true;

        if (visited.find(next) == visited.end())
        {
            visited.insert(next);
            for (node_iterator it = next->nb_begin();
                 it != next->nb_end(); it++)
            {
                if (visited.find(*it) == visited.end())
                    nodes.push(*it);
            }
        }
    }
    return false;
}

// DFS
bool DFS::connected(Node *begin, Node *end)
{
    visited.clear();
    return connected(begin, end, 0);
}

bool DFS::connected(Node *begin, Node *end, int depth)
{
    if (begin == end)
        return true;

    visited.insert(begin);

    for (node_iterator it = begin->nb_begin();
         it != begin->nb_end(); it++)
    {
        if (visited.find(*it) == visited.end())
        {
            if (connected(*it, end, depth + 1))
                return true;
        }
    }
    return false;
}

// PriorityQueue
MarkedNode PriorityQueue::pop()
{
    // Находим элемент с минимальным mark
    int minIndex = 0;
    for (size_t i = 1; i < nodes.size(); i++)
    {
        if (nodes[i].mark < nodes[minIndex].mark)
            minIndex = i;
    }
    MarkedNode mn = nodes[minIndex];
    // Удаляем элемент с минимальным весом
    nodes.erase(nodes.begin() + minIndex);
    return mn;
}

void PriorityQueue::push(Node *node, int mark, Node *prev)
{
    MarkedNode mn(node, mark, prev);
    nodes.push_back(mn);
}

// Dijkstra
Way Dijkstra::shortestWay(Node *begin, Node *end)
{
    if (begin == end)
    {
        Way way;
        way.nodes.push_back(begin);
        way.length = 0;
        return way;
    }

    PriorityQueue nodes;
    nodes.push(begin, 0, nullptr);
    map<Node *, MarkedNode> visited;

    while (!nodes.empty())
    {
        MarkedNode next = nodes.pop();

        // Если уже посещали этот узел с лучшим путём — пропускаем
        if (visited.find(next.node) != visited.end())
            continue;

        visited[next.node] = next;

        if (end == next.node)
            return unroll(visited, begin, end);

        for (node_iterator it = next.node->nb_begin();
             it != next.node->nb_end(); it++)
        {
            int weight = (*it)->getWeight(next.node) + next.mark;

            // Если соседа ещё не посещали
            if (visited.find(*it) == visited.end())
            {
                nodes.push(*it, weight, next.node);
            }
        }
    }
    return Way(); // путь не найден
}

// unroll
Way unroll(map<Node *, MarkedNode> visited,
           Node *begin, Node *curr)
{
    Way way;
    way.length = visited[curr].mark;

    while (curr != begin)
    {
        way.nodes.push_back(curr);
        curr = visited[curr].prev;
        if (curr == nullptr)
            break;
    }
    way.nodes.push_back(begin);

    reverse(way.nodes.begin(), way.nodes.end());

    return way;
}