#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int  semilla(char nombre[]){
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
int tamañobmp(char nombre[]);
int* arraytxt(int size,string* txt);
string* rango8bit(char nombre[],int size){
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
void rango(int size,int*sinrango);
void rotaciones(int* a, int*b);
void XOR(int* a, int* b, int* c, int size);
void enmascaramiento(int* a, int * b ,int * c , int index,int size1, int size);
int main()
{
    char nombre[20];
    char nombre1[20];
    char nombre2[20];
    char nombre3[20];
    int terminacion = 1;
    while(terminacion == 1){
    cout<<"Bienvenido, recuerda ser responsable con la comparacion de los archivos mi rey "<<endl;
    cout<<"Recuerda que mi codigo tiene maticez y le debes de ayudar un poco , se amable :) "<<endl;
    /*cout<<"ingresa el producto del tamaño de la mascara [ejemplo: 15x10 = 150] me das el 150 "<<endl;
    int mascara = 0;
    cin >> mascara;*/
    cout<<"Debes de ingresar dos archivos .txt para poder compararlos, primero pon el archivo mas a la izquierda, el otro que le antepone lo pones despues"<<endl;
    cout<<"Ingresa el primer archivo .txt"<<endl;
    cin >> nombre;
    cout<<"ingresa el segundo archivo .txt "<< endl;
    cin >> nombre1;
    int index = semilla(nombre);
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
     // ponerle el rango a cada array
     rango( size,uno_a_uno);
     //ahora al siguiente
      rango( size,uno_a_uno1);


    /*for(int i = 0 ; i < size ; i++){
         cout<<uno_a_uno[i]<<endl;
    }*/
    // vamos con las tranformaciones

    rotaciones(uno_a_uno,uno_a_uno1);

    cout<<"Sigue siendo amable con el codigo y proporcionale el archivo .txt en donde se encuentra la imagen aleatoria :) "<<endl;
    cin >> nombre2;

    // vamos con xor
    string* dato_a_dato2 = rango8bit(nombre2,size);

    int* uno_a_uno2 = arraytxt(size,dato_a_dato2);

    // toca crear una copia porque pierdo datos
    int* copia_uno_a_uno = new int[size];
    for(int i = 0; i < size; i++) {
        copia_uno_a_uno[i] = uno_a_uno[i];
    }
     XOR(uno_a_uno, uno_a_uno1, uno_a_uno2, size);

    // vamos con la mascara
     cout<<"Esto es lo ultimo que te pido, dame el archivo en donde estan los datos de la mascara :) "<<endl;
     cin >>nombre3;
     int size1 = tamañobmp(nombre3);
     string* dato_a_dato3 = rango8bit(nombre3,size1);
     int * uno_a_uno3 = arraytxt(size1,dato_a_dato3);
     index *=3;
     index += 1;
     enmascaramiento( copia_uno_a_uno, uno_a_uno1 , uno_a_uno3 , index,size1,size);



    delete[] uno_a_uno;
     delete[] uno_a_uno1;
    delete[] uno_a_uno2;
     delete[] uno_a_uno3;
    delete[] copia_uno_a_uno;
     copia_uno_a_uno = nullptr;
     uno_a_uno = nullptr;
     uno_a_uno1 = nullptr;
    uno_a_uno2 = nullptr;
     uno_a_uno3 = nullptr;

    cout<<"Seleccione: \n 1-desea seguir leyendo archivo\n 2-ya terminastes?"<<endl;
     cin>>terminacion;
    }




// Hasta aqui netamente se hice la transformacion de un .txt a una cadena de enteros.
    return 0;
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

void rotaciones(int* a, int* b) {
    for (int i = 1; i < 8; i++) {
        int izquierda = ((a[5] << i) | (a[5] >> (8 - i))) & 0xFF  ;
        if (izquierda == b[5]) {
            cout << "¡Se encontraron rotaciones !! :) hacia la izquierda de << " << i << " bits ";
            if(i == 8){cout<<" o posiblemente de << 0 "<<endl;}
            else if(i == 0){cout<<"o posiblemente de << 8 "<<endl;}
            else if( i == 1 || i == 7){
                cout<<" o posiblemente de << 7 bits"<<endl;
            }
            else if(i == 2 || i == 6){cout<<" o posiblemente de << 6 bits"<<endl;}
            else if(i == 3 || i == 5){cout<<" o posiblemente de << 5 bits"<<endl;}
            cout<<endl;
            return;
        }
    }
    for (int i = 1; i < 8; i++) {
        int derecha = ((a[5] >> i) | (a[5] << (8 - i))) & 0xFF  ;
        if (derecha == b[5]) {
            cout << "¡Se encontraron rotaciones !! :) hacia la derecha de >>" << i << " bits";

            if(i == 8){cout<<" o posiblemente de >> 0 "<<endl;}
            else if(i == 0){cout<<"o posiblemente de >> 8 "<<endl;}

            else if( i == 1 || i == 7){
                cout<<" o posiblemente de >> 7 bits"<<endl;
            }
            else if(i == 2 || i == 6){cout<<" o posiblemente de >> 6 bits"<<endl;}
            else if(i == 3 || i == 5){cout<<" o posiblemente de >> 5 bits"<<endl;}
            cout<<endl;
            return;
        }
    }

    cout << "No hay rotaciones rey :(  pasamos a las tranformaciones XOR" << endl;
}

void XOR(int* a, int* b, int* c,int size){
    bool comprobante = false;
    for(int i = 0;i < size ; i++){
        a[i] = a[i] ^ c[i];
    }

    for(int i = 0 ; i < size;i++){
        if(a[i] == b[i]){comprobante = true;}
    }

    if(comprobante == true){cout<<"¡tranformacion encontrada es un XOR !!"<<endl;}
    else{cout<<"No hay XOR rey :(  pasamos a las mascaras"<<endl;}
}
void enmascaramiento(int* a, int* b, int* c, int index, int size1, int size) {
    // Aplicar enmascaramiento
    for(int i = 0; i < size1; i++) {
        int resta = a[index + i] - c[i + 1];
        if(resta < 0) resta += 256;
        a[index + i] = resta;

    }

    // Comparar arrays
    bool desicion = true;
    for(int i = 1; i < size; i++) {
        if(a[i] == b[i]){desicion = true;}
        else{desicion = false;}
    }

    // Resultado
    if(desicion == true) {
        cout << "¡Transformación encontrada! Se creó un enmascaramiento.\n";
        cout << "La semilla de donde se creó está en: " << (index - 1) / 3 << endl;
    } else {
        cout << "Tiene que haber un error en el formato o la disposición de los archivos." << endl;
    }
}












