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
  this->X1 = 4;
  this->X2 = 4;
  this->X3 = 10;
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
    if(celda->getEstadoCelula() == Viva){
      // cout << "#" << celda->getNivel() << ", " << celda->getFila() << ", " << celda->getColumna() << "#" << endl;
      celdasVivas++;
    }
  }

  return celdasVivas;
}

/*
  pre: la lista de celdas vecinas no puede estar vacia y tampoco la celda
  pos: actualiza la celula futura de la celda y sus genes
*/
void AdminDeCeldas::actualizarCelda(Celda * celda, Lista<Celda *> * celdasVecinas){
  unsigned int vivas = contarVivas(celdasVecinas);

  if(celda->estaVacia()){
    throw "La celda esta vacia";
  }

  // Una célula muerta con exactamente X1 células vecinas vivas "nace"
  if(celda->celulaMuerta() && vivas == this->X1){
    celda->revivirCelula(true);
    // calcular genes
  }
  // Una célula viva con X2 a X3 células vecinas vivas sigue viva, en otro caso muere o permanece muerta
  else if(celda->celulaViva() && (vivas < this->X2 || vivas > this->X3)){
    celda->matarCelula(true);
    // calcular genes
  }

  return;
}

#endif //ADMIN_DE_CELDAS_H_