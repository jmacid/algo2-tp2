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
  
  public:
    Celda();
    ~Celda();
    EstadoCelula getEstadoCelula();
    void revivirCelula();
    void matarCelula();
};

/*
  pre: -
  pos: crea una celula con la carga genetica en 0, muerta e inerte
*/
Celda::Celda(){
  this->celula = new Celula();
  this->celulaFutura = new Celula();
  this->comportamiento = Inerte;
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
void Celda::revivirCelula(){
  this->celula->revivir();
}

/*
  pre: -
  pos: cambia el estado de la celula a Viva
*/
void Celda::matarCelula(){
  this->celula->matar();
}


#endif // CELDA_H_