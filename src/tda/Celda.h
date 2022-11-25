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

Celda::~Celda(){
  delete this->celula;
  delete this->celulaFutura;
}


#endif // CELDA_H_