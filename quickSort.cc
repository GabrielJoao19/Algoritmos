#include <iostream>
#include <algorithm>
#include <string>
#include <random>
using namespace std;


int array[] gerarVetorAleatorio(int tamanho) {
    if (tamanho < 0) {
        tamanho = 0;
    }

    const int MIN_VALOR_PADRAO = 1;
    const int MAX_VALOR_PADRAO = 100;

    // 1. Criar um gerador de números aleatórios de alta qualidade (Mersenne Twister)
    random_device rd;
    mt19937 gerador(rd()); 

    // 2. Definir a distribuição dos números aleatórios
    uniform_int_distribution<> dist(MIN_VALOR_PADRAO, MAX_VALOR_PADRAO);

    // 3. Criar o vetor com o tamanho especificado
    vector<int> vetorAleatorio(tamanho);

    // 4. Preencher o vetor com números aleatórios
    for (int i = 0; i < tamanho; ++i) {
        vetorAleatorio[i] = dist(gerador); 
    }

    return vetorAleatorio;
}
//Quero que essa funcao retorne o pivo
int particionar(vector<int>& arr,int inicio,int fim){
    int pivo = arr[fim];

    int i = inicio - 1;

    for (int j = inicio; j < fim; j++){
        if (arr[j]<= pivo){
            i ++;
            swap(arr[j], arr[i]);
        }
    }

    swap(arr[i+1], pivo);

    return i+1;

}

int quickSort(vector<int>& arr, int inicio, int fim){
    
    if (inicio > fim){
        int pivoIndice = particionar(arr, inicio, fim);
        // a esquerda do pivo
        quickSort(arr , inicio, pivoIndice - 1);
        // a direita do pivo
        quickSort(arr, pivoIndice + 1, fim);
    }
}



int main(){

    cout << "Digite o tamanho do array que voce quer gerar: " << endl;
    int t;
    cin >> t;

    vector<int> vetor = gerarVetorAleatorio(10);
    int fim = vetor.size();

    cout << "Qual algoritmo deseja utilizar, Quick Sort ou Merge Sort? " << endl;
    string a;
    cin >> a;

    if (a == "Quick Sort" || a == "quick sort"){
        quickSort(vetor, 0, fim);
    }
    else if(a == "Merge Sort" || a == "merge sort"){
        mergeSort(vetor);
    }















    return 0;
}