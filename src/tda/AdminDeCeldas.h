#ifndef ADMIN_DE_CELDAS_H_
#define ADMIN_DE_CELDAS_H_

#include <iostream>
using namespace std;

#include "Celda.h"
#include "Lista.h"

class AdminDeCeldas {
  private:
    unsigned int X1;
    unsigned int X2;
    unsigned int X3;

  public:
    AdminDeCeldas();
    AdminDeCeldas(unsigned int X1, unsigned int X2, unsigned int X3);
    ~AdminDeCeldas();
    void actualizarCelda(Celda * celda, Lista<Celda *> * celdasVecinas);
    unsigned int contarVivas(Lista<Celda *> * celdas);
};

/*
  pre: -
  pos: Inicializa los atributos con valores default
*/
AdminDeCeldas::AdminDeCeldas(){
  this->X1 = 10;
  this->X2 = 5;
  this->X3 = 15;
}


/*
  pre: X1, X2, y X3 deben ser menores o iguales que 26. Ademas X2 debe ser menor que X3
  pos: Inicializa los atributos con los valores de los parametros
*/
AdminDeCeldas::AdminDeCeldas(unsigned int X1, unsigned int X2, unsigned int X3){
  if( X1 > 26 || X2 > 26 ||X3 > 26)
    throw "X1, X2 y X3 deben ser menores que 26";
  if( X2 > X3 )
    throw "X2 debe ser menor que X3";
  
  this->X1 = X1;
  this->X2 = X2;
  this->X3 = X3;
}

/*
  pre: -
  pos: destruye el objeto
*/
AdminDeCeldas::~AdminDeCeldas(){}

/*
  pre: la lista no debe estar vacia
  pos: retorna la cantidad de celdas cuyas celulas estan vivas
*/
unsigned int AdminDeCeldas::contarVivas(Lista<Celda *> * celdas){
  if(celdas->estaVacia())
    throw "La lista de celdas esta vacia";
  
  unsigned int celdasVivas = 0;
  celdas->iniciarCursor();
  while(celdas->avanzarCursor()){
    Celda * celda = celdas->obtenerCursor();
    if(celda->getEstadoCelula() == Marcada){
      cout << "#" << celda->getNivel() << ", " << celda->getFila() << ", " << celda->getColumna() << "#" << endl;
      celdasVivas++;
    }
  }

  return celdasVivas;
}

/*
  pre:
  pos:
*/
void AdminDeCeldas::actualizarCelda(Celda * celda, Lista<Celda *> * celdasVecinas){
  
}


#endif //ADMIN_DE_CELDAS_H_