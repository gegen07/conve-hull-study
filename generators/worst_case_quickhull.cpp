#include <bits/stdc++.h>
#include <string>
// n-3*n-2 = n^2 -5 +6
// n+1*n+2 = n^2 + 3n + 2

// Worst Case for gift-wrapping
// Best case for quickhull

using namespace ::std;

int main() {
    for (int p = 3; p <= 15; p+=1) {
        double r=64, d=3/4.0; 

        ofstream f;

        string filename = "worst_case_quickhull/" + std::to_string(p) + ".txt";
        f.open(filename);

        int i=0;
        
        double x,y,t;
        
        while(i<p) {

            t=((M_PI))/pow(2, i);
            x=cos(t)*r;
            y=sin(t)*r;
            f << x << " " << y << endl;
        

            i++;
        }

        f.close();
    }
    
}