
#include <fstream> // investigue un poco esta libreria sirve para manipular archivos .txt

#include <iostream> // libreria estandar xd

#include <QCoreApplication> // Es como la consola de qt algo asi, debo profundizar en esto


#include <QImage>// es como la libreria que manipula los archivos.txt pero en este caso manipula los archivos .BMP

using namespace std;

unsigned char* loadPixels(QString input, int &width, int &height); // es una funcion que retorna un puntero tipo char sin signo

//que interesante que qstring es una clase que puede con utf-16 y tiene muchas funciones

// que interesante que int &w y &h no son direcciones de memoria, sino que son alias es decir apodos que se refieren a una variable
// que interesante que puedo manipular las variables originales sin necesidad de que se cree las copias que se crean.





unsigned int* loadSeedMasking(const char* nombreArchivo, int &seed, int &n_pixels);

void creartxt(char nombretxt[], unsigned char* pixelData,int seed, int width,int height);

 int* leertxt(char nombretxt[],int width, int height  );



int main()
{
    //modificacion
    int height = 0;
    int width = 0;
    int seed = 0;
    char nombretxt[20];
    char nombre[20] ;
    char desicion = 48;
    while(desicion != 101){

        cout<<"Se que este programa  unicamente era para lectura de datos , pero tambien tendre que utilizarla "<<endl;
        cout<<"Para creacion de datos :) "<<endl;
        cout<<"Ingresa lo que quieres hacer a los datos :) RECUERDA QUE TODO SE HARA DE MANERA LINEAL"<<endl;
        cout<<"a-leer una imagen \n b- rotar una imagen \n c- aplicar xor \n d-poner mascara \n e-salir "<<endl;
        cin>> desicion;
        if(desicion == 97 ){
            cout<<"Ingresa el nombre de la imagen"<<endl;
            cin>>nombre;
            QString archivoEntrada = nombre;

            unsigned char *pixelData = loadPixels(archivoEntrada, width, height);

        //    int n_pixels = 0;
            cout<<"Ingrese el nombre del .txt en donde se van a poner los datos leidos"<<endl;

            cin>>nombretxt;
            creartxt(nombretxt, pixelData, seed, width, height);
            cout<<width << height<<endl;
            cout<<"dato leido satisfactoriamente :)"<<endl;


            cout<<"procedo a cambiar los datos para el rango de 8 bit desaado :) "<<endl;
            int size = height * width * 3;
            int * enteros1 =  leertxt( nombretxt, width,  height );
            for(int i = 0 ; i < size; i ++){
                if(enteros1[i] > 255){
                    enteros1[i] = enteros1[i]%256;
                }
                else if(enteros1[i] < 0){
                    enteros1[i] = enteros1[i] + 256;
                }
            }

            ofstream archivo(nombretxt);
            if (!archivo.is_open()) {
                cout << "error al abrir el archivo" << endl;
            }

            //Para la semilla
            archivo << seed << endl;
                //Me copia los rgb :>
            size = width * height * 3 ;
            for (int i = 0; i < size; i += 3) {
                archivo << enteros1[i]  << " " << enteros1[i + 1] << " " << enteros1[i + 2] << endl;
            }

            archivo.close();
            cout << "Archivo " << nombretxt << " todo melo todo bacano" << endl;


            // necesito evitar fugas -->
            delete[] pixelData;
            delete[] enteros1;
            enteros1 = nullptr;
            pixelData = nullptr;
            }


        else if(desicion == 98){
            cout<<"Ingresa el nombre del .txt a rotar "<<endl;
            cin >> nombretxt;
              int * enteros =  leertxt( nombretxt, width,  height );
              // ya tenemos el array en enteros ahora sigue algo muy interesante, algo
              //que me gusta mucho;
              int size = width * height * 3;
              //convertire los datos del array en numero menores de 8 bits

              //esto lo trabajo con el array entero mas no me lo cambia en el .txt.
              for(int i = 0 ; i < size; i ++){
                  if(enteros[i] > 255){
                      enteros[i] = enteros[i]%256;
                  }
              }
              cout<<"Ingresa para donde quieres rotar \n 1-<< \n 2->> "<<endl;
              int rotacion = 0;
              int cantidad;
              cin>>rotacion;
              if(rotacion == 1){cout<<"cuantas veces quieres rotar? TOPE MAXIMO 8 POR TURNO "<<endl;
              cin>>cantidad;}
              else{cout<<"cuantas veces quieres rotar? TOPE MAXIMO 8 POR TURNO "<<endl;
                  cin>>cantidad;}

              // ROTACION PARA TODOS LOS VALORES
              if(rotacion == 1){
                  for(int i = 0; i < width * height*3; i++){

                      enteros[i] = (enteros[i]<< cantidad) | enteros[i]>> (8-cantidad);

                  }
              }
              else if(rotacion == 2){
                  for(int i = 0; (i < width * height*3)  ; i++){

                      enteros[i] = (enteros[i]>> cantidad) | (enteros[i]<< (8-cantidad) & 0xFF);

                  }
              }
              for(int i = 0 ; i < size; i ++){
                  if(enteros[i] >= 255){
                      enteros[i] = enteros[i]%256;
                  }else if(enteros[i] < 0){
                      enteros[i] = enteros[i] + 256;
                  }
              }


              cout<<"Ingresa el txt que recibira la informacion de esta transformacion "<<endl;
              cin >> nombretxt;
               //ahora tengo que tener otro txt para guardar esta combinacion.
                  ofstream archivo(nombretxt);
                  if (!archivo.is_open()) {
                      cout << "error al abrir el archivo" << endl;
                  }

                  //Para la semilla
                 archivo << seed << endl;
                  //Me copia los rgb :>
                   size = width * height * 3 ;
                  for (int i = 0; i < size; i += 3) {
                      archivo << enteros[i]  << " " << enteros[i + 1] << " " << enteros[i + 2] << endl;
                  }

                  archivo.close();
                  cout << "Archivo " << nombretxt << " todo melo" << endl;
                  delete[] enteros;
                  enteros = nullptr;

            }


            else if(desicion == 99){
                int size = height * width * 3;
                //Las pautas para  esto es lo siguiente
                /* Se necesita que se hallan sacado los valores de la imagen aleatoria y de la imagen a
                 transformar y los txt correspondientes y listo a darle*/
                cout<<"Ingrese el .txt en donde se encuentra los datos de la imagen aleatoria :"<<endl;
                char nombretxt[20];
                cin>>nombretxt;
                cout<<"Ahora ingrese el .txt de la imagen a la que se le realizara el procedimiento xor "<<endl;
                char nombretxt1[20];
                cin>>nombretxt1;

                int* datos1 = leertxt( nombretxt,  width,  height);
                //rango que necesito
                for(int i = 0; i < size; i++ ){
                    if(datos1[i] > 255){
                        datos1[i] = datos1[i] % 256;
                    }
                    else if(datos1[i] < 0){
                        datos1[i] = datos1[i] + 256;
                    }
                }

                int* datos2 = leertxt( nombretxt1,  width,  height);
                //rango que necesito
                for(int i = 0; i < size; i++ ){
                    if(datos2[i] > 255){
                        datos2[i] = datos2[i] % 256;
                    }else if(datos2[i] < 0){
                        datos2[i] = datos2[i] + 256;
                    }
                }

                //ahora si viene lo rico
                int * datosresultantes = new int[size];
                for(int i = 0 ; i < size; i++){
                    datosresultantes[i] = datos1[i] ^ datos2[i];

                }

                // volver con el rango
                for(int i = 0; i < size; i++ ){
                    if(datosresultantes[i] > 255){
                        datosresultantes[i] = datosresultantes[i] % 256;
                    }else if(datosresultantes[i] < 0){
                        datosresultantes[i] = datosresultantes[i] + 256;
                    }
                }

                // copio todo esto en otro .txt

                cout<<"Ingresa el nombre del .txt  en donde guardaras esta transformacion "<<endl;
                cin>>nombretxt;
                ofstream archivo(nombretxt);
                if (!archivo.is_open()) {
                    cout << "error al abrir el archivo" << endl;
                }

                //Para la semilla
                archivo << seed << endl;
                    //Me copia los rgb :>
                size = width * height * 3 ;
                for (int i = 0; i < size; i += 3) {
                    archivo << datosresultantes[i]  << " " << datosresultantes[i + 1] << " " << datosresultantes[i + 2] << endl;
                }

                archivo.close();
                cout << "Archivo " << nombretxt << " todo melo todo bacano, hecho correctamente" << endl;

                delete[] datos1;
                delete[] datos2;
                delete[] datosresultantes;
                datos1 = nullptr ; datos2 = nullptr ; datosresultantes = nullptr;

            }
            else if(desicion == 100){
                char nombretxt[20];
                char nombretxt1[20];
                int size = width * height * 3;
                //se empieza lo mas complicadito

                cout<<"Ingresa en donde se pondra la semilla : "<<endl;
                cin >> seed;

                // me ire a esa semilla y sumare los valores que hay en el .txt con los valores
                // de la semilla.
                cout<<"Ingresa el .txt en donde se pondra la mascara :"<<endl;
                cin>>nombretxt;
                int* datos = leertxt(nombretxt, width, height);
                cout<<"Ingresa el .txt en donde estan los datos relacionados con la mascara : "<<endl;
                cin >> nombretxt1;
                 int* datos1 = leertxt(nombretxt1, width, height);
                //seed -= 1;
                seed = seed * 3;

                 // necesito saber el tamaño de la mascara
                int tamaño = 0;
                cout<<"Por comodidad y tiempo, dime de cuanto es el producto de la dimension de la mascara  "<<endl;
                cin>>tamaño;

                for(int i = 0; i < tamaño ; i++){
                    datos[seed + i] = (datos[seed + i]) + datos1[i];
                }
                //pongo el rango otra vez, si yo y mi rango

                for(int i = 0; i < size; i++ ){
                    if(datos[i] > 255){
                        datos[i] = datos[i] % 256;
                    }else if(datos[i] < 0){
                        datos[i] = datos[i] + 256;
                    }
                }

                cout<<"Ingresa el nombre del .txt  en donde guardaras esta transformacion "<<endl;
                cin>>nombretxt;
                ofstream archivo(nombretxt);
                if (!archivo.is_open()) {
                    cout << "error al abrir el archivo" << endl;
                }

                //Para la semilla
                archivo << seed / 3 << endl;
                    //Me copia los rgb :>
                size = width * height * 3 ;
                for (int i = 0; i < size; i += 3) {
                    archivo << datos[i]  << " " << datos[i + 1] << " " << datos[i + 2] << endl;
                }

                archivo.close();
                cout << "Archivo " << nombretxt << " todo melo" << endl;




                delete[] datos;
                delete[] datos1;
                datos = nullptr;
                datos1 = nullptr;

            }
        }


        return 0;

    }

