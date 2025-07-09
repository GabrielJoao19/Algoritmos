#include <iostream>
using namespace std;

int recursao(int n){
    if (n == 0){
        return 0;
    }
    else {
        return n + recursao(n-1);
    }
}


int main(){
    int n;
    cout << "digite um numero: " << endl;
    cin >> n;
    cout << "A soma de 0 ate " << n  << " é igual a: " << recursao(n) << endl;


    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}