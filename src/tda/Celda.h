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
    EstadoCelula getEstadoCelula();
    void revivirCelula(bool futura);
    void matarCelula(bool futura);
    unsigned int getNivel();
    unsigned int getFila();
    unsigned int getColumna();
    bool estaVacia();
    bool celulaViva();
    bool celulaMuerta();
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
EstadoCelula Celda::getEstadoCelula(){
  return this->celula->getEstado();
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

bool Celda::estaVacia(){
  return this == NULL;
}

bool Celda::celulaViva(){
  return this->celula->celulaViva();
}
bool Celda::celulaMuerta(){
  return this->celula->celulaMuerta();
}

#endif // CELDA_H_