/* esto unicamente me lee , los valores que hay en el array que lee la imagen bmp
    for (int i = 0; i < width * height * 3; i += 3) {
        cout << "Pixel " << i / 3 << ": ("
             << pixelData[i] + 48 << ", "
             << pixelData[i + 1] + 48 << ", "
             << pixelData[i + 2] + 48 << ")" << endl;
    }*/

    // Libera la memoria usada para los píxeles


    // Variables para almacenar la semilla y el número de píxeles leídos del archivo de enmascaramiento


    // Carga los datos de enmascaramiento desde un archivo .txt (semilla + valores RGB)
    //M1.txt
/*    unsigned int *maskingData = loadSeedMasking("lecturaimagen_aleatoria.txt", seed, n_pixels);

    // Muestra en consola los primeros valores RGB leídos desde el archivo de enmascaramiento
    for (int i = 0; i < n_pixels * 3; i += 3) {
        cout << "Pixela " << i / 3 << ": ("
             << maskingData[i] << ", "
             << maskingData[i + 1] << ", "
             << maskingData[i + 2] << ")" << endl;
    }

    // librerando todo despues

    // Libera la memoria usada para los datos leidos
    if (maskingData != nullptr){
        delete[] maskingData;
        maskingData = nullptr;
    }*/



unsigned char* loadPixels(QString input, int &width, int &height){
    /*
 * @brief Carga una imagen BMP desde un archivo y extrae los datos de píxeles en formato RGB.
 *
 * Esta función utiliza la clase QImage de Qt para abrir una imagen en formato BMP, convertirla al
 * formato RGB888 (24 bits: 8 bits por canal), y copiar sus datos de píxeles a un arreglo dinámico
 * de tipo unsigned char. El arreglo contendrá los valores de los canales Rojo, Verde y Azul (R, G, B)
 * de cada píxel de la imagen, sin rellenos (padding).
 *
 * @param input Ruta del archivo de imagen BMP a cargar (tipo QString).
 * @param width Parámetro de salida que contendrá el ancho de la imagen cargada (en píxeles).
 * @param height Parámetro de salida que contendrá la altura de la imagen cargada (en píxeles).
 * @return Puntero a un arreglo dinámico que contiene los datos de los píxeles en formato RGB.
 *         Devuelve nullptr si la imagen no pudo cargarse.
 *
 * @note Es responsabilidad del usuario liberar la memoria asignada al arreglo devuelto usando `delete[]`.
 */

    // Cargar la imagen BMP desde el archivo especificado (usando Qt)

    QImage imagen(input); // aqui cargamos la ruta de la imagen osea la imagen como tal xd.


    // Verifica si la imagen fue cargada correctamente
    if (imagen.isNull()) {
        cout << "Error: No se pudo cargar la imagen BMP." << std::endl;
        return nullptr; // Retorna un puntero nulo si la carga falló
    }

    // Convierte la imagen al formato RGB888 (3 canales de 8 bits sin transparencia)
    imagen = imagen.convertToFormat(QImage::Format_RGB888);

    // Obtiene el ancho y el alto de la imagen cargada
    width = imagen.width();
    height = imagen.height();

    // Calcula el tamaño total de datos (3 bytes por píxel: R, G, B)
    int dataSize = width * height * 3; // aqui nos dan los datos en bytes me parece curioso que si
    // lo multiplicamos * 24 nos dan los datos en bits, quiza lo utilize en bits hay que mirar.

    // Reserva memoria dinámica para almacenar los valores RGB de cada píxel
    unsigned char* pixelData = new unsigned char[dataSize]; // todos los datos son en bytes especificamente cp 3 bytes

    // Copia cada línea de píxeles de la imagen Qt a nuestro arreglo lineal
    for (int y = 0; y < height; ++y) {
        const uchar* srcLine = imagen.scanLine(y);              // Línea original de la imagen con posible padding

        // ese uchar me asusto --> significa unsigned char hahaha

        unsigned char* dstLine = pixelData + y * width * 3;     // Línea destino en el arreglo lineal sin padding
        memcpy(dstLine, srcLine, width * 3);                    // Copia los píxeles RGB de esa línea (sin padding)
    }

    // Retorna el puntero al arreglo de datos de píxeles cargado en memoria
    return pixelData;
}

