#ifndef TABLERO_H_
#define TABLERO_H_

#include <string>

#include "Lista.h"
#include "Celda.h"

class Tablero {

  private:
    unsigned int columnas;
    unsigned int filas;
    unsigned int niveles;
    Lista<Lista<Lista<Celda *> *> *> * tablero;
  
    void validarDimensiones(unsigned int nivel, unsigned int columna, unsigned int fila);

  public:
    Tablero(unsigned int niveles, unsigned int columnas, unsigned int filas);
    ~Tablero();
    unsigned int getCantidadColumnas();
    unsigned int getCantidadFilas();
    unsigned int getCantidadNiveles();
    Celda * getCelda(unsigned int nivel, unsigned int fila, unsigned int columna);
    void getCeldasVecinas(/*Lista<Celda *>* celdasVecinas,*/ unsigned int nivel, unsigned int fila, unsigned int columna);
    void getCeldasColumnaVecinas(Lista<Celda *>* celdasVecinas, Lista<Celda *> * columnaCeldas, unsigned int columna, bool incluirCentro);
    unsigned int calcularNivelCircular(unsigned int nivel, int incremento);
    unsigned int calcularColumnaCircular(unsigned int columna, int incremento);
    unsigned int calcularFilaCircular(unsigned int fila, int incremento);
};

Tablero::Tablero(unsigned int niveles, unsigned int filas, unsigned int columnas){

  this->columnas = columnas;
  this->filas = filas;
  this->niveles = niveles;

    this->tablero = new Lista<Lista<Lista<Celda *> *> *>();

    for(int i = 0; i < niveles; i++){
      Lista<Lista<Celda *> *>* tempNivel = new Lista<Lista<Celda *> *>();

      for(int j = 0; j < filas; j++){
        Lista<Celda *> * tempFila = new Lista<Celda *>();
        
        for(int k = 0; k < columnas; k++){
          tempFila->agregar(new Celda()); // agrego el valor de la columna
        }

        tempNivel->agregar(tempFila); // agrego columna
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
      Lista<Celda *> * tempFila = tempNivel->obtenerCursor();
      tempFila->iniciarCursor();

      while(tempFila->avanzarCursor()){
        Celda * celda = tempFila->obtenerCursor();
        delete celda;
      }

      delete tempFila;
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

Celda * Tablero::getCelda(unsigned int nivel, unsigned int fila, unsigned int columna){
  Lista<Lista<Celda *> *> * tempNivel = this->tablero->obtener(nivel);
  Lista<Celda *> * tempFila = tempNivel->obtener(fila);
  return tempFila->obtener(columna);
}


/*
  pre: celdas vecinas debe estar vacia.
*/
void Tablero::getCeldasVecinas(/*Lista<Celda *>* celdasVecinas,*/ unsigned int nivel, unsigned int fila, unsigned int columna){
  Lista<Celda *>* celdasVecinas2 = new Lista<Celda *>();
  if( !celdasVecinas2->estaVacia())
    throw "La lista debe estar vacia";

  this->validarDimensiones(nivel, fila, columna);

  // Recorro los niveles
  for( int i = -1; i < 2; i++){
    int nivelActual = calcularNivelCircular(nivel, i);
    Lista<Lista<Celda *> *> * tempNivel = this->tablero->obtener(nivelActual);

    for(int j = -1; j < 2; j++){
      int filaActual = calcularFilaCircular(fila, i);
      Lista<Celda *> * tempFila = tempNivel->obtener(filaActual);

      bool incluirCentro = !(i == 0 && j == 0);
      getCeldasColumnaVecinas(celdasVecinas2, tempFila, columna, incluirCentro);
    }

  }
}

/*
  pre: la lista filaCeldas no puede estar vacia
  pos: agrega a la lista celdasVecinas las celdas vecinas e incluye la celda central si esta incluirCentro en true
*/
void Tablero::getCeldasColumnaVecinas(Lista<Celda *>* celdasVecinas, Lista<Celda *> * columnaCeldas, unsigned int columna, bool incluirCentro){
  if( columnaCeldas->estaVacia())
    throw "La columna esta vacia";
  for(int i = -1; i < 2; i++){
    if( i == 0 && !incluirCentro) continue;
    unsigned int columnaActual = this->calcularColumnaCircular(columna, i);
    celdasVecinas->agregar( columnaCeldas->obtener(columnaActual));
  }
}

/*
  pre: -
  pos: devlueve true si los parametros son mayores a cero y menores que los maximos establecidos en el constructor
*/
void Tablero::validarDimensiones(unsigned int nivel, unsigned int fila, unsigned int columna){
  if( nivel <= 0 || nivel > this->niveles){
    throw "El nivel debe ser mayor a 0 y menor a " + std::to_string(this->niveles);
  }
  if( fila <= 0 || fila > this->filas){
    throw "El nivel debe ser mayor a 0 y menor a " + std::to_string(this->filas);
  }
  if( columna <= 0 || columna > this->columnas){
    throw "El nivel debe ser mayor a 0 y menor a " + std::to_string(this->columnas);
  }
}

unsigned int Tablero::calcularNivelCircular(unsigned int nivel, int incremento){
  int nivelActual = nivel + incremento;

  if(nivelActual <= 0)
    return this->niveles;

  if(nivelActual > this->niveles)
    return 1;

  return nivelActual;
}

unsigned int Tablero::calcularFilaCircular(unsigned int fila, int incremento){
  int filaActual = fila + incremento;

  if(filaActual <= 0)
    return this->filas;

  if(filaActual > this->filas)
    return 1;

  return filaActual;
}

unsigned int Tablero::calcularColumnaCircular(unsigned int columna, int incremento){
  int columnaActual = columna + incremento;

  if(columnaActual <= 0)
    return this->columnas;

  if(columnaActual > this->columnas)
    return 1;

  return columnaActual;
}

#endif // TABLERO_H_