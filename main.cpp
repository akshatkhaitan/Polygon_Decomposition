#include <bits/stdc++.h>
#include <time.h>
using namespace std;

#include "DCEL.hpp"
#include "Rectangle.hpp"

void build_polygon(DCEL &dcel, const vector<Point *> &polygon)
{
    // Add vertices to DCEL and store their indices
    vector<int> indices;
    for (int i = 0; i < polygon.size(); i++)
    {
        dcel.add_point(polygon[i]->x, polygon[i]->y);
        indices.push_back(i);
    }

    // Add half-edges to DCEL and connect them
    for (int i = 0; i < indices.size(); i++)
    {
        int j = (i + 1) % indices.size(); // index of next vertex
        Point *v1 = dcel.points[indices[i]];
        Point *v2 = dcel.points[indices[j]];
        dcel.add_half_edge(i, j, v1, v2); // adds both the half edges between
    }
    dcel.connect_half_edges();
}
bool check_inside_polygon(Point *p, deque<int> v, DCEL &dcel)
{
    double flag = -1;
    for (int i = 0; i < v.size(); i++)
    {
        Point *p1 = dcel.points[v[i]];
        Point *p2 = dcel.points[v[(i + 1) % v.size()]];
        double x = p->x;
        double y = p->y;
        double x1 = p1->x;
        double y1 = p1->y;
        double x2 = p2->x;
        double y2 = p2->y;
        if (flag == -1)
        {
            flag = (y - y1) * (x2 - x1) - (x - x1) * (y2 - y1);
            if(flag == 0)
                return false;
        }
        else
        {
            double temp = (y - y1) * (x2 - x1) - (x - x1) * (y2 - y1);
            if (flag * temp <= 0)
                return false;
        }
    }
    return true;
}
bool check_notch(Point *p, Point *q, Point *r)
{
    double a = p->x;
    double b = p->y;
    double c = q->x;
    double d = q->y;
    double e = r->x;
    double f = r->y;
    double a1 = (a - c);
    double a2 = (b - d);
    double b1 = (e - c);
    double b2 = (f - d);
    double temp = a1 * b2 - a2 * b1;
    return temp < 0;
}
double helper(double x1, double y1, double x2, double y2, double x, double y)
{
    return (y - y1) * (x2 - x1) - (x - x1) * (y2 - y1);
}
deque<int> semiplane_reduction(int v, deque<int> L, DCEL &dcel)
{
    int v1 = L.front();
    deque<int> L1;
    double x1 = dcel.points[v1]->x;
    double y1 = dcel.points[v1]->y;
    double x2 = dcel.points[v]->x;
    double y2 = dcel.points[v]->y;
    double x = dcel.points[L.back()]->x;
    double y = dcel.points[L.back()]->y;
    int flag = -1;
    flag = helper(x1, y1, x2, y2, x, y);
    for (int i : L)
    {
        x = dcel.points[i]->x;
        y = dcel.points[i]->y;
        if (flag * helper(x1, y1, x2, y2, x, y) < 0)
            L1.push_back(i);    
    }
    return L1;
}
void polygon_decomposition(DCEL &dcel, int start)
{
    int n1 = dcel.points.size();
    deque<int> P;
    for (int i = 0; i < n1; i++)
        P.push_back(i);
    deque<int> L;
    int m = 0;
    L.push_back(P[start]);
    while (P.size() > 3)
    {
        int n = P.size();
        int v1 = L.back();
        int v2;
        int j;
        for (j = 0; j < n; j++)
            if (P[j] == v1)
                break;
        v2 = P[(j + 1) % n];
        L.clear();
        L.push_back(v1);
        L.push_back(v2);
        int i = (j + 1) % n;
        Point *p1 = dcel.points[v1];                   // First Point in the List
        Point *p2 = dcel.points[v2];                   // Secod Point in the list
        Point *p3 = dcel.points[P[i]];                 // Last point added
        Point *p4 = dcel.points[P[(i + 1) % n]];       // point I want to add
        Point *p5 = dcel.points[P[(n + (i - 1)) % n]]; // Last to Last Point Added

        // 3.3
        while (L.size() < n && !check_notch(p5, p3, p4) && !check_notch(p3, p4, p1) && !check_notch(p4, p1, p2))
        {
            L.push_back(P[(i + 1) % n]);
            p5 = p3;
            p3 = p4;
            i = (i + 1) % n;
            p4 = dcel.points[P[(i + 1) % n]];
        }

        // 3.4
        if (L.size() != P.size() && L.size() != 2)
        {

            // 3.4.1
            deque<int> temp;
            for (int j = 0; j < P.size(); j++)
            {
                int flag = 1;
                for (int k = 0; k < L.size(); k++)
                {
                    if (P[j] == L[k])
                        flag = 0;
                }
                if (flag == 1)
                    temp.push_back(P[j]);
            }
            // checking notches
            deque<int> LPVS;
            for (int k = 0; k < temp.size(); k++)
            {
                Point *p1 = dcel.points[temp[k]];
                Point *p2 = dcel.points[(temp[k] + 1) % dcel.points.size()];
                Point *p3 = dcel.points[(dcel.points.size() + (temp[k] - 1)) % dcel.points.size()];
                if (check_notch(p3, p1, p2))
                    LPVS.push_back(temp[k]);
            }
            // 3.4.2

            while (LPVS.size() > 0)
            {
                // point 1
                Rectangle *r = new Rectangle();
                for (auto i : L)
                    r->setLimit(dcel.points[i]);

                // point 2
                bool backward = false;
                // deque<int> LPVS;
                while (!backward && LPVS.size() > 0)
                {
                    int v;
                    do
                    {
                        v = LPVS.front();
                        if (r->checkInside(dcel.points[v]))
                            break;
                        else
                            LPVS.pop_front();
                    } while (LPVS.size() != 0);

                    if (LPVS.size() > 0)
                    {
                        if (check_inside_polygon(dcel.points[v], L, dcel))
                        {
                        cout<<L.size()<<endl;
                        L = semiplane_reduction(v, L, dcel);
                        cout<<L.size()<<endl;
                            backward = true;
                        }
                        LPVS.pop_front();
                    }

                }
            }
        }

        // 3.5 here
        if (L.back() != L[1])
        {
            int v1 = L.back();
            int v2 = L[0];
            dcel.add_half_edge(v1, v2, dcel.points[v1], dcel.points[v2]);
            // dcel.utility(v1, v2);
            deque<int> temp;
            set<int> s;
            for (int i = 1; i < L.size() - 1; i++)
                s.insert(L[i]);
            for (int i = 0; i < P.size(); i++)
            {
                if (s.find(P[i]) == s.end())
                    temp.push_back(P[i]);
            }
            P = temp;
        }
    cout<<"HeloS"<<endl;
        cout<<P.size()<<endl;
        cout<<L.size()<<endl;
        for(auto i:L)
            cout<<i<<" ";
        cout<<endl;
        for(auto i:P)
            cout<<i<<" ";
        cout<<endl;
    }
}