bool exportImage(unsigned char* pixelData, int width,int height, QString archivoSalida){
    /*
 * @brief Exporta una imagen en formato BMP a partir de un arreglo de píxeles en formato RGB.
 *
 * Esta función crea una imagen de tipo QImage utilizando los datos contenidos en el arreglo dinámico
 * `pixelData`, que debe representar una imagen en formato RGB888 (3 bytes por píxel, sin padding).
 * A continuación, copia los datos línea por línea a la imagen de salida y guarda el archivo resultante
 * en formato BMP en la ruta especificada.
 *
 * @param pixelData Puntero a un arreglo de bytes que contiene los datos RGB de la imagen a exportar.
 *                  El tamaño debe ser igual a width * height * 3 bytes.
 * @param width Ancho de la imagen en píxeles.
 * @param height Alto de la imagen en píxeles.
 * @param archivoSalida Ruta y nombre del archivo de salida en el que se guardará la imagen BMP (QString).
 *
 * @return true si la imagen se guardó exitosamente; false si ocurrió un error durante el proceso.
 *
 * @note La función no libera la memoria del arreglo pixelData; esta responsabilidad recae en el usuario.
 */

    // Crear una nueva imagen de salida con el mismo tamaño que la original
    // usando el formato RGB888 (3 bytes por píxel, sin canal alfa)
    QImage outputImage(width, height, QImage::Format_RGB888);

    // Copiar los datos de píxeles desde el buffer al objeto QImage
    for (int y = 0; y < height; ++y) {
        // outputImage.scanLine(y) devuelve un puntero a la línea y-ésima de píxeles en la imagen
        // pixelData + y * width * 3 apunta al inicio de la línea y-ésima en el buffer (sin padding)
        // width * 3 son los bytes a copiar (3 por píxel)
        memcpy(outputImage.scanLine(y), pixelData + y * width * 3, width * 3);
    }

    // Guardar la imagen en disco como archivo BMP
    if (!outputImage.save(archivoSalida, "BMP")) {
        // Si hubo un error al guardar, mostrar mensaje de error
        cout << "Error: No se pudo guardar la imagen BMP modificada.";
        return false; // Indica que la operación falló
    } else {
        // Si la imagen fue guardada correctamente, mostrar mensaje de éxito
        cout << "Imagen BMP modificada guardada como " << archivoSalida.toStdString() << endl;
        return true; // Indica éxito
    }

}

