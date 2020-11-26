/*
Programa para analizar logs de intentos fallidos de ingreso (bitacora3.txt).

    Esteban Sánchez - a01251440
    Michelle Arceo - a01625268

Creación: Sábado, 21 de Noviembre
*/

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <map>

using namespace std;
// Función de Comparador en el queue priorizado.
struct Comparador{
    bool operator()(pair <string ,int> a, pair <string, int> b)
    {
      if(a.second != b.second) return !(a.second < b.second);
         return !(a.first > b.first);
    }
};

//Función que organiza strings en un vector por frecuencia de string
class Sorter {
public:
    //Comparar si la cantidad de strings de un vector en la lista se
    //repite más que el del otro.
    static bool cmp(pair <string, int> a, pair <string, int> b)
    {
      if(a.second != b.second) return a.second > b.second;
         return a.first < b.first;
    }
    //Función de vector para eliminar solo los top k vectores repetidos
    vector<string> topKFrequent(vector<string>& words, int k)
    {
        map<string, int> m;
        priority_queue < pair <string, int>, vector < pair <string, int> >, Comparador > v;
        for(int i = 0; i < words.size(); i++)
        {
            m[words[i]]++;
        }
      map<string, int> :: iterator i = m.begin();
      while(i != m.end())
      {
         if(v.size() < k)
         {
            v.push(*i);
         }
         else if(v.top().second < i->second)
         {
            v.pop();
            v.push(*i);
         }
         else if(v.top().second == i->second && v.top().first > i->first)
         {
            v.pop();
            v.push(*i);
         }
         i++;
      }
      vector <string> res;
      while(!v.empty())
      {
         pair <string, int> temp = v.top();
         v.pop();
         res.push_back(temp.first);
      }
      reverse(res.begin(), res.end());
      return res;
    }
};

//Crea la lista de adyacencia para los puertos
void createGraph(vector<string> adj[], int n, string m)
{
    adj[n].push_back(m);
}


//Función de desplegar los puertos de acceso
void displayPorts(vector<auto> v)
{
    ofstream PuertosPeligrosos;
    PuertosPeligrosos.open("Puertos mas peligrosos.txt");
    for (int i = 0; i < v.size(); i++)
    {
        cout << i << ".- " << v[i] << endl;
    }
    PuertosPeligrosos.close();
}

//Función de desplegar grafo
void displayGraph(vector<string> adj[], vector<string> IPs, vector<string> res, int V)
{
    /*Se navega la lista de los dos vectores, donde n es tanto
    la posición del IP y la posición del arreglo de los puertos
    del mismo IP. Se compara primero la lista de IPs con la lista de IP
    ordenada por la cantidad de intentos de acceso al mismo.*/
    ofstream ListaAdyacencia;
    ListaAdyacencia.open("Lista de adyacencia y Top 10.txt");

    for (int i = 0; i < res.size(); i++)
    {
        for (int n = 0; n < V; ++n)
        {
            if (IPs[n] == res[i])
            {
                cout << "{" << IPs[n] << "}";

                for (auto x : adj[n])
                {
                    cout << " -> " << x;
                }
                printf("\n");
            }
        }
    }

    ListaAdyacencia.close();
}

//Busca versiones duplicadas de los IPs para contar la cantidad de vertices
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

//Busca la posición de cada ip en su respectivo vector para adherirlo
//a la lista de puertos en su posicion correcta
int posicionDuplicados(vector<string> comparative, string ip)
{
    int a;
    for(a = 0; a < comparative.size(); a++)
    {
        //Si el IP ya existe en un punto de la lista, se regresa
        //la posición del IP ya en la lista
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
    //Objeto manipulable de la clase Sorter
    Sorter sorteo;

    int v = 0; //vertices
    int e = 0; //arcos
    int i = 0;

    vector<string> comparativo;
    vector<string> comparativo2;
    vector<string> IPs;
    vector<string> IP2Sort;
    vector<string> port2Sort;

    cout << "------------IPs Vulnerables-----------\n" << endl;
    cout << "Este programa lee una lista de IPs y los puertos que trataron de accesar los IPs\n";
    cout << "y luego los organiza en orden de mas 'atacados' o accesado hasta menos 'atacados'.\n";
    cout << "Finalmente, se despliegan los 10 IPs mas accesados, el IP mas vulnerable, y  los\n";
    cout << "10 puertos que mas intentaron accesar (atacar).\n" << endl;


    cout << "Contando cantidad de arcos (conexiones) y vertices (IPs unicos) en el archivo cargado...";

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
    cout << " Listo!\n" << endl;
    vector<string> adj[e+1];

    cout << "Creando Lista de Adyacencia...";

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
        comparativo2.push_back(ip);
        if (buscarDuplicados(comparativo2, ip) == false)
        {
            IPs.push_back(ip);
        }
        IP2Sort.push_back(ip);
        port2Sort.push_back(port);
        createGraph(adj, posicionDuplicados(comparativo, ip), port);
    }
    cout << "Listo!\n" << endl;

    cout << "Adyacencia de IPs (10 IPs mas vulnerables): \n";
    displayGraph(adj, IPs, sorteo.topKFrequent(IP2Sort, 10), v);
    cout << endl;
    cout << endl;

    cout << "Si pica enter, continua a desplegar los top 10 puertos que\n";
    cout << "intentaron accesar los IPs" << endl;
    system("pause");
    cout << endl;

    cout << "Los top 10 puertos: \n";
    displayPorts(sorteo.topKFrequent(port2Sort, 10));

    cout << endl;
    cout << endl;
    cout << "Programa creado por: Michelle Arceo y Esteban Sanchez\n";

    return 0;
}
