#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int  semilla(char nombre[]);
int tamañobmp(char nombre[]);
int* arraytxt(int size,string* txt);
string* rango8bit(char nombre[],int size);
void rango(int size,int*sinrango);

int main()
{
    char nombre[20];
    char nombre1[20];
    int terminacion = 1;
    while(terminacion == 1){
    cout<<"Bienvenido, recuerda ser responsable con la comparacion de los archivos mi rey "<<endl;
    cout<<"Recuerda que mi codigo tiene maticez y le debes de ayudar un poco , se amable :) "<<endl;
    cout<<"ingresa el producto del tamaño de la mascara [ejemplo: 15x10 = 150] me das el 150 "<<endl;
    int mascara = 0;
    cin >> mascara;
    cout<<"Debes de ingresar dos archivos .txt para poder compararlos, primero pon el archivo mas a la izquierda, el otro que le antepone lo pones despues"<<endl;
    cout<<"Ingresa el primer archivo .txt"<<endl;
    cin >> nombre;
    cout<<"ingresa el segundo archivo .txt "<< endl;
    cin >> nombre1;
    //int index = semilla(nombre);
    int size = tamañobmp(nombre);
    size += 1; // el puesto de la semilla
    //primer txt
    string* dato_a_dato = rango8bit(nombre,size);
    //segundo txt
    string* dato_a_dato1 = rango8bit(nombre1,size);
    //convercion de string a enteros del primer txt
    int* uno_a_uno = arraytxt(size,dato_a_dato);
    //conversion del segundo txt
     int* uno_a_uno1 = arraytxt(size,dato_a_dato1);


    for(int i = 0 ; i < size ; i++){
         cout<<uno_a_uno[i]<<endl;
    }


    delete[] uno_a_uno;
     delete[] uno_a_uno1;
    uno_a_uno = nullptr;
     uno_a_uno1 = nullptr;

    cout<<"Seleccione: \n 1-desea seguir leyendo archivo\n 2-ya terminastes?"<<endl;
     cin>>terminacion;
    }


    //ahora si viene lo chido xd hahaha


// Hasta aqui netamente se hice la transformacion de un .txt a una cadena de enteros.
    return 0;
}


int semilla(char nombre[]){
    int numero = 0;
    // ifstream nombre = namearchivotxt(); --> me generaba un error con el string
    ifstream archivo(nombre);
            string linea;



    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            numero = std::stoi(linea);
            cout << "La semilla en este .txt es : "<<numero << endl;
            break; //Se lee unicamente la primera linea que es lo que queria \0
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo";
    }
    return numero;
}

int tamañobmp(char nombre[]){
    int count = 0;
    ifstream archivo(nombre);
    string linea;
    if (archivo.is_open()) {
        getline(archivo,linea);
        while (archivo >> linea) {
            count++;
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo";
    }
    cout<<"El tamaño de este .txt es : "<<count/3<<endl;// esta es dato por dato hahaha se necesita ponerlo en rgb
    return count;
}

string* rango8bit(char nombre[], int size){
    ifstream archivo(nombre);
    string linea;
    if (!archivo.is_open()) {
       cout << "Error al abrir el archivo";
        return nullptr;
        }
     int i = 0;
     size += 1; // la semilla
     string* cambio = new string[size];


    while (archivo >> linea && i < size) {
    cambio[i] = linea;
    i ++;
    }

    archivo.close();
    return cambio;

}

//presentando problemas en la siguiente funcion
int* arraytxt(int size, string* txt){

    int * valores = new int[size];
    for(int i = 0; i < size; i++){
        valores[i]= std::stoi(txt[i]);

    }

    rango(size,valores);
   /* for(int i = 0 ; i < size;i++){
        cout<<valores[i]<<endl;
    }*/
  delete[] txt;
  return valores;
}
// creo que no utilizare esta funcion
void rango(int size,int*sinrango){
    for(int i = 0; i< size; i++){
        if(sinrango[i] >= 255){
            sinrango[i] = sinrango[i] % 256;
        } else if(sinrango[i] < 0){
            sinrango[i] = sinrango[i] + 256;
        }


    }

}



