#ifndef TABLERO_H_
#define TABLERO_H_

#include <iostream>
#include <string>

using namespace std;

#include "Lista.h"
#include "Celda.h"
#include "AdminDeCeldas.h"
#include "BmpHandle.h"

class Tablero {

  private:
    unsigned int columnas;
    unsigned int filas;
    unsigned int planos;
    Lista<Lista<Lista<Celda *> *> *> * tablero;
  
    void validarDimensiones(unsigned int nivel, unsigned int columna, unsigned int fila);

  public:
    Tablero(unsigned int planos, unsigned int columnas, unsigned int filas);
    ~Tablero();
    unsigned int getCantidadColumnas();
    unsigned int getCantidadFilas();
    unsigned int getCantidadPlanos();
    Celda * getCelda(unsigned int nivel, unsigned int fila, unsigned int columna);
    void getCeldasVecinas(Lista<Celda *>* celdasVecinas, unsigned int nivel, unsigned int fila, unsigned int columna);
    void getCeldasColumnaVecinas(Lista<Celda *>* celdasVecinas, Lista<Celda *> * columnaCeldas, unsigned int columna, bool incluirCentro);
    unsigned int calcularNivelCircular(unsigned int nivel, int incremento);
    unsigned int calcularColumnaCircular(unsigned int columna, int incremento);
    unsigned int calcularFilaCircular(unsigned int fila, int incremento);

    void actualizarTablero(AdminDeCeldas* adminDeCeldas, unsigned int& nacimientos, unsigned int& fallecimientos);
    void syncTablero(AdminDeCeldas* adminDeCeldas, bool destinoFutura);
    void imprimirTablero();
    void imprimirImagenDelTablero();
};

Tablero::Tablero(unsigned int planos, unsigned int filas, unsigned int columnas){

  this->columnas = columnas;
  this->filas = filas;
  this->planos = planos;

    this->tablero = new Lista<Lista<Lista<Celda *> *> *>();

    for(int i = 0; i < planos; i++){
      Lista<Lista<Celda *> *>* tempPlano = new Lista<Lista<Celda *> *>();

      for(int j = 0; j < filas; j++){
        Lista<Celda *> * tempFila = new Lista<Celda *>();
        
        for(int k = 0; k < columnas; k++){
          // cout << i+1 << " " << j+1 << " " << k+1 << endl;
          tempFila->agregar(new Celda(i+1, j+1, k+1)); // agrego el valor de la columna
        }

        tempPlano->agregar(tempFila); // agrego columna
      }

       this->tablero->agregar(tempPlano);
    }


}

Tablero::~Tablero(){
  this->tablero->iniciarCursor();
  while(this->tablero->avanzarCursor()){
    Lista<Lista<Celda *> *>* tempPlano = this->tablero->obtenerCursor();
    tempPlano->iniciarCursor();

    while(tempPlano->avanzarCursor()){
      Lista<Celda *> * tempFila = tempPlano->obtenerCursor();
      tempFila->iniciarCursor();

      while(tempFila->avanzarCursor()){
        Celda * celda = tempFila->obtenerCursor();
        delete celda;
        celda = NULL;
      }

      delete tempFila;
      tempFila = NULL;
    }

    delete tempPlano;
    tempPlano = NULL;
  }

  delete this->tablero;
  this->tablero = NULL;
}


unsigned int Tablero::getCantidadColumnas(){
  return this->columnas;
}

unsigned int Tablero::getCantidadFilas(){
  return this->filas;
}

unsigned int Tablero::getCantidadPlanos(){
  return this->planos;
}

/*
  pre: los parametros deben estar dentro del rango establecido en el construcor
*/
Celda * Tablero::getCelda(unsigned int nivel, unsigned int fila, unsigned int columna){
  this->validarDimensiones(nivel, fila, columna);

  Lista<Lista<Celda *> *> * tempPlano = this->tablero->obtener(nivel);
  Lista<Celda *> * tempFila = tempPlano->obtener(fila);
  return tempFila->obtener(columna);
}


