#ifndef ADMIN_DE_CELDAS_H_
#define ADMIN_DE_CELDAS_H_

#include <iostream>
using namespace std;

#include "Celda.h"
#include "Lista.h"
#include "Gen.h"
#include "Celula.h"

class AdminDeCeldas {
  private:
    unsigned int X1;
    unsigned int X2;
    unsigned int X3;

  public:
    AdminDeCeldas();
    AdminDeCeldas(unsigned int X1, unsigned int X2, unsigned int X3);
    ~AdminDeCeldas();
    unsigned int contarVivas(Lista<Celda *> * celdas);
    void actualizarCelda(Celda * celda, Lista<Celda *> * celdasVecinas);

    void heredarGenes(Celda * celda, bool futura, Lista<Celda *> * celdas);
    unsigned int actualizarGen(unsigned int posicion, Lista<Celda *> * celdas);
    unsigned int generadorPorMaximo(unsigned int posicion, Lista<Celda *> * celdas);
    unsigned int generadorPorMinimo(unsigned int posicion, Lista<Celda *> * celdas);
    unsigned int generadorPromedio(unsigned int posicion, Lista<Celda *> * celdas);

    void syncCelda(Celda *celda);
};

/*
  pre: -
  pos: Inicializa los atributos con valores default
*/
AdminDeCeldas::AdminDeCeldas(){
  this->X1 = 4;
  this->X2 = 6;
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
    if(celda->getEstadoCelula(false) == Viva){
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
  if(celda->estaVacia()){
    throw "La celda esta vacia";
  }

  unsigned int vivas = contarVivas(celdasVecinas);

  // Una célula muerta con exactamente X1 células vecinas vivas "nace"
  if(celda->celulaMuerta() && vivas == this->X1){
    celda->revivirCelula(true);
    this->heredarGenes(celda, true, celdasVecinas);
  }
  // Una célula viva con X2 a X3 células vecinas vivas sigue viva, en otro caso muere o permanece muerta
  else if(celda->celulaViva() && (vivas < this->X2 || vivas > this->X3)){
    celda->matarCelula(true);
    this->heredarGenes(celda, true, celdasVecinas);
  }

  return;
}

/*
  pre: la lista de celdas no puede estar vacia y la celula tampoco
  pos: actualiza los genes de la celula
*/
void AdminDeCeldas::heredarGenes(Celda * celda, bool futura, Lista<Celda *> * celdas){

  if(celdas->estaVacia())
    throw "La lista de celdas no puede estar vacia";
  if(celda->estaVacia())
    throw "La celda no puede estar vacia";

  for(int i = 0; i < celda->getCantidadGenes(); i++){
    unsigned int nuevaCargaGenetica = this->actualizarGen(i + 1, celdas);
    cout << "Antes: " << celda->getCargaGenetica(true, i+1) << endl;
    celda->setCargaGenetica(futura, i+1, nuevaCargaGenetica);
    cout << "Despues: " << celda->getCargaGenetica(true, i + 1) << endl;
  }
}

/*
  pre: las celdas no pueden estar vacias
  pos: genera la carga genetica en base a 3 funciones seleccionadas de forma aleatoria
*/
unsigned int AdminDeCeldas::actualizarGen(unsigned int posicion, Lista<Celda *> * celdas){
  if(celdas->estaVacia())
    throw "La lista de celdas no puede estar vacia";

  srand(time(0));
  float randNumber = (float)rand()/RAND_MAX;

  if(randNumber < 0.33){
    return this->generadorPorMaximo(posicion, celdas);
  }
  else if(randNumber < 0.66){
    return this->generadorPorMinimo(posicion, celdas);
  }
  else{
    return this->generadorPromedio(posicion, celdas);
  }
}

/*
  pre: celdas no puede estar vacio. posicion debe ser mayor que cero o menor que la cantidad de genes.
  pos: devulve el gen cuyo valor es maximo segun la posicion.
*/
unsigned int AdminDeCeldas::generadorPorMaximo(unsigned int posicion, Lista<Celda *> * celdas){
  if(celdas->estaVacia())
    throw "La lista de celdas no puede estar vacia";

  unsigned int maximoGen = 0;
  celdas->iniciarCursor();
  while(celdas->avanzarCursor()){
    Celda * celda = celdas->obtenerCursor();
    unsigned int valorGen = celda->getCargaGenetica(false, posicion);
    if(maximoGen < valorGen){
      maximoGen = valorGen;
    }
  }

  return maximoGen;
}

/*
  pre: celdas no puede estar vacio. posicion debe ser mayor que cero o menor que la cantidad de genes.
  pos: devulve el gen cuyo valor es minimo segun la posicion.
*/
unsigned int AdminDeCeldas::generadorPorMinimo(unsigned int posicion, Lista<Celda *> * celdas){
  if(celdas->estaVacia())
    throw "La lista de celdas no puede estar vacia";

  unsigned int minimoGen = -1;  // Valor maximo posible para este tipo de dato
  celdas->iniciarCursor();
  while(celdas->avanzarCursor()){
    Celda * celda = celdas->obtenerCursor();
    unsigned int valorGen = celda->getCargaGenetica(false, posicion);
    if(minimoGen > valorGen){
      minimoGen = valorGen;
    }
  }

  return minimoGen;
}


unsigned int AdminDeCeldas::generadorPromedio(unsigned int posicion, Lista<Celda *> * celdas){
  if(celdas->estaVacia())
    throw "La lista de celdas no puede estar vacia";

  unsigned int suma = 0;
  unsigned int cantidad = 0;

  celdas->iniciarCursor();
  while(celdas->avanzarCursor()){
    Celda * celda = celdas->obtenerCursor();
    suma += celda->getCargaGenetica(false, posicion);
    cantidad++;
  }

  return suma/cantidad;
}

/*
  pre: la celda no tiene que estar vacia
  pos: copia los valores de la celda futura en la celda actual
*/
void AdminDeCeldas::syncCelda(Celda *celda){
  if(celda->estaVacia())
    throw "La celda esta vacia";

  if( celda->getEstadoCelula(true) == Viva){
    celda->revivirCelula(false);
  }
  else{
    celda->matarCelula(false);
  }

  for(int i = 0; i < celda->getCantidadGenes(); i ++){
    unsigned int cargaGeneticaFutura = celda->getCargaGenetica(true, i + 1);
    celda->setCargaGenetica(false, i + 1, cargaGeneticaFutura);
  }

}

#endif //ADMIN_DE_CELDAS_H_