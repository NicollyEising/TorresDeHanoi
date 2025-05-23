#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<char, vector<int>> torres;

void imprimirTorres(int num_discos) {
    cout << "\nEstado atual das torres:\n";
    for (int nivel = num_discos - 1; nivel >= 0; --nivel) {
        for (char t : {'A', 'B', 'C'}) {
            if (nivel < torres[t].size()) {
                int d = torres[t][nivel];
                cout << string(num_discos - d, ' ') << string(d, '=') << "|" << string(d, '=') << string(num_discos - d, ' ') << " ";
            } else {
                cout << string(num_discos, ' ') << "|" << string(num_discos, ' ') << " ";
            }
        }
        cout << endl;
    }
    cout << "   A" << string(num_discos * 2 - 1, ' ') << "B" << string(num_discos * 2 - 1, ' ') << "C" << endl;
    cout << "-------------------------------\n";
}

void moverDisco(int disco, char origem, char destino, int num_discos) {
    torres[destino].push_back(torres[origem].back());
    torres[origem].pop_back();
    cout << "Mover disco " << disco << " de " << origem << " para " << destino << endl;
    imprimirTorres(num_discos);
}

void hanoi(int n, char origem, char destino, char auxiliar, int num_discos) {
    if (n == 1) {
        moverDisco(1, origem, destino, num_discos);
        return;
    }
    hanoi(n - 1, origem, auxiliar, destino, num_discos);
    moverDisco(n, origem, destino, num_discos);
    hanoi(n - 1, auxiliar, destino, origem, num_discos);
}

void resolverTorresDeHanoi(int num_discos, char torre_origem, char torre_destino) {
    set<char> torres_set = {'A', 'B', 'C'};

    if (torre_origem == torre_destino || torres_set.count(torre_origem) == 0 || torres_set.count(torre_destino) == 0) {
        cout << "Torres devem ser diferentes e entre 'A', 'B' e 'C'." << endl;
        return;
    }

    char torre_auxiliar;
    for (char t : torres_set) {
        if (t != torre_origem && t != torre_destino) {
            torre_auxiliar = t;
            break;
        }
    }

    torres['A'].clear();
    torres['B'].clear();
    torres['C'].clear();

    for (int i = num_discos; i >= 1; --i) {
        torres[torre_origem].push_back(i);
    }

    cout << "Resolvendo para " << num_discos << " discos, de " << torre_origem << " para " << torre_destino << ":\n";
    imprimirTorres(num_discos);
    hanoi(num_discos, torre_origem, torre_destino, torre_auxiliar, num_discos);
}

int main() {
    int discos;
    char origem, destino;

    cout << "Informe o número de discos: ";
    cin >> discos;

    cout << "Informe a torre de origem (A, B ou C): ";
    cin >> origem;

    cout << "Informe a torre de destino (A, B ou C): ";
    cin >> destino;

    resolverTorresDeHanoi(discos, toupper(origem), toupper(destino));


    cin.ignore();
    cin.get();
    return 0;


}
