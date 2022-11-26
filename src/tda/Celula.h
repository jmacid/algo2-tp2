#ifndef CELULA_H_
#define CELULA_H_

#include <iostream>
#include "Gen.h"
#include "Vector.h"
#include "../constantes.h"


enum EstadoCelula {
  Viva, 
  Muerta
};

class Celula {
  private:
    EstadoCelula estado;
    Vector<Gen *> * genes;

  public:
    Celula();
    Celula(unsigned int cantidadGenes, unsigned int maximaCargaGenetica);
    ~Celula();
    EstadoCelula getEstado();
    unsigned int getCargaGenetica(unsigned int posicion);
    unsigned int getCargaMaximaGenetica();
    int getCantidadGenes();
    void actualizarGen(unsigned int posicion, unsigned int cargaGenetica);
    void revivir();
    void matar();
    bool celulaViva();
    bool celulaMuerta();
    bool estaVacia();
};


/*
  pre: -
  pos: crea el objeto celula muerta y los genes en un numero aleatorio
*/
Celula::Celula() {
  this->estado = Muerta;
  this->genes = new Vector<Gen *>(cantidadGenes, NULL);

  int longuitud = this->genes->getLongitud();
  for(int i = 0; i < longuitud; i++ ){
    this->genes->agregar(i + 1, new Gen(maximaCargaGenetica));
  }
}

/*
  pre: la cantidad de genes no puede ser menos o igual a cero
  pos: crea el objeto celula muerta y los genes en un numero aleatorio
*/
Celula::Celula(unsigned int cantidadGenes, unsigned int maximaCargaGenetica) {
  if(cantidadGenes <= 0)
    throw "(celula) Cantidad de genes no puede ser menos o igual a cero";

  this->estado = Muerta;
  this->genes = new Vector<Gen *>(cantidadGenes, NULL);

  int longuitud = this->genes->getLongitud();
  for(int i = 0; i < longuitud; i++ ){
    this->genes->agregar(i + 1, new Gen(maximaCargaGenetica));
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
    gen = NULL;
  }

  delete this->genes;
  this->genes = NULL;
}

/*
  pre: -
  pos: devuelve el estado de la celula
*/
EstadoCelula Celula::getEstado(){
  return this->estado;
}

/*
  pre: -
  pos: devulve true si la celula esta viva
*/
bool Celula::celulaViva(){
  return this->estado == Viva;
}

/*
  pre: -
  pos: devulve true si la celula esta muerta
*/
bool Celula::celulaMuerta(){
  return this->estado == Muerta;
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
  pos: retorna la carga genetica maxima del primer gen encontrado, sino un 0
*/
unsigned int Celula::getCargaMaximaGenetica(){
  for(int i = 0; i < this->genes->getLongitud(); i++){
    return this->genes->obtener(i + 1)->getMaximoCargaGenetica();
  }
  return 0;
}

/*
  pre: -
  pos: retorna la cantidad de genes
*/
int Celula::getCantidadGenes(){
  return this->genes->getLongitud();
}

/*
  pre: -
  pos: retorna la cantidad de genes
*/
void Celula::actualizarGen(unsigned int posicion, unsigned int cargaGenetica){
  Gen * gen = this->genes->obtener(posicion);
  gen->setCargaGentica(cargaGenetica);
  return;
}

/*
  pre: -
  pos: cambia el estado de la celula a Viva
*/
void Celula::revivir(){
  this->estado = Viva;
}

/*
  pre: -
  pos: cambia el estado de la celula a Muerta
*/
void Celula::matar(){
  this->estado = Muerta;
}

/*
  pre: -
  pos: devuelve true si la celula es nula
*/
bool Celula::estaVacia(){
  return this == NULL;
}

#endif // CELULA_H_