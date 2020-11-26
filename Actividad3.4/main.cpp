/*
Programa para analizar logs de intentos fallidos de ingreso (bitacora2.txt).

    Matías Kochlowski – a01625364
    Esteban Sánchez - a01251440
    Michelle Arceo - a01625268

Creación: Jueves, 29 de Octubre
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <map>

// Correr el programa dos veces para desplegar el archivo heapTree.txt final
using namespace std;

// Archivo de ingreso raw
ifstream bitacora("input/bitacora2.txt");
// Archivo de los IpAddress solamente
ifstream RegistroIP("input/ipAddress only.txt");
//Lista de conteos de cada IpAddress
ifstream FrequencyIpAddress("input/Frequency of ipAddress.txt");

// Reemplazar valores de meses textuales por numericos
string mesTextoANro(const string& mes) {
    if (mes == "Jun ") return "06-";
    if (mes == "Jul ") return "07-";
    if (mes == "Aug ") return "08-";
    if (mes == "Sep ") return "09-";
    if (mes == "Oct ") return "10-";
    return "";
}

// Vector para almacenar datos
vector<string> Heap;
int size = -1;

// Agregar datos
void push(string i){
    Heap.push_back(i);
    size = size + 1;
}

// Muestra la extraccion de solamente los ipAddress
void PrintipAddress(){
    ofstream bitacoraipAddress;
    bitacoraipAddress.open ("input/ipAddress only.txt");
    int i = 0;
    while (i <= size){
    bitacoraipAddress << Heap[i] << "\n";
    i++;
    }
    bitacoraipAddress.close();
}

//Realiza el conteo de todas las IpAddress
void PrintCountipAddress(){
    int n = 10;
    map<string, unsigned int> ipAddress;
    map<string, unsigned int>::iterator swop;
    string IpAddress;
    ofstream FrequencyipAddress;
    FrequencyipAddress.open ("input/Frequency of ipAddress.txt");
    static const char filename[] = "input/ipAddress only.txt";
    ifstream input(filename);
    while (input >> IpAddress){
        if (ipAddress.find(IpAddress) != ipAddress.end()){
            ipAddress[IpAddress]++;
        }
        else{
            ipAddress[IpAddress] = 1;
        }
    }
    // Conteo de los ipAddress
    for (swop = ipAddress.begin(); swop != ipAddress.end(); ++swop){
        // Si el conteo es menor que 10
        if (swop->second < n){
            FrequencyipAddress << "0" << swop->second << "\t" << swop->first << "\n";
        }
        else{
            FrequencyipAddress << swop->second << "\t" << swop->first << "\n";
        }
    }
    FrequencyipAddress.close();
}

//Ordenamiento de elementos
void Heapdata(vector<string> &vHeap, int n, int i) {
	int low = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	// Si hijo izquierdo es mas pequeño que la raiz
	if (left < n && vHeap[left] < vHeap[low])
		low = left;
	// Si hijo derecho es mas pequeño que la raiz
	if (right < n && vHeap[right] < vHeap[low])
		low = right;
	// Si el mas pequeño no es razi
	if (low != i) {
		swap(vHeap[i], vHeap[low]);
		Heapdata(vHeap, n, low);
	}
}

// Hace el heap tree
void heapTree(vector<string> &vHeap) {
	// Organiza la matriz
	for (int i =  vHeap.size() - 1; i >= 0; i--)
		Heapdata(vHeap,  vHeap.size() - 1, i);
	// Extrae elementos del heap
	for (int i =  vHeap.size() - 1; i >= 0; i--) {
		swap(vHeap[0], vHeap[i]);
		Heapdata(vHeap, i, 0);
	}
}

int main(int argc, char** argv) {
    string line;
    // Vector de Strings para almacenar lectura de archivo bitacora2.txt
    vector<string> Heap;
    // Ciclo while que lee línea por línea hasta llegar al final del archivo bitacora2.txt
    while (getline(bitacora, line)){
        istringstream iss(line);
        string s = line;
        s = s.replace(0,4,mesTextoANro(line.substr (0,4))).replace(5,1,"T");
        stringstream ss(s);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> vstrings(begin, end);
        string ip = vstrings[1];
        int pos = ip.find(":");
        string IP = ip.substr(0, pos);
        string cleanedLine;
        cleanedLine.append(IP);
        push(cleanedLine);
    };
    // Exportar Lista de IPaddress solamente
    PrintipAddress();
    // Exportar Lista de conteos de cada IPaddress
    PrintCountipAddress();
    //Frecuencia ordenada
    ofstream heapTreeFrequency;
    heapTreeFrequency.open ("output/heapTree.txt");
    // Vector de Strings para almacenar lectura de archivo Frequency of ipAddress.txt
    vector<string> vHeap;
    // Ciclo while que lee línea por línea hasta llegar al final del archivo Frequency of ipAddress.txt
    while (getline(FrequencyIpAddress, line)){
        stringstream ss(line);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> vstrings(begin, end);
        string Frequency = vstrings[0];
        string ipAddress = vstrings[1];
        string cleanedLine;
        cleanedLine.append(Frequency).append("\t").append(ipAddress);
        vHeap.push_back(cleanedLine);
    };
    // Llamado función recursiva de ordenamiento
    heapTree(vHeap);
    heapTreeFrequency << "Freq" << "\t" << "ipAddress\n";
    //Imprimir el heap tree
    for (int i = 0; i <  vHeap.size(); i++){
        if(vHeap[i] < vHeap[4]){
            heapTreeFrequency << vHeap[i] << "\n";
        }
        else{
            heapTreeFrequency << vHeap[i] << "\t" << "ipAdreess con mayores accesos" << "\n";
        }
	}
	heapTreeFrequency.close();
    return 0;
}
