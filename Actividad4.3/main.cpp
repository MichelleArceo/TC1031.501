/*
Programa para analizar logs de intentos fallidos de ingreso (bitacora3.txt).

    Esteban Sánchez - a01251440
    Michelle Arceo - a01625268

Creación: Sábado, 21 de Noviembre
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

using namespace std;

void createGraph(vector<string> adj[], int n, string m)
{
    adj[n].push_back(m);
}

void displayGraph(vector<string> adj[], vector<string> IPs, int V)
{
    for (int n = 0; n < V; ++n)
    {
        cout << "{" << IPs[n] << "}";

        for (auto x : adj[n])
        {
            cout << " -> " << x;
        }
        printf("\n");
    }
}

bool buscarDuplicados(vector<string> comparative, string ip)
{
    for(int a = 0; a < comparative.size()-1; a++)
    {
        if (comparative[a] == ip)
        {
            return true;
        }
    }
    return false;
}

int posicionDuplicados(vector<string> comparative, string ip)
{
    int a;
    for(a = 0; a < comparative.size(); a++)
    {
        if (comparative[a] == ip)
        {
            return a;
        }
    }
    return a;
}


// Reemplazar valores de meses textuales por numericos
string mesTextoANro(const string& mes)
{
    if (mes == "Jun ") return "06-";
    if (mes == "Jul ") return "07-";
    if (mes == "Aug ") return "08-";
    if (mes == "Sep ") return "09-";
    if (mes == "Oct ") return "10-";
    return "";
}

int main()
{
    int v = 0; //vertices
    int e = 0; //arcos
    int i = 0;

    vector<string> comparativo; //Almacenaje de IPs para buscar duplicados
    vector<string> Ordenado;


    string line;
    ifstream bitacora("bitacora3.txt");
    while(getline(bitacora, line))
    {
        ++e;
        istringstream iss(line);
        string s = line;
        s = s.replace(0,4,mesTextoANro(line.substr (0,4))).replace(0,1,"T");
        stringstream ss(s);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> vstrings(begin, end);
        string ip_port = vstrings[2];

        size_t pos = ip_port.find(":");
        string ip = ip_port.substr(0, pos);
        comparativo.push_back(ip);
        if (buscarDuplicados(comparativo, ip) == false)
        {
            ++v;
        }
    }

    vector<string> adj[e+1];
    vector<string> IPs;

    // Grafo *G = loadGraph(v);
    // string edge[e][2];


     cout << "edges: " << e << endl;
     cout << "vertex: " << v << endl;

    vector<string> comp2;
    string line2;
    ifstream bitacoraOtra("bitacora3.txt");
    while(getline(bitacoraOtra, line2))
    {
        istringstream iss(line2);
        string s = line2;
        s = s.replace(0,4,mesTextoANro(line2.substr (0,4))).replace(0,1,"T");
        stringstream ss(s);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> vstrings(begin, end);
        string ip_port = vstrings[2];

        size_t pos = ip_port.find(":");
        string ip = ip_port.substr(0, pos);
        string port = ip_port.substr(pos+1);
        comp2.push_back(ip);
        if (buscarDuplicados(comp2, ip) == false)
        {
            IPs.push_back(ip);
        }
        createGraph(adj, posicionDuplicados(comparativo, ip), port);
    }

    cout << "Adyacencia de IPs \n";
    displayGraph(adj, IPs, v);


    return 0;
}
