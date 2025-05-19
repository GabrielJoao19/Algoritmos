#include <iostream>
using namespace std;
int main() {
    int *n,t, i;
    cin >> t;
    n = new int [t];
    if (t == 0){
        cout << "ERRO  ao alocar memoria" << endl;
        exit(1);
    }
    for (i=0; i<t;i++){
        cin >> n[i];
    }
    for (i=0;i<t;i++){
        cout << n[i] << " ";
    }
    cout << endl;

    delete [] n;
    cout << n;
    return 0;
}