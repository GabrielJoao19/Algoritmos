#include <iostream>
#include <random>
#include <chrono>
#include <algorithm> // Para std::sort

using namespace std;

void preencherArrayAleatorio(int arr[], int tamanho, int min_val, int max_val) {
    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<> distrib(min_val, max_val);

    for (int i = 0; i < tamanho; ++i) {
        arr[i] = distrib(gen);
    }
}

// BINARIA RECURSIVA (Mantida como recursiva)
int buscaBinariaRecursiva(int arr[], int chave, int inicio, int fim) {
    if (inicio > fim)
        return -1; // Não encontrado
    
    int meio = inicio + (fim - inicio) / 2;
    
    if (arr[meio] == chave)
        return meio; // Encontrado
    else if (arr[meio] < chave)
        return buscaBinariaRecursiva(arr, chave, meio + 1, fim); // Busca na metade direita
    else
        return buscaBinariaRecursiva(arr, chave, inicio, meio - 1); // Busca na metade esquerda
}

// BUSCA LINEAR ITERATIVA (Revertida para iterativa)
int buscaLinearIterativa(int arr[], int tamanho, int chave) {
    for (int i = 0; i < tamanho; i++) {
        if (arr[i] == chave)
            return i; // Encontrado
    }
    return -1; // Não encontrado
}

int main() {
    const int TAMANHO_ARRAY = 10000;
    int arr[TAMANHO_ARRAY]; 

    // Preenche o array com valores aleatórios
    preencherArrayAleatorio(arr, TAMANHO_ARRAY, 1, 100000); 

    // Define a chave a ser buscada
    // Usamos uma chave que provavelmente não está no array original aleatório
    // para demonstrar o pior caso de busca linear.
    // Para testar o caso de chave encontrada, você pode usar: int chaveBusca = arr[TAMANHO_ARRAY / 2];
    int chaveBusca = 999999; 
    
    cout << "Realizando buscas para a chave: " << chaveBusca << endl;
    cout << "------------------------------------------" << endl;

    // --- Busca Linear Iterativa ---
    auto inicioLinearIterativa = chrono::high_resolution_clock::now();
    int resultadoLinearIterativa = buscaLinearIterativa(arr, TAMANHO_ARRAY, chaveBusca);
    auto fimLinearIterativa = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracaoLinearIterativa = fimLinearIterativa - inicioLinearIterativa;

    cout << "Busca Linear Iterativa:" << endl;
    if (resultadoLinearIterativa != -1) {
        cout << "   Chave encontrada na posicao: " << resultadoLinearIterativa << endl;
    } else {
        cout << "   Chave nao encontrada." << endl;
    }
    cout << "   Tempo gasto: " << duracaoLinearIterativa.count() << " ms" << endl;
    cout << "------------------------------------------" << endl;

    // --- Ordenação do Array para Busca Binária ---
    // É importante ordenar o array ANTES de realizar as buscas binárias.
    auto inicioOrdenacao = chrono::high_resolution_clock::now();
    sort(arr, arr + TAMANHO_ARRAY); // Ordena o array
    auto fimOrdenacao = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracaoOrdenacao = fimOrdenacao - inicioOrdenacao;
    cout << "Array ordenado para Busca Binaria." << endl;
    cout << "   Tempo gasto na ordenacao: " << duracaoOrdenacao.count() << " ms" << endl;
    cout << "------------------------------------------" << endl;

    // --- Busca Binária Recursiva ---
    auto inicioBinariaRecursiva = chrono::high_resolution_clock::now();
    int resultadoBinariaRecursiva = buscaBinariaRecursiva(arr, chaveBusca, 0, TAMANHO_ARRAY - 1);
    auto fimBinariaRecursiva = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracaoBinariaRecursiva = fimBinariaRecursiva - inicioBinariaRecursiva;

    cout << "Busca Binaria Recursiva:" << endl;
    if (resultadoBinariaRecursiva != -1) {
        cout << "   Chave encontrada na posicao: " << resultadoBinariaRecursiva << endl;
    } else {
        cout << "   Chave nao encontrada." << endl;
    }
    cout << "   Tempo gasto: " << duracaoBinariaRecursiva.count() << " ms" << endl;
    cout << "------------------------------------------" << endl;

    return 0;
}