#include <iostream> 
using namespace std;
int main(int argc, char *argv[]) {
    cout << "Número de argumentos: " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << "Argumento " << i << ": " << argv[i] << endl;
    }
    return 0;
}
