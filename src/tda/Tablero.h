#ifndef TABLERO_H_
#define TABLERO_H_

#include "Lista.h"
#include "Celda.h"

class Tablero {

  private:
    unsigned int columnas;
    unsigned int filas;
    unsigned int niveles;
    Lista<Lista<Lista<Celda *> *> *> * tablero;
  
  public:
    Tablero(unsigned int columnas, unsigned int filas, unsigned int niveles);
    ~Tablero();
    unsigned int getCantidadColumnas();
    unsigned int getCantidadFilas();
    unsigned int getCantidadNiveles();
    Celda * getCelda(unsigned int nivel, unsigned int columna, unsigned int fila);
};

Tablero::Tablero(unsigned int columnas, unsigned int filas, unsigned int niveles){

  this->columnas = columnas;
  this->filas = filas;
  this->niveles = niveles;

    this->tablero = new Lista<Lista<Lista<Celda *> *> *>();

    for(int i = 0; i < niveles; i++){
      Lista<Lista<Celda *> *>* tempNivel = new Lista<Lista<Celda *> *>();

      for(int j = 0; j < columnas; j++){
        Lista<Celda *> * tempColumna = new Lista<Celda *>();
        
        for(int k = 0; k < filas; k++){
          tempColumna->agregar(new Celda()); // agrego el valor de la fila
        }

        tempNivel->agregar(tempColumna); // agrego columna
      }

       this->tablero->agregar(tempNivel);
    }


}

Tablero::~Tablero(){
  this->tablero->iniciarCursor();
  while(this->tablero->avanzarCursor()){
    Lista<Lista<Celda *> *>* tempNivel = this->tablero->obtenerCursor();
    tempNivel->iniciarCursor();
    while(tempNivel->avanzarCursor()){
      Lista<Celda *> * tempColumna = tempNivel->obtenerCursor();
      tempColumna->iniciarCursor();
      while(tempColumna->avanzarCursor()){
        Celda * celda = tempColumna->obtenerCursor();
        delete celda;
      }
      delete tempColumna;
    }
    delete tempNivel;
  }

  delete this->tablero;
}


unsigned int Tablero::getCantidadColumnas(){
  return this->columnas;
}

unsigned int Tablero::getCantidadFilas(){
  return this->filas;
}

unsigned int Tablero::getCantidadNiveles(){
  return this->niveles;
}

Celda * Tablero::getCelda(unsigned int nivel, unsigned int columna, unsigned int fila){
  Lista<Lista<Celda *> *> * tempNivel = this->tablero->obtener(nivel);
  Lista<Celda *> * tempColumna = tempNivel->obtener(columna);
  return tempColumna->obtener(fila);
}

#endif // TABLERO_H_