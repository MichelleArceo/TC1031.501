/*
Programa para analizar logs de intentos fallidos de ingreso (bitacora.txt).
    
    Matías Kochlowski – a01625364
    Esteban Sánchez - a01251440
    Michelle Arceo - a01625268

Creación: Sábado, 12 de Septiembre 
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

// Archivo de ingreso raw
std::ifstream bitacora("input/bitacora.txt");

// Reemplazar valores de meses textuales por numericos
std::string mesTextoANro(const std::string& mes) {
    if (mes == "Jun ") return "06-";
    if (mes == "Jul ") return "07-";
    if (mes == "Aug ") return "08-";
    if (mes == "Sep ") return "09-";
    if (mes == "Oct ") return "10-";
    return "";
}

// Quicksort recursivo
void quickSort(std::vector<std::string> &str, int inicio, int fin) {
    int i = inicio, j = fin;
    // Variable para asistir en cambio de valores - SWAP
    std::string buffer;
    // Valor medio en lista
    std::string mid = str[(inicio + fin) / 2];
    while (i <= j) {
        // Contador desde inicio hacia el centro
        while (str[i] < mid)
            i++;
        // Contador desde el final hacia el centro
        while (str[j] > mid)
            j--;
        // Comparador y cambiador de valores - SWAP
        if (i <= j) {
                buffer = str[i];
                str[i] = str[j];
                str[j] = buffer;
                i++; j--;
        }
    };
    // Recursión - función se llama a si misma
    if (inicio < j) quickSort(str, inicio, j);
    if (i < fin) quickSort(str, i, fin);
}

// Solicitud a usuario de rango de fechas para realizar la búsqueda
void fechasFiltro(std::vector<std::string> listaVector)
{
    std::string fecha1, fecha2;
    std::cout << "\nEsta base contiene 16,806 registros de intentos fallidos de ingreso al sistema desde 01-Jun hasta 30-Oct.\n";
    std::cout << "\nPara realizar una búsqueda, por favor ingrese el rango de fechas deseado en formato MM-DD. Por ejemplo, el 10 de Junio se debe escribir como 06-10.\n";
    std::cout << "Ingrese Fecha (06-01). Desde: ";
    std::cin >> fecha1;
    std::cout << "Ingrese Fecha (10-30). Hasta: ";
    std::cin >> fecha2;
    std::cout << "Buscando resultados entre " << fecha1 << " y " << fecha2 << ".\n\n";
    // Creación de archivo y grabado de resultados en carpeta output
    std::ofstream resultadosBusqueda;
    resultadosBusqueda.open ("output/resultados" + fecha1 + "a" + fecha2 + ".csv");
    resultadosBusqueda << "dateTime,ipAddress,errorMessage\n";
    for(int a = 0; a < listaVector.size(); a++){
        if (listaVector[a] > fecha1 && listaVector[a] < fecha2 + "z") {
            resultadosBusqueda << listaVector[a] << "\n"; // Graba en archivo CSV
            std::cout << listaVector[a] << "\n"; // Imprime en la consola
        }
    };
    // Mensaje de Confirmación
    std::cout << "\nLos resultados de su búsqueda han sido almacenados en la carpeta output (formato CSV). \n";
}

int main() {
    std::string line;
    std::ofstream bitacoraOrdenada;
    // Archivo a grabar con datos ordenados
    bitacoraOrdenada.open ("output/bitacora_AZ.csv");
    // Vector de Strings para almacenar lectura de archivo
    std::vector<std::string> bitacoraVector;
    // Ciclo while que lee línea por línea hasta llegar al final
    while (std::getline(bitacora, line)){
        std::istringstream iss(line);
        std::string s = line;
        s = s.replace(0,4,mesTextoANro(line.substr (0,4))).replace(5,1,"T");
        std::stringstream ss(s);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);
        std::string datetime = vstrings[0];
        std::string ip = vstrings[1];
        std::string message;
        for(int i = 2; i < vstrings.size(); i++){
            message.append(vstrings[i]).append(" ");
        }
        std::string cleanedLine;
        cleanedLine.append(datetime).append(",").append(ip).append(",").append(message);
        bitacoraVector.push_back(cleanedLine);
    };
    // Llamado función recursiva de ordenamiento
    quickSort(bitacoraVector, 0, bitacoraVector.size()-1);
    // Grabado de bitacora ordenada por fecha y hora a archivo CSV
    bitacoraOrdenada << "dateTime,ipAddress,errorMessage\n";
    for(int b = 0; b < bitacoraVector.size(); b++){
        bitacoraOrdenada << bitacoraVector[b] << "\n";
    };
    bitacoraOrdenada.close();

    // Variables y función para búsqueda
    fechasFiltro(bitacoraVector);

    return 0;
}