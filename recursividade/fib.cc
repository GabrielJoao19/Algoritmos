#include <iostream>
#include <fstream>   // Para manipulação de arquivos
#include <algorithm> // Para min e max
#include <random>    // Para random_device, mt19937, uniform_int_distribution
#include <chrono>    // Para high_resolution_clock

using namespace std;
using namespace std::chrono;

// --- Min/Max Algorithms ---

// Function to find Min/Max iteratively in a C-style array
// Returns a dynamically allocated array of 2 ints: result[0] = min, result[1] = max
int* findMinMaxIterative(int arr[], int n) {
    if (n <= 0) {
        int* result = new int[2];
        result[0] = 0;
        result[1] = 0;
        return result;
    }
    int minVal = arr[0];
    int maxVal = arr[0];
    for (int i = 1; i < n; ++i) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    int* result = new int[2];
    result[0] = minVal;
    result[1] = maxVal;
    return result;
}

// Helper function for recursive Min/Max to manage min/max values across calls
void findMinMaxRecursiveHelper(int arr[], int start, int end, int* currentMin, int* currentMax) {
    if (start == end) { // Only one element
        *currentMin = arr[start];
        *currentMax = arr[start];
        return;
    }
    if (end == start + 1) { // Two elements
        *currentMin = min(arr[start], arr[end]);
        *currentMax = max(arr[start], arr[end]);
        return;
    }

    int mid = start + (end - start) / 2;
    int leftMin, leftMax;
    int rightMin, rightMax;

    findMinMaxRecursiveHelper(arr, start, mid, &leftMin, &leftMax);
    findMinMaxRecursiveHelper(arr, mid + 1, end, &rightMin, &rightMax);

    *currentMin = min(leftMin, rightMin);
    *currentMax = max(leftMax, rightMax);
}

// Function to find Min/Max recursively in a C-style array
// Returns a dynamically allocated array of 2 ints: result[0] = min, result[1] = max
int* findMinMaxRecursive(int arr[], int n) {
    if (n <= 0) {
        int* result = new int[2];
        result[0] = 0;
        result[1] = 0;
        return result;
    }
    int* result = new int[2];
    findMinMaxRecursiveHelper(arr, 0, n - 1, &result[0], &result[1]);
    return result;
}

// --- Fibonacci Algorithms ---

// Iterative Fibonacci with sequence display
// Modified to also return the last Fibonacci number for logging
long long printAndGetFibonacciIterative(int n, ostream& os) {
    if (n <= 0) {
        os << "0";
        if (n == 0) os << endl; // Only print newline if it's just 0
        return 0;
    }
    long long a = 0, b = 1;
    os << a;
    if (n >= 1) { // Changed from n > 0 to n >= 1 to handle n=1 correctly (prints "0 1")
        os << " " << b;
    }

    for (int i = 2; i <= n; ++i) {
        long long nextTerm = a + b;
        os << " " << nextTerm;
        a = b;
        b = nextTerm;
    }
    os << endl;
    return b; // Return the last calculated Fibonacci number
}

// Recursive Fibonacci - helper to get single number
long long getFibonacciRecursive(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    return getFibonacciRecursive(n - 1) + getFibonacciRecursive(n - 2);
}

// Recursive Fibonacci with sequence display
// Modified to also return the last Fibonacci number for logging
void printFibonacciRecursiveSequence(int n, ostream& os) {
    if (n < 0) {
        return;
    }
    for (int i = 0; i <= n; ++i) {
        os << getFibonacciRecursive(i) << (i == n ? "" : " ");
    }
    os << endl;
}

// --- Factorial Algorithms ---

// Iterative Factorial
long long factorialIterative(int n) {
    if (n < 0) return 0;
    long long res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}

// Recursive Factorial
long long factorialRecursive(int n) {
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;
    return n * factorialRecursive(n - 1);
}

// --- Main Program ---

