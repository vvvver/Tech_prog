#ifndef GRAPH_H
#define GRAPH_H
#include <QStringList>
#include <iostream>
#include <queue>
#include <list>
#include <stack>
#include <limits>
#include <unordered_map>

struct edge {
    int val;
    edge* next;
    edge* prev;
    edge(int val);
};

struct vertex {
    int index;
    edge* first;
    edge* last;
    vertex* next;
    vertex* prev;
    int cnt;
    vertex(int numb);
    bool push(int val);
    bool pop(int index);
    void print();
};

class list_graph {
    vertex* first;
    vertex* last;
    int cnt;
    vertex* find_vertex(int index);
public:
    list_graph();
    QString BFS(int start_index, int end_index);
    bool push(int index, int val);
    bool pop(int index);
    bool pop(int index_vertex, int index_edge);
    void print();
};


#endif // GRAPH_H
