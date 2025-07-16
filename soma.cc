#include <iostream>
#include <random>
#include <fstream>   // Para leitura de arquivos
#include <string>    // Para manipulação de strings
#include <sstream>   // Para parsing de strings
#include <vector>
#include <unistd.h>  // Para getpid() no Linux
#include <sys/times.h> // Para times() no Linux
#include <climits>   // Para CLK_TCK
#include <chrono>    // Para medir o tempo de execução da ordenação
#include <iomanip>   // Para setprecision e fixed

using namespace std;

// --- Funções de Ordenação Existentes ---

// Função auxiliar para trocar dois elementos
int particionar(int* arr, int inicio, int fim) {
    int pivo = arr[fim]; // Escolhe o último elemento como pivô
    int i = (inicio - 1); // Índice do menor elemento

    for (int j = inicio; j < fim; j++) {
        // Se o elemento atual é menor ou igual ao pivô
        if (arr[j] <= pivo) {
            i++; // Incrementa o índice do menor elemento
            swap(arr[i], arr[j]); // Troca os elementos
        }
    }
    swap(arr[i + 1], arr[fim]); // Coloca o pivô na posição correta
    return (i + 1);
}

// Função de ordenação QuickSort
// A função quickSort recebe um array, o índice inicial e o índice final
int quickSort(int* arr, int inicio, int fim) {
    if (inicio < fim) {
        // Particiona o array
        int pi = particionar(arr, inicio, fim);

        // Recursivamente ordena os elementos antes e depois da partição
        quickSort(arr, inicio, pi - 1);
        quickSort(arr, pi + 1, fim);
    }
    return 0; // O retorno não é estritamente necessário aqui, mas mantém a assinatura
}