int main()
{
    ofstream fout, fout2, fout3;
    ifstream in1;
    in1.open("input.txt");
    fout.open("output_after.txt");
    fout2.open("output_before.txt");
    fout3.open("timing.txt");
    // start timer
    int n;
    in1 >> n;
    double min_time = INT_MAX;
    DCEL min_dcel;
    vector<Point *> polygon(n);
    vector<int> pt;
    for (int i = 0; i < n; i++)
        {
            pt.push_back(i);
            double t_x, t_y;
            in1 >> t_x >> t_y;
            polygon[i] = new Point(t_x, t_y);
        }
        //output before
        for (int i = 0; i < n; i++)
        {
            fout2 << polygon[i]->x << " " << polygon[i]->y;
            if (i != n - 1)
                fout2 << "\n";
        }
    // for (int index = 0; index < 52; index++)
    // {
    //         cout<<"Hello "<<index<<endl;
        DCEL dcel;        
        build_polygon(dcel, polygon);
             
        clock_t start;
        start = clock();
        polygon_decomposition(dcel, 0);
        // end timer
        clock_t end;
        end = clock();
        double time = ((end - start) / (double)CLOCKS_PER_SEC) * 1000;
        fout3 << time << endl;
        if (time < min_time)
        {
            min_dcel = dcel;
            min_time = time;
        }
//    }

    for (int i = 0; i < min_dcel.half_edges.size(); i += 2)
    {
        fout << min_dcel.points[min_dcel.half_edges[i]->origin]->x << " " << min_dcel.points[min_dcel.half_edges[i]->origin]->y << endl;
        fout << min_dcel.points[min_dcel.half_edges[i]->twin->origin]->x << " " << min_dcel.points[min_dcel.half_edges[i]->twin->origin]->y << endl;
    }
    fout.close();
    return 0;
}
