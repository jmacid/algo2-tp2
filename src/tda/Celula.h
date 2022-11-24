#ifndef CELULA_H_
#define CELULA_H_

#include <iostream>
#include "Gen.h"
#include "Vector.h"

enum EstadoCelula {
  Viva, 
  Muerta
};

class Celula {
  private:
    EstadoCelula estado;
    Vector<Gen *> * genes;

  public:
    Celula(unsigned int cantidadGenes, unsigned int maximaCargaGenetica);
    ~Celula();
    EstadoCelula getEstado();
    unsigned int getCargaGenetica(unsigned int posicion);
    int getCantidadGenes();
};

/*
  pre: la cantidad de genes no puede ser menos o igual a cero
  pos: crea el objeto celula muerta con todos los genes en 0 
*/
Celula::Celula(unsigned int cantidadGenes, unsigned int maximaCargaGenetica) {
  if(cantidadGenes <= 0)
    throw "(celula) Cantidad de genes no puede ser menos o igual a cero";

  this->estado = Muerta;
  this->genes = new Vector<Gen *>(cantidadGenes, NULL);

  int longuitud = this->genes->getLongitud();
  for(int i = 0; i < longuitud; i++ ){
    this->genes->agregar(i + 1, new Gen(maximaCargaGenetica, 0));
  }
}

/*
  pre: la cantidad de genes no puede ser menos o igual a cero
  pos: crea el objeto celula muerta con todos los genes en 0 
*/
Celula::~Celula() {

  int longuitud = this->genes->getLongitud();
  for(int i = 0; i < longuitud; i++ ){
    Gen* gen = this->genes->obtener(i + 1);
    delete gen;
  }

  delete this->genes;
}

/*
  pre: -
  pos: devuelve el estado de la celula
*/
EstadoCelula Celula::getEstado(){
  return this->estado;
}

/*
  pre: la posicion debe ser mayor a 1 y menor a la cantidad de genes
  pos: retorna la carga genetica del gen solicitado
*/
unsigned int Celula::getCargaGenetica(unsigned int posicion){
  if( posicion < 0 || posicion > this->genes->getLongitud())
    throw "La posicion solicitada es incorrecta. Debe ser mayor a cero y menor a " + this->genes->getLongitud();
  return this->genes->obtener(posicion)->getCargaGentica();
}

/*
  pre: -
  pos: retorna la cantidad de genes
*/
int Celula::getCantidadGenes(){
  return this->genes->getLongitud();
}

#endif // CELULA_H_