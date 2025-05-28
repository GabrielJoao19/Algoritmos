#include <iostream>
#include <cmath>
using namespace std;
struct Ponto{
    int x,y;
};

float calcDist(Ponto p1, Ponto p2){
    return sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));
}

int main() {
    Ponto p1;
    int n;

    cout << "digite os eixos x e y do ponto:";
    cin >> p1.x >> p1.y;

    cout << "digite a quantidade de pontos:";
    cin >> n;

    for (int i=0;i<n;i++){
        Ponto x;
        cout << "digite os eixos x e y do ponto:";
        cin >> x.x >> x.y;
        
        calcDist(p1,x)

        if ()
    }
}