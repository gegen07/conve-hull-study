#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <vector>
#define fast_input ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define pb push_back
#define ll long long
#define vi vector<int>
#define pii pair<int, int>
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
using namespace ::std;

long op;

const double EPS = 5E-8;
struct pt {
    double x, y;
};

struct line {
    pt v;
    double c;
};

double abs(pt a) {
    return sqrt(a.x*a.x + a.y*a.y);
}

double cross(pt a, pt b) {
    return a.x*b.y - a.y*b.x;
}

line create_line(pt a, pt b) {
    line line_comp;
    line_comp.v.x = b.x - a.x;
    line_comp.v.y = b.y - a.y;
    line_comp.c = cross(line_comp.v, a);

    return line_comp;  
}

int side(line line_comp, pt a, int total_value=0) {
    double val = cross(line_comp.v, a)-line_comp.c;

    // cout << val << endl;

    if (!total_value) {
        if (val > EPS) return 1;
        if (val < -EPS) return -1;
        else return 0;    
    }
    return val;
}

double dist(line line_comp, pt a) {
    return (abs(side(line_comp, a, 1))/abs(line_comp.v));
}

vector<vector<pt>> side(vector<pt> pts, line line_comp) {

    vector<pt> left;
    vector<pt> right;

    for (int i=0; i<pts.size(); i++) {
        if (side(line_comp, pts[i]) > 0) {
            left.push_back(pts[i]);
        } else if (side(line_comp, pts[i]) < 0) {
            right.push_back(pts[i]);
        }
    }

    vector<vector<pt>> sides = {left, right};

    return sides;
}

void findHull(vector<pt> sk, pt p, pt q, vector<pt>& ch) {
    vector<vector<pt>> sides;
    
    if (sk.size() == 0) return;

    line line_comp = create_line(p, q);

    double dist_max = dist(line_comp, sk[0]);
    pt c = sk[0];

    for (int i=1; i < sk.size(); i++) {
        double d = dist(line_comp, sk[i]);
        if (d > dist_max) {
            dist_max = d;
            c = sk[i];
        }

        op++;
    }

    ch.push_back(c);

    line seg_pc = create_line(p, c);
    sides = side(sk, seg_pc);
    vector<pt> s1 = sides[1];

    line seg_cq = create_line(c, q);
    sides = side(sk, seg_cq);
    vector<pt> s2 = sides[1];

    findHull(s1, p, c, ch);
    findHull(s2, c, q, ch);
}

vector<pt> quickhull(vector<pt> pts) {
    vector<pt> ch;
    pt leftmost = pts[0];
    pt rightmost = pts[pts.size()-1];

    ch.push_back(leftmost);
    ch.push_back(rightmost);

    vector<vector<pt>> sides = side(pts, create_line(leftmost, rightmost));
    vector<pt> s1 = sides[1];

    sides = side(pts, create_line(rightmost, leftmost));
    vector<pt> s2 = sides[1];

    findHull(s1, leftmost, rightmost, ch);
    findHull(s2, rightmost, leftmost, ch);

    return ch;
}

int main() {
    fast_input;

    // vector<pt> pts = {
    //     {0, 0}, {10, 0}, {0, 10}
    // };

    // vector<pt> pts = {
    //     {41, -6}, {-24, -74}, {-51, -6}, {73, 17}, {-30, -34}
    // };

    // vector<pt> pts = {
    //     {50, 50}, {50, 50}
    // };

    // vector<pt> pts = {
    //     {30, 60}, {0, 30}, {15,25}, {20, 0}, 
    //     {50, 40}, {70, 30}, {55, 20}, {50, 10}
    // };

    // vector<pt> pts = {
    //     {0,0}, {1, -4}, {-1,-5}, {-5, -3},
    //     {-3,-1}, {-1, -3}, {-2, -2}, {-1,-1},
    //     {-2, -1}, {-1, 1}
    // };

    ifstream in;
    vector<long> basic_operations;

    struct stat {
        long op;
        long vertices;
        long npoints;
    };

    vector<stat> stats;

    for (int i=3; i<=15; i+=1) {    
        stat s;

        op = 0;
        vector<pt> pts;
        pt p;

        string filename = "./generators/worst_case_quickhull/"+to_string(i)+".txt"; 
        in.open(filename);

        string line;
        while (getline(in, line)) {
            stringstream s(line);

            s >> p.x >> p.y;  
            pts.push_back(p);
        }


        sort(pts.begin(), pts.end(), [](const pt& a, const pt& b) {
            return a.x < b.x;
        });


        vector<pt> ch = quickhull(pts);

        cout << ch.size() << endl;

        s.op = op;
        s.npoints = pts.size();
        s.vertices = ch.size();

        pts.clear();
        ch.clear();

        stats.push_back(s);

        in.close();
        in.clear();

        // for (pt p: ch) {
        //     cout << p.x << " " << p.y << endl;
        // }
    }

    ofstream out("worst_case_quick_hull.csv");

    out << "n,h,op" << endl;
    for (stat s: stats) {
        out << s.npoints << "," << s.vertices << "," << s.op << endl;
    }


    return 0;
}