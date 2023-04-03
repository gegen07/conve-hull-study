#include <bits/stdc++.h>
#include <fstream>
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

long long op;

struct pt {
    double x, y;
};

int eq(pt a, pt b) {
    return a.x == b.x and a.y == b.y;
}

int orientation (pt a, pt b, pt c) {
    double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
    if (v < 0) return -1;
    if (v > 0) return +1;
    return 0;
}

vector<pt> gift_wrapping(vector<pt> pts) {
    vector<pt> ch;
    pt leftmost = pts[0];
    

    for (int i = 1; i < pts.size(); i++) 
        if (leftmost.x <= pts[i].x) leftmost = pts[i];

    pt pointHull = leftmost;
    
    int i=0;
    while (true) {
        ch.push_back(pointHull);
        pt endpoint = pts[0];

        for (int j=0; j < pts.size(); j++) {
            if (eq(pointHull, endpoint) or orientation(pointHull, endpoint, pts[j])==1) {
                endpoint = pts[j];
            }
            op+=2;
        }

        i++;
        pointHull = endpoint;

        if (eq(endpoint, ch[0])) break;
    }

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


    ifstream in;
    vector<long> basic_operations;

    struct stat {
        long op;
        long vertices;
        long npoints;
    };

    vector<stat> stats;

    for (int i=50; i<=2000; i+=25) {
        cout << i << endl;
        stat s;

        op = 0;
        vector<pt> pts;
        pt p;

        string filename = "./generators/regular_polygons/"+to_string(i)+".txt"; 
        in.open(filename);

        string line;
        while (getline(in, line)) {
            stringstream s(line);

            s >> p.x >> p.y;  
            pts.push_back(p);
        }

        vector<pt> ch = gift_wrapping(pts);

        in.close();
        in.clear();

        s.op = op;
        s.npoints = pts.size();
        s.vertices = ch.size();

        pts.clear();
        ch.clear();

        stats.push_back(s);
    }

    ofstream out("worst_case_gift_wrapping.csv");

    out << "n,h,op,2nh" << endl;
    for (stat s: stats) {
        out << s.npoints << "," << s.vertices << "," << s.op << "," << 2*s.npoints*s.vertices << endl;
    }

    // for (pt p: ch) {
    //     cout << p.x << " " << p.y << endl;
    // }

    return 0;
}