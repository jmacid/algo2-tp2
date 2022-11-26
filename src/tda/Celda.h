#ifndef CELDA_H_
#define CELDA_H_

#include "Celula.h"

enum Comportamiento {
  Inerte,
  Zombie,
  Decay,
  Complementaria,
  Portal,
  Radioactiva
};

class Celda {
  private:
    Celula * celula;
    Celula * celulaFutura;
    Celda * celdaAuxiliar;
    Comportamiento comportamiento;
    unsigned int plano;
    unsigned int fila;
    unsigned int columna;

  
  public:
    Celda(unsigned int plano, unsigned int fila, unsigned int columna);
    ~Celda();
    EstadoCelula getEstadoCelula(bool futura);
    Comportamiento getComportamiento();
    void revivirCelula(bool futura);
    void matarCelula(bool futura);
    unsigned int getPlano();
    unsigned int getFila();
    unsigned int getColumna();
    bool estaVacia();
    bool celulaViva();
    bool celulaMuerta();
    unsigned int getCargaGenetica(bool futura, unsigned int posicion);
    void setCargaGenetica(bool futura, unsigned int posicion, unsigned int cargaGenetica);
    unsigned int getCantidadGenes();
    void syncActualyFutura();

    void setZombie();
    void setDecay();
    void setComplemento(Celda * celdaComplementaria);
    void setPortal(Celda * celdaOrigen);
    void setRadioactiva();

    EstadoCelula getEstadoCelulaAuxiliar(bool futura);
    unsigned int getCargaGeneticaAuxiliar(bool futura, unsigned int posicion);
    unsigned int getCargaMaximaGenetica(bool futura);

    bool esZombie();
    bool esDecay();
    bool esComplementaria();
    bool esPortal();
    bool esRadioactiva();
};

/*
  pre: -
  pos: crea una celula con la carga genetica en 0, muerta e inerte
*/
Celda::Celda(unsigned int plano, unsigned int fila, unsigned int columna){
  this->celula = new Celula();
  this->celulaFutura = new Celula();
  this->celdaAuxiliar = NULL;
  this->comportamiento = Inerte;
  this->plano = plano;
  this->fila = fila;
  this->columna = columna;
}

/*
  pre: -
  pos: destruye el objeto liberando la memoria solicitada y los apunta a NULL
*/
Celda::~Celda(){
  delete this->celula;
  delete this->celulaFutura;
  delete this->celdaAuxiliar;

  this->celula = NULL;
  this->celulaFutura = NULL;
  this->celdaAuxiliar = NULL;
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
  pos: devuelve el comportamiento de la celda
*/
Comportamiento Celda::getComportamiento(){
  return this->comportamiento;
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

unsigned int Celda::getPlano(){
  return this->plano;
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

/*
  pre: -
  pos: cambia el comportamiento a Zombie
*/
void Celda::setZombie(){
  this->comportamiento = Zombie;
}

/*
  pre: -
  pos: cambia el comportamiento a Decay
*/
void Celda::setDecay(){
  this->comportamiento = Decay;
}

/*
  pre: -
  pos: cambia el comportamiento a Complementaria y apunta la celula complementaria
*/
void Celda::setComplemento(Celda * celdaComplementaria){
  this->comportamiento = Complementaria;
  this->celdaAuxiliar = celdaComplementaria;
}

/*
  pre: -
  pos: cambia el comportamiento a Portal y apunta a la celda origen del portal
*/
void Celda::setPortal(Celda * celdaOrigen){
  this->comportamiento = Portal;
  this->celdaAuxiliar = celdaOrigen;
}

/*
  pre: -
  pos: cambia el comportamiento a Radioactiva
*/
void Celda::setRadioactiva(){
  this->comportamiento = Radioactiva;
}

/*
  pre: -
  pos: retorna el estado de la celula dentro de la celda auxiliar
*/
EstadoCelula Celda::getEstadoCelulaAuxiliar(bool futura){
    return this->celdaAuxiliar->getEstadoCelula(futura);
}

/*
  pre: posicion tiene que ser mayor a 0 y menor a la cantidad de genes que tenga la celula
  pos: devuelve la carga genetica de la posicion solicitada
*/
unsigned int Celda::getCargaGeneticaAuxiliar(bool futura, unsigned int posicion){
  if( posicion <= 0 || posicion > this->celula->getCantidadGenes())
    throw "Posicion invalida";

  return this->celdaAuxiliar->getCargaGenetica(futura, posicion);
}

/*
  pre:-
  pos: retorna la carga genetica maxima del primer gen que encuentre
*/
unsigned int Celda::getCargaMaximaGenetica(bool futura){
  if(futura){
    return this->celulaFutura->getCargaMaximaGenetica();
  }
  else{
    return this->celula->getCargaMaximaGenetica();
  }
}

/*
  pre: -
  pos: retorna true si la celda elegida es Zombie
*/
bool Celda::esZombie(){
  return this->getComportamiento() == Zombie;
}

/*
  pre: -
  pos: retorna true si la celda elegida es Decay
*/
bool Celda::esDecay(){
  return this->getComportamiento() == Decay;
}

/*
  pre: -
  pos: retorna true si la celda elegida es Complementaria
*/
bool Celda::esComplementaria(){
  return this->getComportamiento() == Complementaria;
}

/*
  pre: -
  pos: retorna true si la celda elegida es Portal
*/
bool Celda::esPortal(){
  return this->getComportamiento() == Portal;
}

/*
  pre: -
  pos: retorna true si la celda elegida es Radioactiva
*/
bool Celda::esRadioactiva(){
  return this->getComportamiento() == Radioactiva;
}

#endif // CELDA_H_