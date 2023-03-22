

#ifndef HALFEDGE_HPP
#define HALFEDGE_HPP

#include <bits/stdc++.h>
using namespace std;

class HalfEdge
{
public:
    int origin; // index of the originating vertex in DCEL::points
    HalfEdge* twin;   // index of the twin half-edge in DCEL::half_edges
    HalfEdge* next;   // index of the next half-edge in the face
    HalfEdge(int);
};

HalfEdge::HalfEdge(int a)
{
    origin = a;
    twin = NULL;
    next = NULL;
}

#endif