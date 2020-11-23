/*
Programa para analizar logs de intentos fallidos de ingreso (bitacora.txt).
    
    Matías Kochlowski – a01625364
    Esteban Sánchez - a01251440
    Michelle Arceo - a01625268

Creación: Sábado, 10 de Octubre
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

// Nodo de una lista doblemente ligada (LDL)
struct Node { 
    std::string data; 
    struct Node* prev, *next; 
}; 

// Función para insertar posterior
void insercionOrdenada(Node **head, Node **tail, std::string key) {  
    Node *p = new Node();  
    p->data = key;  
    p->next = NULL;  
    // 1er Nodo insertado en LDL
    if ((*head) == NULL)  {  
        (*head) = p;  
        (*tail) = p;  
        (*head)->prev = NULL;  
        return;  
    }  
    // Si nuevo nodo tiene valor menor
    if ((p->data) < ((*head)->data))  {  
        p->prev = NULL;  
        (*head)->prev = p;  
        p->next = (*head);  
        (*head) = p;  
        return;  
    }  
    // Si nuevo noto tiene valor mayor
    if ((p->data) > ((*tail)->data))  {  
        p->prev = (*tail);  
        (*tail)->next = p;  
        (*tail) = p;  
        return;  
    }  
    // Encontrar nodo previo a p
    Node *temp = (*head)->next;  
    while ((temp->data) < (p->data))  
        temp = temp->next;  
    // Insertar nuevo nodo antes de p
    (temp->prev)->next = p;  
    p->prev = temp->prev;  
    temp->prev = p;  
    p->next = temp;  
}  

// Función para imprimir la LDL
void ipsOrdenados(Node *head) {  
    std::ofstream bitacoraOrdenada;
    bitacoraOrdenada.open ("output/bitacora_AZ.csv");
    bitacoraOrdenada << "ipAddress,dateTime,errorMessage\n";
    while (head != NULL) {  
        bitacoraOrdenada << head->data << "\n";  
        head = head->next;  
    }  
    bitacoraOrdenada.close();
}  

// Archivo de ingreso raw - mismo archivo que Act. 1.3 - @TODO: ver de usar mismo orígen
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

// Solicitud a usuario de rango de IPs para realizar la búsqueda
void ipsFiltro(Node *head){
    std::string ip1, ip2;
    std::cout << "\nEsta base contiene 16,806 registros de intentos fallidos de ingreso al sistema desde 01-Jun hasta 30-Oct y que detalla IPs y puertos origen de requests.\n";
    std::cout << "\nPara realizar una búsqueda, por favor ingrese el rango de IPs deseado en formato 0.0.0.0:0000\n";
    std::cout << "Ingrese IP y Puerto (0.0.0.0:0000). Desde: ";
    std::cin >> ip1;
    std::cout << "Ingrese IP y Puerto (999.999.999.999:9999). Hasta: ";
    std::cin >> ip2;
    std::cout << "Buscando resultados entre " << ip1 << " y " << ip2 << ".\n\n";
    // Creación de archivo y grabado de resultados en carpeta output
    std::ofstream resultadosBusqueda;
    resultadosBusqueda.open ("output/resultados" + ip1 + "a" + ip2 + ".csv");
    resultadosBusqueda << "ipAddress,dateTime,errorMessage\n";
    while (head != NULL) { 
        if (head->data > ip1 && head->data < ip2) {
            resultadosBusqueda << head->data << "\n"; // Graba en archivo CSV
            std::cout << head->data << "\n"; // Imprime en la consola
        }    
        head = head->next;     
    } 
    resultadosBusqueda.close();
    // Mensaje de Confirmación
    std::cout << "\nLos resultados de su búsqueda han sido almacenados en la carpeta output (formato CSV). \n";
}

int main() {
    Node *head = NULL, *right = NULL;
    std::string line;
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
        cleanedLine.append(ip).append(",").append(datetime).append(",").append(message);
        insercionOrdenada(&head, &right, cleanedLine);
    };

    // Exportar Lista Ordenada por IP
    ipsOrdenados(head);
    // Variables y función para búsqueda
    ipsFiltro(head);

    return 0;
}