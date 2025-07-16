#include <iostream>
#include <random>
#include <chrono>
using namespace std;

void preencherArrayAleatorio(int arr[], int tamanho, int min_val, int max_val) {
    // Semente para o gerador de números aleatórios
    // É importante inicializar o gerador UMA VEZ, geralmente na main
    // ou passar um gerador já inicializado para a função.
    // Para simplificar, estamos inicializando aqui, mas para muitas chamadas,
    // o ideal seria passar 'gen' como parâmetro ou usar uma semente mais robusta.
    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());

    // Definição da distribuição dos números
    uniform_int_distribution<> distrib(min_val, max_val);

    // Preenche o array
    for (int i = 0; i < tamanho; ++i) {
        arr[i] = distrib(gen);
    }
}

// BINARIA ITERATIVA
int buscaBinariaIterativa(int arr[], int tamanho, int chave) {
    int inicio = 0;
    int fim = tamanho - 1;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        if (arr[meio] == chave)
            return meio; // encontrado
        else if (arr[meio] < chave)
            inicio = meio + 1;
        else
            fim = meio - 1;
}
    return -1; // não encontrado
}

// BINARIA RECURSIVA
int buscaBinariaRecursiva(int arr[], int chave, int inicio, int fim) {
    if (inicio > fim)
        return -1;
        int meio = inicio + (fim - inicio) / 2;
    if (arr[meio] == chave)
        return meio;
    else if (arr[meio] < chave)
        return buscaBinariaRecursiva(arr, chave, meio + 1, fim);
    else
        return buscaBinariaRecursiva(arr, chave, inicio, meio - 1);
}
// BUSCA LINEAR
int buscaLinear(int arr[], int tamanho, int chave) {
    for (int i = 0; i < tamanho; i++) {
        if (arr[i] == chave)
            return i;
    }
    return -1; // não encontrado
}

int main() {
    int arr[10000];
    preencherArrayAleatorio(arr,10000, 1, 1000);

    buscaLinear(arr, 10000, 158);

    
    buscaBinariaIterativa(arr, 10000,158);
    buscaBinariaRecursiva(arr, 158,0,9999);























    return 0;
}

