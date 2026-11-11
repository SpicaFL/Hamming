#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

string aMayusculas(string s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    return s;
}

bool esValida(const string &s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != 'A' && s[i] != 'C' && s[i] != 'G' && s[i] != 'T') {
            return false;
        }
    }
    return true;
}

int distanciaHamming(const string &a, const string &b) {
    int d = 0;
    for (int i = 0; i < a.length(); i++) {
        if (a[i] != b[i]) {
            d++;
        }
    }
    return d;
}

double porcentajeIdentidad(int d, int L) {
    return ((double)(L - d) / L) * 100.0;
}

void contarNucleotidos(const string &s, int conteo[4]) {
    for (int i = 0; i < 4; i++) {
        conteo[i] = 0;
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'A') {
            conteo[0]++;
        } else if (s[i] == 'C') {
            conteo[1]++;
        } else if (s[i] == 'G') {
            conteo[2]++;
        } else if (s[i] == 'T') {
            conteo[3]++;
        }
    }
}

double contenidoGC(const int conteo[4], int L) {
    return ((double)(conteo[1] + conteo[2]) / L) * 100.0;
}

bool separarPareja(const string &linea, string &seq1, string &seq2) {
    int pos = -1;
    for (int i = 0; i < linea.length(); i++) {
        if (linea[i] == ' ' || linea[i] == ',') {
            if (pos != -1) return false;
            pos = i;
        }
    }
    if (pos <= 0 || pos == linea.length() - 1) return false;
    seq1 = linea.substr(0, pos);
    seq2 = linea.substr(pos + 1);
    return true;
}

int main() {
    string nombreArchivo;
    cout << "Nombre del archivo: ";
    cin >> nombreArchivo;
    cout << endl;

    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir el archivo." << endl;
        return 1;
    }

    cout << fixed << setprecision(1);

    string linea;
    int numPareja = 0;

    while (getline(archivo, linea)) {
        if (!linea.empty() && linea[linea.length() - 1] == '\r') {
            linea.erase(linea.length() - 1);
        }

        if (linea.empty()) {
            continue;
        }

        string seq1, seq2;
        if (!separarPareja(linea, seq1, seq2)) {
            cout << "Aviso: línea ignorada por formato incorrecto: " << linea << endl;
            continue;
        }

        numPareja++;

        seq1 = aMayusculas(seq1);
        seq2 = aMayusculas(seq2);

        if (!esValida(seq1) || !esValida(seq2)) {
            cout << "Pareja " << numPareja << ": " << seq1 << " vs " << seq2
                 << " -> Error: caracteres inválidos" << endl;
        } else if (seq1.length() != seq2.length()) {
            cout << "Pareja " << numPareja << ": " << seq1 << " vs " << seq2
                 << " -> Error: longitudes diferentes" << endl;
        } else {
            int L = seq1.length();
            int d = distanciaHamming(seq1, seq2);
            double id = porcentajeIdentidad(d, L);

            cout << "Pareja " << numPareja << ": " << seq1 << " vs " << seq2
                 << " -> Distancia: " << d << " | Identidad: " << id << "%" << endl;

            int c1[4];
            contarNucleotidos(seq1, c1);
            double gc1 = contenidoGC(c1, L);
            cout << seq1 << " A=" << c1[0] << " C=" << c1[1] << " G=" << c1[2]
                 << " T=" << c1[3] << " GC=" << gc1 << "%" << endl;

            int c2[4];
            contarNucleotidos(seq2, c2);
            double gc2 = contenidoGC(c2, L);
            cout << seq2 << " A=" << c2[0] << " C=" << c2[1] << " G=" << c2[2]
                 << " T=" << c2[3] << " GC=" << gc2 << "%" << endl;
        }
    }

    archivo.close();
    return 0;
// Integrantes:Sajit Chaljub Benitez y Ivanna Isabel Real Cuadrado