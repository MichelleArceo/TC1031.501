/*
Programa para analizar logs de intentos fallidos de ingreso (bitacora3.txt).
    Esteban Sánchez - a01251440
    Michelle Arceo - a01625268
Creación: Sábado, 28 de Noviembre
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <list>
#include <cmath>
#include <unordered_map>

using namespace std;

//Clase para representar una tabla de hash utilizando listas encadenadas
class hashingFunction {
    public:
        Hash (int V){ // Establece el numero de bucket
            BUCKET = V;
            table = new list<int>[BUCKET];
        }

        void insertar(int key){
            insertaElemento(key);
        }

        void duplicados(int arr[], int n){
            removerduplicados(arr, n);
        }

        void tablaEncadena(){
            displayChain();
        }

	private:
        int BUCKET; // Número de buckets

        // Apuntador a la lista que contiene los buckets
        list<int> *table;

        // Función de hash que calcula la posición en la tabla
        int funcionHash(int x){
            return (x % BUCKET);
        }

        // Insertar un elemento en la tabla
        void insertaElemento(int key){
            int pos = funcionHash(key);
            table[pos].push_back(key);
        }

        // Remueve los puertos duplicados
        void removerduplicados(int arr[], int n) {
            unordered_map<int, bool> mp;
            for (int i = 0; i < n; ++i) {
                if (mp.find(arr[i]) == mp.end()) {
                    cout << arr[i] << " ";
                }
            }
        }

        // Funcion para mostrar la tabla de hash por metodo de encadenamiento
        void displayChain() {
        ofstream TableHashing;
        TableHashing.open ("output/hashing.txt");
            for (int i = 0; i < BUCKET; i++) {
                TableHashing << "[ " << i << " ]";
                for (auto x : table[i])
                TableHashing << " --> " << x;
                TableHashing << endl << "\n";
            }
         TableHashing.close();
        }
};

int main() {
    hashingFunction hashing;
    int dato;
    int i = 0;
    int x = 0;
    int N = 1000;
    int arr[N];
    int size = 16807;
    int n = sizeof(arr)/sizeof(arr[0]);
    hashing.Hash(N);

    // Archivo de los registroshashing.duplicados(arr, n);
    ifstream bitacora("input/bitacora3.txt");

    string line;
    ofstream TableHashing;
    TableHashing.open("output/hashing.txt");
    while(getline(bitacora, line)) {
        int n = sizeof(arr)/sizeof(arr[0]);
        stringstream ss(line);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> vstrings(begin, end);
        string ip_port = vstrings[3];
        int pos = ip_port.find(":");
        string port = ip_port.substr(pos+1);
        stringstream newint(port);
        newint >> x;
        hashing.insertar(x);
    }
    // Crea la tabla Hash
    hashing.tablaEncadena();
    TableHashing.close();
    return 0;
}
