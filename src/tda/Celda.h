#ifndef CELDA_H_
#define CELDA_H_

#include "Celula.h"

enum Comportamiento {
  Inerte,
  Zombie,
  Decay,
  FALTA_UNO,
  Radioactiva,
  Portal
};

class Celda {
  private:
    Celula * celula;
    Celula * celulaFutura;
    Comportamiento comportamiento;
    unsigned int nivel;
    unsigned int fila;
    unsigned int columna;

  
  public:
    Celda(unsigned int nivel, unsigned int fila, unsigned int columna);
    ~Celda();
    EstadoCelula getEstadoCelula(bool futura);
    void revivirCelula(bool futura);
    void matarCelula(bool futura);
    unsigned int getNivel();
    unsigned int getFila();
    unsigned int getColumna();
    bool estaVacia();
    bool celulaViva();
    bool celulaMuerta();
    unsigned int getCargaGenetica(bool futura, unsigned int posicion);
    void setCargaGenetica(bool futura, unsigned int posicion, unsigned int cargaGenetica);
    unsigned int getCantidadGenes();
};

/*
  pre: -
  pos: crea una celula con la carga genetica en 0, muerta e inerte
*/
Celda::Celda(unsigned int nivel, unsigned int fila, unsigned int columna){
  this->celula = new Celula();
  this->celulaFutura = new Celula();
  this->comportamiento = Inerte;
  this->nivel = nivel;
  this->fila = fila;
  this->columna = columna;
}

/*
  pre: -
  pos: destruye el objeto liberando la memoria solicitada
*/
Celda::~Celda(){
  delete this->celula;
  delete this->celulaFutura;
}

/*
  pre: -
  pos: devuelve el estado de la celula actual
*/
EstadoCelula Celda::getEstadoCelula(bool futura){
  if(futura){
    return this->celulaFutura->getEstado();
  }
  else{
    return this->celula->getEstado();
  }
}

/*
  pre: -
  pos: cambia el estado de la celula a Viva
*/
void Celda::revivirCelula(bool futura){
  if(futura){
    this->celulaFutura->revivir();
  }
  else{
    this->celula->revivir();
  }
}

/*
  pre: -
  pos: cambia el estado de la celula a Viva
*/
void Celda::matarCelula(bool futura){
  if(futura){
    this->celulaFutura->matar();
  }
  else{
    this->celula->matar();
  }
}

unsigned int Celda::getNivel(){
  return this->nivel;
}

unsigned int Celda::getFila(){
  return this->fila;
}

unsigned int Celda::getColumna(){
  return this->columna;
}

/*
  pre: -
  pos: devuelve true si la celda es nula
*/
bool Celda::estaVacia(){
  return this == NULL;
}

bool Celda::celulaViva(){
  return this->celula->celulaViva();
}
bool Celda::celulaMuerta(){
  return this->celula->celulaMuerta();
}

/*
  pre: posicion tiene que ser mayor a 0 y menor a la cantidad de genes que tenga la celula
  pos: devuelve la carga genetica de la posicion solicitada
*/
unsigned int Celda::getCargaGenetica(bool futura, unsigned int posicion){
  if( posicion <= 0 || posicion > this->celula->getCantidadGenes())
    throw "Posicion invalida";

  if(futura){
    return this->celulaFutura->getCargaGenetica(posicion);
  }
  else{
    return this->celula->getCargaGenetica(posicion);
  }
}

/*
  pre: posicion tiene que ser mayor a 0 y menor a la cantidad de genes que tenga la celula
*/
void Celda::setCargaGenetica(bool futura, unsigned int posicion, unsigned int cargaGenetica){
  if( posicion <= 0 || posicion > this->celula->getCantidadGenes())
    throw "Posicion invalida";

  if(futura){
    this->celulaFutura->actualizarGen(posicion, cargaGenetica);
  }
  else{
    this->celula->actualizarGen(posicion, cargaGenetica);
  }
}

unsigned int Celda::getCantidadGenes(){
  return this->celula->getCantidadGenes();
}

#endif // CELDA_H_