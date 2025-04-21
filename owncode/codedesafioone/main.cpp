#include <iostream>
#include <fstream>
#include <string>
using namespace std;
string namearchivotxt();
void semilla();
int tamañobmp();
int* arraytxt();
string* rango8bit();
int* rango();

int main()
{



}

string namearchivotxt(){
    string name;
    cout<<"Ingresa el nombre del archivo .txt : "<<endl;
    cin >> name;
    return name;
}

void semilla(){
    string nombre = namearchivotxt();
    // ifstream nombre = namearchivotxt(); --> me generaba un error con el string
    ifstream archivo(nombre.c_str());
            string linea;



    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            cout << "La semilla es : "<<linea << endl;
            break; //Se lee unicamente la primera linea que es lo que queria \0
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo";
    }

}

int tamañobmp(){
    int count = 0;
    string nombre = namearchivotxt();
    ifstream archivo(nombre.c_str());
    string linea;
    if (archivo.is_open()) {
        while (archivo >> linea) {
            count++;
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo";
    }

    cout<<count - 1;
    return count;
}

string* rango8bit(){
    int i = 0;
    int size = tamañobmp();
    string* cambio = new string[size];


    string nombre = namearchivotxt();
    ifstream archivo(nombre.c_str());
    string linea;
    if (archivo.is_open()) {
        while (archivo >> linea) {
            cambio[i] = linea;
            i ++;
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo";
    }
    return cambio;

}

int* arraytxt(){
    int size = tamañobmp();
    int * valores = new int[size];
    string* txt = rango8bit();
    for(int i = 0; i < size; i++){
        valores[i]= std::stoi(txt[i]);

    }
   /* for(int i = 0 ; i < size;i++){
        cout<<valores[i]<<endl;
    }*/
    return valores;
    delete[] txt;
}

int* rango(){
    int size = tamañobmp();
    int* sinrango = arraytxt();
    for(int i = 0; i< size; i++){
        if(sinrango[i] > 255){
            sinrango[i] %= 256;
        }

    }
    return sinrango;

}
