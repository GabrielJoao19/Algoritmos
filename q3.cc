#include <iostream> 
using namespace std;

// Função Fibonacci Recursiva
int fibonacciRecursivo(int n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
    }
}

// Função Fibonacci Iterativa
void fibonacciIterativo(int n) {
    
    if (n == 1){
        cout << 0 << 1;
        return;
    }
    
    int a = 0;
    int b = 1;
    
    cout << a << " " ;
    cout << b << " " ;

    int proximo = 0;

    for (int i = 2; i <= n; ++i) {
        proximo = a + b;
        cout << proximo << " ";
        a = b;
        b = proximo;
    }
}

// Função Fatorial Recursiva
int fatorialRecursivo(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * fatorialRecursivo(n - 1);
    }
}

// Função Fatorial Iterativa
int fatorialIterativo(int n) {
    if (n == 0) {
        return 1;
    }

    int resultado = 1;
    for (int i = 1; i <= n; ++i) {
        resultado *= i;
    }
    return resultado;
}


int main() {
    int numero;

    cout << "Digite um número para Fibonacci: ";
    cin >> numero;

    if (numero < 0) {
        cout << "Número não pode ser negativo." << endl;
    } else {
        cout << "Fibonacci Recursivo(" << numero << "): " << fibonacciRecursivo(numero) << endl;
        fibonacciIterativo(numero); 
    }

    cout << "Digite um número para Fatorial: ";
    cin >> numero;

    if (numero < 0) {
        cout << "Número não pode ser negativo" << endl;
    } else {
        cout << "Fatorial Recursivo(" << numero << "): " << fatorialRecursivo(numero) << endl;
        cout << "Fatorial Iterativo(" << numero << "): " << fatorialIterativo(numero) << endl;
    }

    return 0;
}