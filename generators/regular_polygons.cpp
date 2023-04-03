#include <bits/stdc++.h>
#include <string>

// Worst Case for gift-wrapping
// Best case for quickhull

using namespace ::std;

int main() {
    for (int p = 50; p <= 2000; p+=25) {
        double r=2000, d=3/4.0;

        ofstream f;

        string filename = "regular_polygons/" + std::to_string(p) + ".txt";
        f.open(filename);

        int i=0;
        
        double x,y,t;
        
        while(i<p) {
            t=2*M_PI*((double)i/p+d);
            x=cos(t)*r;
            y=sin(t)*r;
            f << x << " " << y << endl;
            i++;
        }

        f.close();
    }
    
}