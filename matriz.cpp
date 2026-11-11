#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int distanciaHamming(const string &a, const string &b) {
    int d = 0;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] != b[i]) {
            d++;
        }
    }
    return d;
}

int main() {
    string nombreArchivo = "muestras.txt";
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir el archivo " << nombreArchivo << endl;
        return 1;
    }

    string seq[10];
    int N = 0;
    string linea;

    while (getline(archivo, linea) && N < 10) {
        if (!linea.empty() && linea[linea.length() - 1] == '\r') {
            linea.erase(linea.length() - 1);
        }
        if (!linea.empty()) {
            seq[N] = linea;
            N++;
        }
    }
    archivo.close();

    if (N == 0) {
        cout << "Error: no hay secuencias en el archivo." << endl;
        return 0;
    }

    int D[10][10];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            D[i][j] = distanciaHamming(seq[i], seq[j]);
        }
    }

    // Imprimir matriz con formato
    cout << "\t";
    for (int j = 0; j < N; j++) {
        cout << "S" << (j + 1) << "\t";
    }
    cout << endl;

    for (int i = 0; i < N; i++) {
        cout << "S" << (i + 1) << "\t";
        for (int j = 0; j < N; j++) {
            cout << D[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}