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

using namespace std;

//Vector para almacenar datos
vector<int> Heap;
int size = -1;

//No se le llama si no hay dato
int raiz(int i){
    return (i - 1) / 2;
}

//Regresa el hijo izquierdo
int hijoIzquierdo(int i){
    return (2 * i + 1);
}

//Regresa el hijo derecho
int hijoDerecho(int i){
    return (2 * i + 2);
}

//Ver si un nuevo dato es de mayor prioridad que del que ya esta
void subir(int i){
    if (i > 0 && Heap[raiz(i)] < Heap[i]){
        swap(Heap[i], Heap[raiz(i)]);
        i = raiz(i);
    }
}

//Mantener el orden de prioridades
void bajar(int i){
    int maximo = i;
    int left = hijoIzquierdo(i);
    int right = hijoDerecho(i);
    //Si es mayor prioridad el hijo izquierdo
    if (left < size && Heap[left] > Heap[maximo]){
        maximo = left;
    }
    //Si es mayor prioridad el hijo derecho
    if (right < size && Heap[right] > Heap[maximo]){
        maximo = right;
    }
    //Si la raiz no tiene mayor prioridad
    if (i != maximo){
        swap(Heap[i], Heap[maximo]);
        subir(maximo);
    }
}

//Agregar datos
void push(int x){
    Heap.push_back(x);
    size = size + 1;
    subir(size);
}

//Mayor prioridad de la fila
int top(){
    return Heap[0];
}

//Mostrar la fila priorizada
void mostrar(){
    ofstream bitacoraOrdenada;
    bitacoraOrdenada.open ("output/bitacora_AZ.csv");
    bitacoraOrdenada << "ipAddress,dateTime,errorMessage\n";
    int i = 0;
    while (i <= size){
    cout << Heap[i] << "\n";
    i++;
    }
    bitacoraOrdenada.close();
}

// Archivo de ingreso raw
ifstream bitacora("input/bitacora2.txt");

// Reemplazar valores de meses textuales por numericos
string mesTextoANro(const string& mes) {
    if (mes == "Jun ") return "06-";
    if (mes == "Jul ") return "07-";
    if (mes == "Aug ") return "08-";
    if (mes == "Sep ") return "09-";
    if (mes == "Oct ") return "10-";
    return "";
}

int main() {
    string line;
    // Ciclo while que lee línea por línea hasta llegar al final
    // Vector de Strings para almacenar lectura de archivo
    vector<string> bitacoraVector;
    while (getline(bitacora, line)){
        istringstream iss(line);
        string s = line;
        s = s.replace(0,4,mesTextoANro(line.substr (0,4))).replace(5,1,"T");
        stringstream ss(s);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> vstrings(begin, end);
        string datetime = vstrings[0];
        string ip = vstrings[1];
        string message;
        for(int i = 2; i < vstrings.size(); i++){
            message.append(vstrings[i]).append(" ");
        }
        string cleanedLine;
        cleanedLine.append(ip).append(",").append(datetime).append(",").append(message);
        bitacoraVector.push_back(cleanedLine);
    };
    return 0;
}
