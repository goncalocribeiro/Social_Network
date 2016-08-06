#include <iostream>
using namespace std;
int main(){
    int min=1;
    int vertices=250;
    int connections=2000;

    for(int i=0; i<connections; i++){
        int u = min + (rand() % (int)(vertices - min + 1));
        int v = u;

        while(v==u){
            v = min + (rand() % (int)(vertices - min + 1));
        }
        cout << u << " " << v << "\n";

    }

    return 0;
}
