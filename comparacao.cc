#include <iostream>
#include <random>
#include <chrono>
#include <algorithm> // Para std::sort
#include <vector>    // Para usar std::vector (opcional, mas melhor prática)

using namespace std;

void preencherArrayAleatorio(int arr[], int tamanho, int min_val, int max_val) {
    mt19937 gen(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_int_distribution<> distrib(min_val, max_val);

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

// BUSCA LINEAR ITERATIVA (renomeei para clareza)
int buscaLinearIterativa(int arr[], int tamanho, int chave) {
    for (int i = 0; i < tamanho; i++) {
        if (arr[i] == chave)
            return i;
    }
    return -1; // não encontrado
}

// BUSCA LINEAR RECURSIVA (NOVA)
int buscaLinearRecursiva(int arr[], int tamanho, int chave, int indiceAtual = 0) {
    if (indiceAtual == tamanho) {
        return -1;
    }
    if (arr[indiceAtual] == chave) {
        return indiceAtual;
    }
    return buscaLinearRecursiva(arr, tamanho, chave, indiceAtual + 1);
}

int main() {
    const int TAMANHO_ARRAY = 10000;
    int arr[TAMANHO_ARRAY]; 

    // Preenche o array com valores aleatórios
    preencherArrayAleatorio(arr, TAMANHO_ARRAY, 1, 100000); 

    // Define a chave a ser buscada
    // Escolha uma chave que provavelmente estará no array.
    // Para garantir que a chave exista, você pode pegá-la de dentro do array aleatório.
    // Se quiser testar o caso de não encontrar, use um valor como 999999.
    int chaveBusca = arr[TAMANHO_ARRAY / 3]; // Exemplo: pega um valor existente no array aleatório
    
    cout << "Realizando buscas para a chave: " << chaveBusca << endl;
    cout << "------------------------------------------" << endl;

    // --- Busca Linear Iterativa ---
    auto inicioLinearIterativa = chrono::high_resolution_clock::now();
    int resultadoLinearIterativa = buscaLinearIterativa(arr, TAMANHO_ARRAY, chaveBusca);
    auto fimLinearIterativa = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracaoLinearIterativa = fimLinearIterativa - inicioLinearIterativa;

    cout << "Busca Linear Iterativa:" << endl;
    if (resultadoLinearIterativa != -1) {
        cout << "  Chave encontrada na posicao: " << resultadoLinearIterativa << endl;
    } else {
        cout << "  Chave nao encontrada." << endl;
    }
    cout << "  Tempo gasto: " << duracaoLinearIterativa.count() << " ms" << endl;
    cout << "------------------------------------------" << endl;

    // --- Busca Linear Recursiva ---
    auto inicioLinearRecursiva = chrono::high_resolution_clock::now();
    int resultadoLinearRecursiva = buscaLinearRecursiva(arr, TAMANHO_ARRAY, chaveBusca);
    auto fimLinearRecursiva = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracaoLinearRecursiva = fimLinearRecursiva - inicioLinearRecursiva;

    cout << "Busca Linear Recursiva:" << endl;
    if (resultadoLinearRecursiva != -1) {
        cout << "  Chave encontrada na posicao: " << resultadoLinearRecursiva << endl;
    } else {
        cout << "  Chave nao encontrada." << endl;
    }
    cout << "  Tempo gasto: " << duracaoLinearRecursiva.count() << " ms" << endl;
    cout << "------------------------------------------" << endl;

    // --- Ordenação do Array para Busca Binária ---
    // É importante ordenar o array ANTES de realizar as buscas binárias.
    auto inicioOrdenacao = chrono::high_resolution_clock::now();
    sort(arr, arr + TAMANHO_ARRAY); // Ordena o array
    auto fimOrdenacao = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracaoOrdenacao = fimOrdenacao - inicioOrdenacao;
    cout << "Array ordenado para Busca Binaria." << endl;
    cout << "  Tempo gasto na ordenacao: " << duracaoOrdenacao.count() << " ms" << endl;
    cout << "------------------------------------------" << endl;

    // --- Busca Binária Iterativa ---
    auto inicioBinariaIterativa = chrono::high_resolution_clock::now();
    int resultadoBinariaIterativa = buscaBinariaIterativa(arr, TAMANHO_ARRAY, chaveBusca);
    auto fimBinariaIterativa = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracaoBinariaIterativa = fimBinariaIterativa - inicioBinariaIterativa;

    cout << "Busca Binaria Iterativa:" << endl;
    if (resultadoBinariaIterativa != -1) {
        cout << "  Chave encontrada na posicao: " << resultadoBinariaIterativa << endl;
    } else {
        cout << "  Chave nao encontrada." << endl;
    }
    cout << "  Tempo gasto: " << duracaoBinariaIterativa.count() << " ms" << endl;
    cout << "------------------------------------------" << endl;

    // --- Busca Binária Recursiva ---
    auto inicioBinariaRecursiva = chrono::high_resolution_clock::now();
    int resultadoBinariaRecursiva = buscaBinariaRecursiva(arr, chaveBusca, 0, TAMANHO_ARRAY - 1);
    auto fimBinariaRecursiva = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracaoBinariaRecursiva = fimBinariaRecursiva - inicioBinariaRecursiva;

    cout << "Busca Binaria Recursiva:" << endl;
    if (resultadoBinariaRecursiva != -1) {
        cout << "  Chave encontrada na posicao: " << resultadoBinariaRecursiva << endl;
    } else {
        cout << "  Chave nao encontrada." << endl;
    }
    cout << "  Tempo gasto: " << duracaoBinariaRecursiva.count() << " ms" << endl;
    cout << "------------------------------------------" << endl;

    return 0;
}