#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    
    class filme{
        int id;
        string nome;
    };

    filme filmes[10];

    ifstream arquivo("filme.txt");
    if (!arquivo.is_open()){
        cout << "Arquivo nao lido." << endl;
        return 1;
    }

    int numFilmes = 0;
    for(arquivo >> filmes[numFilmes].id){
        
    }
    
    
    
    
    
    
    
    
    
    
    return 0;
}