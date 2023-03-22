#ifndef DCEL_HPP
#define DCEL_HPP

#include <bits/stdc++.h>
#include "Point.hpp"
#include "HalfEdge.hpp"
#include "Face.hpp"

using namespace std;


class DCEL
{
public:
    vector<Point *> points;
    vector<HalfEdge *> half_edges;
    vector<Face *> faces;

    // Function that adds a point to the DCEL and returns its index
    void add_point(double x, double y);
    // Function that adds a half-edge to the DCEL and returns its index
    void add_half_edge(int i, int j, Point* v1, Point* p2);
    // Function that adds a face to the DCEL and returns its index
    int add_face(int edge);
    // Function that connects two half-edges together by setting their next pointers to each other
    void addDiagonal(int i, int j);
    void connect_half_edges();
    void merge();

};

void DCEL::add_point(double x, double y)
{
    points.emplace_back(new Point(x, y));
}

void DCEL::add_half_edge(int i, int j, Point* v1, Point* v2)
{
    HalfEdge *he1 = new HalfEdge(i);
    HalfEdge *he2 = new HalfEdge(j);
    he1->twin = he2;
    he2->twin = he1;
    he1->next = NULL;
    he2->next = NULL;
    half_edges.push_back(he1);
    half_edges.push_back(he2);   
    v1->incident_edge = he1;
}

int DCEL::add_face(int edge)
{
    Face *f = new Face(faces.size(), edge);
    faces.push_back(f);
    return faces.size() - 1;
}

void DCEL::connect_half_edges()
{
    for(int i = 0; i < half_edges.size(); i+=2)
        half_edges[i]->next = half_edges[(i+2)%half_edges.size()];
    for(int i = half_edges.size() - 1; i >= 0; i-=2)
        half_edges[i]->next = half_edges[(half_edges.size() + (i-2)) %half_edges.size()];
}

#endif