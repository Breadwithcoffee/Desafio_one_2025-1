#include <iostream>
#include <fstream>
#include <string>
using namespace std;
string namearchivotxt();
void semilla(string nombre);
int tamañobmp(string nombre);
int* arraytxt(string nombre,int size,string* txt);
string* rango8bit(string nombre,int size);
int* rango(string nombre,int size,int*sinrango);

int main()
{
    int mascara[2];
    cout<<"Bienvenido, este programa intentara darte las posibles transformaciones que se le han hecho a un grupo de datos :"<<endl;
    string nombre = namearchivotxt();
    semilla(nombre);
    int size = tamañobmp(nombre);
    cout<<"Ingresa el tamaño de la mascara en la tranformacion de esta imagen  "<<endl;
    for(int i = 0; i < 2; i++){cin>>mascara[i];}
    //ahora si viene lo chido xd hahaha
    string* dato_a_dato = rango8bit(nombre,size);
    int* uno_a_uno = arraytxt(nombre,size,dato_a_dato);

    return 0;

}

string namearchivotxt(){
    string name;
    cout<<"Ingresa el nombre del archivo .txt : "<<endl;
    cin >> name;
    return name;
}

void semilla(string nombre){
    // ifstream nombre = namearchivotxt(); --> me generaba un error con el string
    ifstream archivo(nombre.c_str());
            string linea;



    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            cout << "La semilla en este .txt es : "<<linea << endl;
            break; //Se lee unicamente la primera linea que es lo que queria \0
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo";
    }

}

int tamañobmp(string nombre){
    int count = 0;
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
    count -= 1;
    cout<<"El tamaño de este .txt es : "<<count/3<<endl;//esta dato por dato hahaha se necesita ponerlo en rgb
    return count;
}

string* rango8bit(string nombre, int size){
    int i = 0;
    string* cambio = new string[size];

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

int* arraytxt(string nombre, int size, string* txt){

    int * valores = new int[size];
    for(int i = 0; i < size; i++){
        valores[i]= std::stoi(txt[i]);

    }
   /* for(int i = 0 ; i < size;i++){
        cout<<valores[i]<<endl;
    }*/
  delete[] txt;
return valores;
}

int* rango(string nombre,int size,int*sinrango){
    for(int i = 0; i< size; i++){
        if(sinrango[i] > 255){
            sinrango[i] %= 256;
        }

    }
    return sinrango;

}



