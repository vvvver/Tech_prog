#include "graph.h"
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <QString>

using namespace std;

    edge::edge(int val) : next(nullptr), prev(nullptr), val(val) {}

    vertex::vertex(int numb) : index(numb), first(nullptr), last(nullptr), next(nullptr), prev(nullptr), cnt(0) {}

    bool vertex::push(int val) {
        edge* n = new edge(val);
        if (first == nullptr) {
            first = last = n;
            cnt++;
            return true;
        }
        last->next = n;
        n->prev = last;
        last = n;
        cnt++;
        return true;
    }

    bool vertex::pop(int index) {
        if (index >= cnt or index < 0) {
            return false;
        }
        if (cnt == 1) {
            edge* p = last;
            first = last = nullptr;
            delete p;
            cnt--;
            return true;
        }
        if (cnt / 2 - 1 < index) {
            edge* p = last;
            for (int i = 0; i < cnt - index - 1; i++) {
                p = p->prev;
            }
            if (p->next == nullptr) {
                last->prev->next = nullptr;
                last = last->prev;
                delete p;
                cnt--;
                return true;
            }
            p->next->prev = p->prev;
            p->prev->next = p->next;
            delete p;
            cnt--;
            return true;
        }
        else {
            edge* p = first;
            for (int i = 0; i < index; i++) {
                p = p->next;
            }
            if (p->prev == nullptr) {
                p->next->prev = nullptr;
                first = p->next;
                delete p;
                cnt--;
                return true;
            }
            p->next->prev = p->prev;
            p->prev->next = p->next;
            delete p;
            cnt--;
            return true;
        }
    }

    void vertex::print() {
        edge* p = first;
        int x(0);
        while (p) {
            cout << "  " << x << ": " << p->val << "\n";
            p = p->next;
            x++;
        }
        cout << "\n";
    }

    vertex* list_graph::find_vertex(int index) {
        vertex* v = first;
        while (v != nullptr) {
            if (v->index == index) {
                return v;
            }
            v = v->next;
        }
        return nullptr;
    }

    list_graph::list_graph() : first(nullptr), last(nullptr), cnt(0) {}

    QString list_graph::BFS(int start_index, int end_index) {
        unordered_map<int, bool> visited;
        unordered_map<int, int> distance;
        unordered_map<int, int> parent;
        queue<int> q;

        q.push(start_index);
        visited[start_index] = true;
        distance[start_index] = 0;
        parent[start_index] = -1;

        while (!q.empty()) {
            int current_index = q.front();
            q.pop();

            vertex* v = find_vertex(current_index);
            if (v != nullptr) {
                edge* e = v->first;
                while (e != nullptr) {
                    if (!visited[e->val]) {
                        visited[e->val] = true;
                        distance[e->val] = distance[current_index] + 1;
                        parent[e->val] = current_index;
                        q.push(e->val);

                        if (e->val == end_index) {
                            break;
                        }
                    }
                    e = e->next;
                }
            }
        }

        if (!visited[end_index]) {
            return "No path from vertex " + QString::number(start_index) + " to vertex " + QString::number(end_index);
        }

        QString result = "Shortest distance from vertex " + QString::number(start_index) + " to vertex " + QString::number(end_index) + " is: " + QString::number(distance[end_index]) + "\r\nPath: ";
        stack<int> path;
        for (int step = end_index; step != -1; step = parent[step]) {
            path.push(step);
        }
        while (!path.empty()) {
            result += QString::number(path.top());
            path.pop();
            if (!path.empty()) {
                result += " -> ";
            }
        }

        return result;
    }

    bool list_graph::push(int index, int val) {
        if (first == nullptr) {
            vertex* n = new vertex(index);
            n->push(val);
            first = last = n;
            cnt++;
            return true;
        }
        if (first == last) {
            vertex* n = new vertex(index);
            n->push(val);
            if (n->index == last->index) {
                last->push(val);
                return true;
            }
            last->next = n;
            n->prev = last;
            last = n;
            cnt++;
            return true;
        }
        vertex* p1 = first;
        vertex* p2 = last;
        for (int i = 0; i < cnt / 2 + cnt % 2; i++) {
            if (p1->index == index) {
                p1->push(val);
                return true;
            }
            if (p2->index == index) {
                p2->push(val);
                return true;
            }
            p1 = p1->next;
            p2 = p2->prev;
        }
        vertex* n = new vertex(index);
        n->push(val);
        last->next = n;
        n->prev = last;
        last = n;
        cnt++;
        return true;
    }
    bool list_graph::pop(int index) {
        if (index >= cnt or index < 0) {
            return false;
        }
        if (cnt == 1) {
            vertex* p = last;
            for (int i = 0; i < p->cnt; i++) {
                p->pop(i);
            }
            first = last = nullptr;
            delete p;
            return true;
        }
        if (cnt / 2 - 1 < index) {
            vertex* p = last;
            for (int i = 0; i < cnt - index - 1; i++) {
                p = p->prev;
            }
            if (p->next == nullptr) {
                last->prev->next = nullptr;
                last = last->prev;
                for (int i = 0; i < p->cnt; i++) {
                    p->pop(i);
                }
                delete p;
                cnt--;
                return true;
            }
            p->next->prev = p->prev;
            p->prev->next = p->next;
            for (int i = 0; i < p->cnt; i++) {
                p->pop(i);
            }
            delete p;
            cnt--;
            return true;
        }
        else {
            vertex* p = first;
            for (int i = 0; i < index; i++) {
                p = p->next;
            }
            if (p->prev == nullptr) {
                p->next->prev == nullptr;
                first = p->next;
                for (int i = 0; i < p->cnt; i++) {
                    p->pop(i);
                }
                delete p;
                cnt--;
                return true;
            }
            p->next->prev = p->prev;
            p->prev->next = p->next;
            for (int i = 0; i < p->cnt; i++) {
                p->pop(i);
            }
            delete p;
            cnt--;
            return true;
        }
    }
    bool list_graph::pop(int index_vertex, int index_edge) {
        if (index_vertex >= cnt or index_vertex < 0) {
            return false;
        }
        if (cnt == 1) {
            vertex* p = last;
            p->pop(index_edge);
            return true;
        }
        if (cnt / 2 - 1 < index_vertex) {
            vertex* p = last;
            for (int i = 0; i < cnt - index_vertex - 1; i++) {
                p = p->prev;
            }
            p->pop(index_edge);
            return true;
        }
        else {
            vertex* p = first;
            for (int i = 0; i < index_vertex; i++) {
                p = p->next;
            }
            p->pop(index_edge);
            return true;
        }
    }

    void list_graph::print() {
        vertex* p = first;
        while (p) {
            cout << p->index << "\n";
            p->print();
            p = p->next;
        }
        cout << "\n";
    }
