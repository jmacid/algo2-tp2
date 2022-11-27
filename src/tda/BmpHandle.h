#ifndef BMP_HANDLE_H_
#define BMP_HANDLE_H_

#include <string>
#include "../easyBMP/EasyBMP.h"

class BmpHandle {
  private:
    unsigned int altoImagen;
    unsigned int anchoImagen;
    BMP Output;
    

  public:
    BmpHandle(unsigned int altoDatos, unsigned int anchoDatos);
    ~BmpHandle();
    void validar(unsigned int fila, unsigned int columna, unsigned char R, unsigned char G, unsigned char B);
    void imprimirCuadradito(unsigned int fila, unsigned int columna, unsigned char R, unsigned char G, unsigned char B);
    void iniciar();
    void finalizar(string nombreArchivo);
};


/*
  pre: filas y columnas debe ser mayor a cero
  pos: inicializa el objeto
*/
BmpHandle::BmpHandle(unsigned int filas, unsigned int columnas){
  if( filas <= 0 || columnas <= 0){
    throw "El ancho y alto de los datos ";
  }
  this->altoImagen = filas; // * altoCuadrado;
  this->anchoImagen = columnas; // * anchoCuadrado;
}

/*
  pre: -
  pos: destruye el objeto
*/
BmpHandle::~BmpHandle(){}


/*
  pre: x e y deben ser mayores o iguales a cero y menor a las dimensiones de la imagen. R, G y B deben estar entre 0 y 255.
  pos: devuelve true si se cumplen con las condiciones de la pre
*/
void BmpHandle::validar(unsigned int fila, unsigned int columna, unsigned char R, unsigned char G, unsigned char B){
  if(fila < 0 || columna < 0){
    throw "La fila y la posicion debe ser mayor a cero";
  }

  if(fila > this->altoImagen || columna > this->anchoImagen){
    throw "La fila y la columna deben ser menores al ancho de la imagen";
  }

  if(R < 0 || R > 255){
    throw "El color rojo tiene que estar entre 0 y 255";
  }

  if(G < 0 || G > 255){
    throw "El color verde tiene que estar entre 0 y 255";
  }
  
  if(B < 0 || B > 255){
    throw "El color azul tiene que estar entre 0 y 255";
  }
}

/*
  pre: x e y deben ser mayores o iguales a cero y menor a las dimensiones de la imagen. R, G y B deben estar entre 0 y 255.
  pos: crea un cuadrado de anchoCuadrado x altoCuadrado en la ubicacion indicada.
*/
void BmpHandle::imprimirCuadradito(unsigned int fila, unsigned int columna, unsigned char R, unsigned char G, unsigned char B){
  this->validar(fila, columna, R, G, B);

  RGBApixel NewPixel = {R, G, B, 1};

  Output.SetPixel(columna, fila, NewPixel);
  return;
}

/*
  pre: -
  pos: realiza la configuracion de la imagen
*/
void BmpHandle::iniciar(){
  this->Output.SetSize( this->anchoImagen , this->altoImagen);
  this->Output.SetBitDepth( 24 ); // 8 8 8
}

/*
  pre: el nombre no puede estar vacio
  pos: graba la imagen en un archivo
*/
void BmpHandle::finalizar(string nombreArchivo){
  if( nombreArchivo.empty())
    throw "El nombre del archivo no puede estar vacio";

  string nombreArchivoConExtension = nombreArchivo + ".bmp";
  const char * constNombreArchivoConExtension = nombreArchivoConExtension.c_str();
  this->Output.WriteToFile(constNombreArchivoConExtension);
}

#endif // BMP_HANDLE_H_