unsigned int* loadSeedMasking(const char* nombreArchivo, int &seed, int &n_pixels){
    /*
 * @brief Carga la semilla y los resultados del enmascaramiento desde un archivo de texto.
 *
 * Esta función abre un archivo de texto que contiene una semilla en la primera línea y,
 * a continuación, una lista de valores RGB resultantes del proceso de enmascaramiento.
 * Primero cuenta cuántos tripletes de píxeles hay, luego reserva memoria dinámica
 * y finalmente carga los valores en un arreglo de enteros.
 *
 * @param nombreArchivo Ruta del archivo de texto que contiene la semilla y los valores RGB.
 * @param seed Variable de referencia donde se almacenará el valor entero de la semilla.
 * @param n_pixels Variable de referencia donde se almacenará la cantidad de píxeles leídos
 *                 (equivalente al número de líneas después de la semilla).
 *
 * @return Puntero a un arreglo dinámico de enteros que contiene los valores RGB
 *         en orden secuencial (R, G, B, R, G, B, ...). Devuelve nullptr si ocurre un error al abrir el archivo.
 *
 * @note Es responsabilidad del usuario liberar la memoria reservada con delete[].
 */

    // Abrir el archivo que contiene la semilla y los valores RGB
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        // Verificar si el archivo pudo abrirse correctamente
        cout << "No se pudo abrir el archivo." << endl;
        return nullptr;
    }

    // Leer la semilla desde la primera línea del archivo
    archivo >> seed;

    int r, g, b;

    // Contar cuántos grupos de valores RGB hay en el archivo
    // Se asume que cada línea después de la semilla tiene tres valores (r, g, b)
    while (archivo >> r >> g >> b) {
        n_pixels++;  // Contamos la cantidad de píxeles
    }

    // Cerrar el archivo para volver a abrirlo desde el inicio
    archivo.close();
    archivo.open(nombreArchivo);

    // Verificar que se pudo reabrir el archivo correctamente
    if (!archivo.is_open()) {
        cout << "Error al reabrir el archivo." << endl;
        return nullptr;
    }

    // Reservar memoria dinámica para guardar todos los valores RGB
    // Cada píxel tiene 3 componentes: R, G y B
    unsigned int* RGB = new unsigned int[n_pixels * 3];

    // Leer nuevamente la semilla desde el archivo (se descarta su valor porque ya se cargó antes)
    archivo >> seed;

    // Leer y almacenar los valores RGB uno por uno en el arreglo dinámico
    for (int i = 0; i < n_pixels * 3; i += 3) {
        archivo >> r >> g >> b;
        RGB[i] = r;
        RGB[i + 1] = g;
        RGB[i + 2] = b;
    }

    // Cerrar el archivo después de terminar la lectura
    archivo.close();

    // Mostrar información de control en consola
    cout << "Semilla: " << seed << endl;
    cout << "Cantidad de píxeles leídos: " << n_pixels << endl;

    // Retornar el puntero al arreglo con los datos RGB
    return RGB;

}