int main() {
    int algorithmChoice;
    int versionChoice;
    int n;

    // Abrir o arquivo para escrita. O ios::app faz com que o novo conteúdo seja anexado, não sobrescrevendo.
    // Se o arquivo não existir, ele será criado.
    ofstream outFile("resultados_algoritmos.txt", ios::app);
    if (!outFile.is_open()) {
        cerr << "Erro ao abrir o arquivo para escrita!\n";
        return 1; // Retorna com erro se não conseguir abrir o arquivo
    }

    // Também imprime no console
    cout << "Selecione o algoritmo a ser executado:\n";
    cout << "1. Min/Max\n";
    cout << "2. Fibonacci\n";
    cout << "3. Fatorial\n";
    cout << "Escolha: ";
    cin >> algorithmChoice;

    cout << "Selecione a versão:\n";
    cout << "1. Iterativa\n";
    cout << "2. Recursiva\n";
    cout << "Escolha: ";
    cin >> versionChoice;

    // Log the choices to the file
    outFile << "----------------------------------------\n";
    outFile << "Escolha do Algoritmo: ";
    if (algorithmChoice == 1) outFile << "Min/Max\n";
    else if (algorithmChoice == 2) outFile << "Fibonacci\n";
    else if (algorithmChoice == 3) outFile << "Fatorial\n";
    else outFile << "Inválida\n";

    outFile << "Versão Escolhida: ";
    if (versionChoice == 1) outFile << "Iterativa\n";
    else if (versionChoice == 2) outFile << "Recursiva\n";
    else outFile << "Inválida\n";

    switch (algorithmChoice) {
        case 1: { // Min/Max
            cout << "Digite o tamanho do array (n): ";
            cin >> n;
            outFile << "Tamanho do Array (n): " << n << endl;

            if (n <= 0) {
                cout << "O tamanho do array deve ser positivo.\n";
                outFile << "Erro: Tamanho do array inválido.\n";
                outFile.close();
                return 1;
            }

            int* arr = new int[n];
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distr(1, 1000);

            for (int i = 0; i < n; ++i) {
                arr[i] = distr(gen);
            }

            cout << "Array gerado: [";
            outFile << "Array gerado: [";
            for (int i = 0; i < n; ++i) {
                cout << arr[i] << (i == n - 1 ? "" : ", ");
                outFile << arr[i] << (i == n - 1 ? "" : ", ");
            }
            cout << "]\n";
            outFile << "]\n";

            int* result = nullptr;
            if (versionChoice == 1) {
                auto start = high_resolution_clock::now();
                result = findMinMaxIterative(arr, n);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "Min/Max (Iterativo): Min = " << result[0] << ", Max = " << result[1] << endl;
                cout << "Tempo de execução: " << duration.count() << " microssegundos\n";

                outFile << "Min/Max (Iterativo): Min = " << result[0] << ", Max = " << result[1] << endl;
                outFile << "Tempo de execução: " << duration.count() << " microssegundos\n";
            } else if (versionChoice == 2) {
                auto start = high_resolution_clock::now();
                result = findMinMaxRecursive(arr, n);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "Min/Max (Recursivo): Min = " << result[0] << ", Max = " << result[1] << endl;
                cout << "Tempo de execução: " << duration.count() << " microssegundos\n";

                outFile << "Min/Max (Recursivo): Min = " << result[0] << ", Max = " << result[1] << endl;
                outFile << "Tempo de execução: " << duration.count() << " microssegundos\n";
            } else {
                cout << "Escolha de versão inválida.\n";
                outFile << "Escolha de versão inválida.\n";
            }

            delete[] arr;
            if (result != nullptr) {
                delete[] result;
            }
            break;
        }
        case 2: { // Fibonacci
            long long fib_last_term = 0; // To store the last Fibonacci number for logging
            cout << "Digite um número (n) para Fibonacci: ";
            cin >> n;
            outFile << "Número (n) para Fibonacci: " << n << endl;

            if (n < 0) {
                cout << "O número deve ser não-negativo.\n";
                outFile << "Erro: Número inválido.\n";
                outFile.close();
                return 1;
            }
            if (versionChoice == 1) {
                cout << "Fibonacci (Iterativo) até " << n << ": ";
                outFile << "Fibonacci (Iterativo) até " << n << ": ";
                auto start = high_resolution_clock::now();
                fib_last_term = printAndGetFibonacciIterative(n, cout); // Print to console
                // For file logging, we re-run. In optimized code, capture output once.
                printAndGetFibonacciIterative(n, outFile); 
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                
                cout << "Tempo de execução: " << duration.count() << " microssegundos\n";
                outFile << "Tempo de execução: " << duration.count() << " microssegundos\n";
                outFile << "Último termo calculado: " << fib_last_term << endl; // Log the last term
            } else if (versionChoice == 2) {
                cout << "Fibonacci (Recursivo) até " << n << ": ";
                outFile << "Fibonacci (Recursivo) até " << n << ": ";
                auto start = high_resolution_clock::now();
                printFibonacciRecursiveSequence(n, cout); // Print to console
                // For file logging, we re-run. In optimized code, capture output once.
                printFibonacciRecursiveSequence(n, outFile); 
                // To get the last term for logging, call getFibonacciRecursive(n) explicitly
                fib_last_term = getFibonacciRecursive(n); 
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "Tempo de execução: " << duration.count() << " microssegundos\n";
                outFile << "Tempo de execução: " << duration.count() << " microssegundos\n";
                outFile << "Último termo calculado: " << fib_last_term << endl; // Log the last term
            } else {
                cout << "Escolha de versão inválida.\n";
                outFile << "Escolha de versão inválida.\n";
            }
            break;
        }
        case 3: { // Fatorial
            long long fact_result = 0; // To store the factorial result for logging
            cout << "Digite um número (n) para Fatorial: ";
            cin >> n;
            outFile << "Número (n) para Fatorial: " << n << endl;

            if (n < 0) {
                cout << "O número deve ser não-negativo.\n";
                outFile << "Erro: Número inválido.\n";
                outFile.close();
                return 1;
            }
            if (versionChoice == 1) {
                auto start = high_resolution_clock::now();
                fact_result = factorialIterative(n);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "Fatorial (Iterativo) de " << n << " é: " << fact_result << endl;
                cout << "Tempo de execução: " << duration.count() << " microssegundos\n";

                outFile << "Fatorial (Iterativo) de " << n << " é: " << fact_result << endl;
                outFile << "Tempo de execução: " << duration.count() << " microssegundos\n";
            } else if (versionChoice == 2) {
                auto start = high_resolution_clock::now();
                fact_result = factorialRecursive(n);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);

                cout << "Fatorial (Recursivo) de " << n << " é: " << fact_result << endl;
                cout << "Tempo de execução: " << duration.count() << " microssegundos\n";

                outFile << "Fatorial (Recursivo) de " << n << " é: " << fact_result << endl;
                outFile << "Tempo de execução: " << duration.count() << " microssegundos\n";
            } else {
                cout << "Escolha de versão inválida.\n";
                outFile << "Escolha de versão inválida.\n";
            }
            break;
        }
        default: {
            cout << "Escolha de algoritmo inválida.\n";
            outFile << "Escolha de algoritmo inválida.\n";
            break;
        }
    }

    outFile << "----------------------------------------\n\n"; // Separador para próximas execuções
    outFile.close(); // Fechar o arquivo ao finalizar

    return 0;
}