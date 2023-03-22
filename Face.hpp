#ifndef FACE_HPP
#define FACE_HPP

class Face
{
public:
    int id;
    int edge; // index of a half-edge on the boundary of the face in DCEL::half_edges
    Face(int , int);
};

Face::Face(int a, int b)
{
    id = a;
    edge = b;
}

#endif