/*
  pre: celdas vecinas debe estar vacia.
*/
void Tablero::getCeldasVecinas(Lista<Celda *>* celdasVecinas, unsigned int nivel, unsigned int fila, unsigned int columna){
  // Lista<Celda *>* celdasVecinas2 = new Lista<Celda *>();
  if( !celdasVecinas->estaVacia())
    throw "La lista debe estar vacia";

  this->validarDimensiones(nivel, fila, columna);

  // Recorro los planos
  for( int i = -1; i < 2; i++){
    int nivelActual = calcularNivelCircular(nivel, i);
    Lista<Lista<Celda *> *> * tempPlano = this->tablero->obtener(nivelActual);

    for(int j = -1; j < 2; j++){
      int filaActual = calcularFilaCircular(fila, j);
      Lista<Celda *> * tempFila = tempPlano->obtener(filaActual);

      bool incluirCentro = !(i == 0 && j == 0);
      this->getCeldasColumnaVecinas(celdasVecinas, tempFila, columna, incluirCentro);
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
    Celda * celda = columnaCeldas->obtener(columnaActual);
    // cout << "(" << celda->getPlano() << ", " << celda->getFila() << ", " << celda->getColumna() << ")" << endl;
    celdasVecinas->agregar(celda);
  }
}

/*
  pre: -
  pos: devlueve true si los parametros son mayores a cero y menores que los maximos establecidos en el constructor
*/
void Tablero::validarDimensiones(unsigned int nivel, unsigned int fila, unsigned int columna){
  if( nivel <= 0 || nivel > this->planos){
    throw "El nivel debe ser mayor a 0 y menor a " + std::to_string(this->planos);
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
    return this->planos;

  if(nivelActual > this->planos)
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

/*
  pre: adminDeCeldas no debe estar vacio
  pos: recorre todo el tablero actualizando cada celda
*/
void Tablero::actualizarTablero(AdminDeCeldas* adminDeCeldas, unsigned int& nacimientos, unsigned int& fallecimientos){
  if(adminDeCeldas->estaVacio())
    throw "adminDeCeldas no puede estar vacio";

  this->tablero->iniciarCursor();
  while(this->tablero->avanzarCursor()){
    // Plano
    Lista<Lista<Celda *> *> * tempPlano = this->tablero->obtenerCursor();
    tempPlano->iniciarCursor();
    while(tempPlano->avanzarCursor()){
      // Fila
      Lista<Celda *> * tempFila = tempPlano->obtenerCursor();
      tempFila->iniciarCursor();
      while(tempFila->avanzarCursor()){
        // Columna
        Celda * celda = tempFila->obtenerCursor();
        // cout << "Actualizando: " << celda->getPlano() << ", " << celda->getFila() << ", " << celda->getColumna() << endl;
        Lista<Celda *>* celdasVecinas = new Lista<Celda *>();
        this->getCeldasVecinas(celdasVecinas, celda->getPlano(), celda->getFila(), celda->getColumna());
        adminDeCeldas->actualizarCelda(celda, celdasVecinas, nacimientos, fallecimientos);
        delete celdasVecinas;
      }
    }
  }

}

/*
  pre: adminDeCeldas no debe estar vacio
  pos: recorre todo el tablero sincronizando cada celda futura con la actual o al reves
*/
void Tablero::syncTablero(AdminDeCeldas* adminDeCeldas, bool destinoFutura){
  if(adminDeCeldas->estaVacio())
    throw "adminDeCeldas no puede estar vacio";

  this->tablero->iniciarCursor();
  while(this->tablero->avanzarCursor()){
    // Plano
    Lista<Lista<Celda *> *> * tempPlano = this->tablero->obtenerCursor();
    tempPlano->iniciarCursor();
    while(tempPlano->avanzarCursor()){
      // Fila
      Lista<Celda *> * tempFila = tempPlano->obtenerCursor();
      tempFila->iniciarCursor();
      while(tempFila->avanzarCursor()){
        // Columna
        Celda * celda = tempFila->obtenerCursor();
        // cout << "Sincronizando: " << celda->getPlano() << ", " << celda->getFila() << ", " << celda->getColumna() << endl;
        adminDeCeldas->syncCelda(celda, destinoFutura);
      }
    }
  }
}

/*
  pre: -
  pos: recorre todo el tablero e imprime cada celda
*/
void Tablero::imprimirTablero(){
  this->tablero->iniciarCursor();
  int plano = 0;
  while(this->tablero->avanzarCursor()){
    // Plano
    plano++;
    cout << "Plano: " << plano << endl;
    Lista<Lista<Celda *> *> * tempPlano = this->tablero->obtenerCursor();
    tempPlano->iniciarCursor();
    while(tempPlano->avanzarCursor()){
      // Fila
      Lista<Celda *> * tempFila = tempPlano->obtenerCursor();
      tempFila->iniciarCursor();
      while(tempFila->avanzarCursor()){
        // Columna
        Celda * celda = tempFila->obtenerCursor();
        EstadoCelula estado = celda->getEstadoCelula(false);
        char estadoChar = estado == Viva ? 'V' : 'M';
        cout << estadoChar << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
}

/*
  pre: -
  pos: imprime una imagen de cada nivel del tablero
*/
void Tablero::imprimirImagenDelTablero(){
  this->tablero->iniciarCursor();
  int plano = 0;
  while(this->tablero->avanzarCursor()){
    // Plano
    plano++;
    BmpHandle* bmpHandle = new BmpHandle(this->getCantidadFilas(), this->getCantidadColumnas());
    bmpHandle->iniciar();
    string nombreArchivo = "Plano " + to_string(plano);

    Lista<Lista<Celda *> *> * tempPlano = this->tablero->obtenerCursor();
    tempPlano->iniciarCursor();
    while(tempPlano->avanzarCursor()){
      // Fila
      Lista<Celda *> * tempFila = tempPlano->obtenerCursor();
      tempFila->iniciarCursor();
      while(tempFila->avanzarCursor()){
        // Columna
        Celda * celda = tempFila->obtenerCursor();
        unsigned char gen1 = celda->getCargaGenetica(false, 1);
        unsigned char gen2 = celda->getCargaGenetica(false, 2);
        unsigned char gen3 = celda->getCargaGenetica(false, 3);
        bmpHandle->imprimirCuadradito(celda->getFila() - 1, celda->getColumna() - 1, gen1, gen2, gen3);
        //
      }
    }
    bmpHandle->finalizar(nombreArchivo);
    delete bmpHandle;
  }
}

#endif // TABLERO_H_