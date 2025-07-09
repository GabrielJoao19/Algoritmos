#include <iostream>
using namespace std;

void somaValores(){
    
    cout << "Digite o primeiro valor: " << endl;
    int n1;
    cin >> n1;
    cout << "Digite o segundo valor: " << endl;
    int n2;
    cin >> n2;

    int soma = n1 + n2;

    cout << "O resultado da soma é : " << soma << endl;

    cout << "Digite 1 se desejar executar o programa novamente." << endl;

    int valor;
    cin >> valor;

    if (valor == 1){
        somaValores();
    }
    else{
        exit(0);
    }
}

int main(){

    somaValores();

    return 0;
}