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
        Hash (int V) // Establece el numero de bucket
        {
            BUCKET = V;
            table = new list<int>[BUCKET];
        }

        void insertar(int key)
        {
            insertaElemento(key);
        }

        void tablaEncadena()
        {
            displayChain();
        }

        void count_puertos(vector<int>& puertos)
        {
            count_occurrence(puertos);
        }

        void print(int x)
        {
            desplegar_contado(x);
        }

        unordered_map<int, int> contado;

	private:
        int BUCKET; // Número de buckets

        // Apuntador a la lista que contiene los buckets
        list<int> *table;

        // Función de hash que calcula la posición en la tabla
        int funcionHash(int x)
        {
            return (x % BUCKET);
        }

        // Insertar un elemento en la tabla
        void insertaElemento(int key)
        {
            int pos = funcionHash(key);
            table[pos].push_back(key);
            unordered_map<int, int> m;
        }

        // Funcion para mostrar la tabla de hash por metodo de encadenamiento
        void displayChain()
        {
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

        void count_occurrence(vector<int>& puertos)
        {
            for (auto x = puertos.begin(); x != puertos.end(); ++x)
            {
                ++contado[*x];
            }
        }

        void desplegar_contado(int x)
        {
            cout << x << " fue accesado: " << contado[x] << endl;

            ifstream bitacora2("input/bitacora3.txt");
            string line2;
            while(getline(bitacora2, line2)) {
                stringstream ss(line2);
                istream_iterator<string> begin(ss);
                istream_iterator<string> end;
                vector<string> vstrings(begin, end);
                string ip_port = vstrings[3];
                int pos = ip_port.find(":");
                string ip = ip_port.substr(0, pos);
                string port = ip_port.substr(pos+1);
                stringstream newint(port);
                int k = 0;
                newint >> k;
                if (x == k)
                {
                    cout << ip << endl;
                }
            }
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
    vector<int> puertos;
    int y;


    cout << "-------------------------Actividad 5.2---------------------------\n";
    cout << "----------------------------Puertos------------------------------\n";
    cout << "   Este programa realiza una tabla de hash en el cual se ordenan los\n";
    cout << "puertos en la tabla de hash. Luego se le pide que el usuario ingrese\n";
    cout << "uno de los puertos y el programa regresará la cantidad de veces que se\n";
    cout << "repite el puerto en la lista y los IPs que acceso.\n" << endl;

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
        puertos.push_back(x);
    }
    hashing.count_puertos(puertos);
    cout << "Buscar puerto: ";
    cin >> y;
    cout << endl;
    hashing.print(y);
    // Crea la tabla Hash
    hashing.tablaEncadena();
    TableHashing.close();
    return 0;
}
