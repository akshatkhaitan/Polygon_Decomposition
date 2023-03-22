#include<bits/stdc++.h>
using namespace std;

struct Vertex;
struct HalfEdge;

struct Vertex {
    double x, y;
    HalfEdge* incident_edge;
};

struct HalfEdge {
    Vertex* origin;
    HalfEdge* twin;
    HalfEdge* next;
};

class DCEL {
public:
    vector<Vertex*> vertices;
    vector<HalfEdge*> half_edges;
    DCEL() {}
    void add_vertex(double x, double y) {
        Vertex* v = new Vertex;
        v->x = x;
        v->y = y;
        v->incident_edge = NULL;
        vertices.push_back(v);
    }
    void add_half_edge(Vertex* v1, Vertex* v2) {
        HalfEdge* he1 = new HalfEdge;
        HalfEdge* he2 = new HalfEdge;
        he1->origin = v1;
        he2->origin = v2;
        he1->twin = he2;
        he2->twin = he1;
        he1->next = NULL;
        he2->next = NULL;
        v1->incident_edge = he1;
        half_edges.push_back(he1);
        half_edges.push_back(he2);
    }
};

int main() {
    DCEL dcel;
    dcel.add_vertex(0, 0);
    dcel.add_vertex(1, 0);
    dcel.add_vertex(1, 1);
    dcel.add_vertex(0, 1);
    dcel.add_half_edge(dcel.vertices[0], dcel.vertices[1]);
    dcel.add_half_edge(dcel.vertices[1], dcel.vertices[2]);
    dcel.add_half_edge(dcel.vertices[2], dcel.vertices[3]);
    dcel.add_half_edge(dcel.vertices[3], dcel.vertices[0]);
    return 0;
}