//Funcion propia para crear del array datos

void creartxt(char nombretxt[] , unsigned char* pixelData, int seed ,int width,int height){
    ofstream archivo(nombretxt);
    if (!archivo.is_open()) {
        cout << "error al abrir el archivo" << endl;
    }

    //Para la semilla
    archivo << seed << endl;

    //Me copia los rgb :>
    for (int i = 0; i < width * height * 3; i += 3) {
        archivo << pixelData[i] + 48 << " " << pixelData[i + 1] + 48 << " " << pixelData[i + 2]+ 48 << endl;
    }
    for (int i = 0; i < width * height * 3; i += 3) {
        if(pixelData[i] >= 255){
            pixelData[i] = pixelData[i] % 256;
            archivo << pixelData[i] << " ";
        } else if(pixelData[i] < 0){  pixelData[i] = (pixelData[i] + 256);
            archivo << pixelData[i] << " ";}
        /*else if(pixelData[i] < 0){
            pixelData[i] = pixelData[i] + 256;
            archivo << pixelData[i] << " ";
        }*/

    }

    archivo.close();
    cout << "Archivo " << nombretxt << " todo melo" << endl;
}
int* leertxt(char nombretxt[], int width, int height) {
    ifstream archivo(nombretxt);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo";
        return nullptr;
    }

    int size = width * height * 3;
    int* datos = new int[size];
    int i = 0;

    //salto la primera linea
    // osea leo la primera linea y la descarto
    string linea;
    getline(archivo, linea);


    int r, g, b;
    while (archivo >> r >> g >> b && i < size) {
        datos[i++] = r;
        datos[i++] = g;
        datos[i++] = b;
    }


    // creare el filtro de rango de una vez para no estar poniendolo cada momentico
    for (int i = 0; i < size; i += 3) {
        if(datos[i] >= 255){
            datos[i] = datos[i] % 256;
        }
        else if(datos[i] < 0){
            datos[i] = datos[i] + 256;
        }}

    archivo.close();
    return datos;
}