void shellSort(int* arr, int n) {
    //controla o tamanho do gap
    // O gap é reduzido a cada iteração, começando pela metade do tamanho do array
    // e diminuindo até 1, o que é o caso do insertion sort.
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            //insertion_sort
            // Move elementos do arr[0..i-gap] que sao maiores que temp
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// --- Funções de Utilitário Existentes ---

// vai gerar um array aleatório de inteiros
int* gerarArrayAleatorio(int tamanho) {
    int* arr = new int[tamanho];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 10000);

    for (int i = 0; i < tamanho; ++i) {
        arr[i] = distrib(gen);
    }
    return arr;
}
// Imprime o array
// Se o tamanho do array for maior que 100, imprime apenas os primeiros e últimos
void imprimirArray(const int* arr, int tamanho) {
    for (int i = 0; i < tamanho; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// --- Novas Funções para Métricas ---

// Estrutura para armazenar o tempo de CPU
struct CpuTime {
    long user_hz;
    long system_hz;
};

// Lê o tempo de CPU do processo atual (em ticks de clock)
// Retorna um struct CpuTime com o tempo de usuário e sistema
CpuTime getProcessCpuTime() {
    struct tms time_buffer;
    times(&time_buffer); // Preenche a estrutura tms com os tempos de processo

    CpuTime cpu_time;
    cpu_time.user_hz = time_buffer.tms_utime;  // Tempo de usuário em ticks
    cpu_time.system_hz = time_buffer.tms_stime; // Tempo de sistema em ticks
    return cpu_time;
}

// Obtém o uso de memória do processo atual (Resident Set Size - RSS) em KB
long getProcessMemoryUsageKb() {
    long rss_kb = 0;
    ifstream stat_stream("/proc/" + to_string(getpid()) + "/status");
    string line;
    while (getline(stat_stream, line)) {
        // Procura pela linha que contém "VmRSS:"
        if (line.rfind("VmRSS:", 0) == 0) {
            stringstream ss(line);
            string label;
            ss >> label >> rss_kb; // Extrai "VmRSS" e o valor em KB
            break;
        }
    }
    return rss_kb; // Memória em KB
}


int main() {
    int tamanho_array;

    cout << "--- Programa de Ordenacao com Shell Sort ou Quick Sort ---" << endl;
    cout << "Digite o tamanho do array a ser gerado: ";
    cin >> tamanho_array;

    if (tamanho_array <= 0) {
        cout << "O tamanho do array deve ser positivo." << endl;
        return 1;
    }

    int* meu_array = gerarArrayAleatorio(tamanho_array);

    //printar array desordenado e ordenado
    cout << "Array desordenado: ";
    if (tamanho_array <= 100) {
        imprimirArray(meu_array, tamanho_array);
    } else {
        cout << "Array muito grande para imprimir completamente. "
             << "Primeiros 10 elementos: ";
        for (int i = 0; i < 10; ++i) {
            cout << meu_array[i] << " ";
        }
        cout << "... Ultimos 10 elementos: ";
        for (int i = tamanho_array - 10; i < tamanho_array; ++i) {
            cout << meu_array[i] << " ";
        }
        cout << endl;
    }

    cout << "Qual algoritmo de ordenação deseja usar?" << endl;
    cout << "1. Quick Sort" << endl;
    cout << "2. Shell Sort" << endl;
    int escolha;
    cin >> escolha;

    if (escolha != 1 && escolha != 2) {
        cout << "Escolha inválida. Encerrando o programa." << endl;
        delete[] meu_array; // Libera a memória alocada
        return 1;
    }

    // --- Medição de Tempo e Memória ---
    long mem_start_kb = getProcessMemoryUsageKb(); // Memória antes da ordenação

    CpuTime cpu_start_times = getProcessCpuTime(); // Tempos de CPU antes da ordenação
    auto start_wall_clock = chrono::high_resolution_clock::now(); // Tempo de relógio de parede

    if (escolha == 1) {
        cout << "\nUsando Quick Sort..." << endl;
        quickSort(meu_array, 0, tamanho_array - 1);
    } else if (escolha == 2) {
        cout << "\nUsando Shell Sort..." << endl;
        shellSort(meu_array, tamanho_array);
    }

    auto end_wall_clock = chrono::high_resolution_clock::now(); // Tempo de relógio de parede
    CpuTime cpu_end_times = getProcessCpuTime();   // Tempos de CPU depois da ordenação
    long mem_end_kb = getProcessMemoryUsageKb();   // Memória depois da ordenação

    // Calcular o tempo de relógio de parede (total de execução)
    chrono::duration<double> elapsed_wall_clock = end_wall_clock - start_wall_clock;

    // Calcular o tempo de CPU usado pela ordenação
    long user_cpu_ticks = cpu_end_times.user_hz - cpu_start_times.user_hz;
    long system_cpu_ticks = cpu_end_times.system_hz - cpu_start_times.system_hz;

    // CLK_TCK é o número de ticks por segundo. É definido em <climits> ou <time.h>
    // Ou pode ser obtido via sysconf(_SC_CLK_TCK)
    long ticks_per_second = sysconf(_SC_CLK_TCK);
    if (ticks_per_second == -1) { // Fallback caso sysconf falhe
        ticks_per_second = 100; // Valor comum, mas pode variar
    }

    double user_cpu_seconds = static_cast<double>(user_cpu_ticks) / ticks_per_second;
    double system_cpu_seconds = static_cast<double>(system_cpu_ticks) / ticks_per_second;
    double total_cpu_seconds = user_cpu_seconds + system_cpu_seconds;

    cout << "\nArray Ordenado: ";
    if (tamanho_array <= 100) {
        imprimirArray(meu_array, tamanho_array);
    } else {
        cout << "Array muito grande para imprimir completamente. "
             << "Primeiros 10 elementos: ";
        for (int i = 0; i < 10; ++i) {
            cout << meu_array[i] << " ";
        }
        cout << "... Ultimos 10 elementos: ";
        for (int i = tamanho_array - 10; i < tamanho_array; ++i) {
            cout << meu_array[i] << " ";
        }
        cout << endl;
    }

    // --- Exibição das Métricas ---
    cout << "\n--- Métricas de Desempenho ---" << endl;
    cout << "Tempo de Execucao (Wall Clock Time): " << fixed << setprecision(6) << elapsed_wall_clock.count() << " segundos" << endl;
    cout << "Tempo de CPU (Usuario): " << fixed << setprecision(6) << user_cpu_seconds << " segundos" << endl;
    cout << "Tempo de CPU (Sistema): " << fixed << setprecision(6) << system_cpu_seconds << " segundos" << endl;
    cout << "Tempo de CPU (Total): " << fixed << setprecision(6) << total_cpu_seconds << " segundos" << endl;
    cout << "Uso de Memoria (RSS) antes da ordenacao: " << mem_start_kb << " KB" << endl;
    cout << "Uso de Memoria (RSS) depois da ordenacao: " << mem_end_kb << " KB" << endl;
    cout << "Variacao de Memoria (RSS): " << (mem_end_kb - mem_start_kb) << " KB" << endl;


    delete[] meu_array; // Libera a memória alocada

    return 0;
}