#ifndef ADMIN_DE_CELDAS_H_
#define ADMIN_DE_CELDAS_H_

#include <iostream>
using namespace std;

#include "Celda.h"
#include "Lista.h"
#include "Celula.h"

class AdminDeCeldas {
  private:
    unsigned int X1;
    unsigned int X2;
    unsigned int X3;

    void complementarCelda(Celda* celda, unsigned int& nacimientos, unsigned int& fallecimientos);
    void copiarCelda(Celda* celda, unsigned int& nacimientos, unsigned int& fallecimientos);

  public:
    AdminDeCeldas();
    AdminDeCeldas(unsigned int X1, unsigned int X2, unsigned int X3);
    ~AdminDeCeldas();
    bool estaVacio();
    unsigned int contarVivas(Lista<Celda *> * celdas);
    void actualizarCelda(Celda * celda, Lista<Celda *> * celdasVecinas, unsigned int& nacimientos, unsigned int& fallecimientos);

    void heredarGenes(Celda * celda, bool futura, Lista<Celda *> * celdas);
    unsigned int actualizarGen(unsigned int posicion, Lista<Celda *> * celdas);
    unsigned int generadorPorMaximo(unsigned int posicion, Lista<Celda *> * celdas);
    unsigned int generadorPorMinimo(unsigned int posicion, Lista<Celda *> * celdas);
    unsigned int generadorPromedio(unsigned int posicion, Lista<Celda *> * celdas);

    void syncCelda(Celda *celda, bool destinoFutura);
};

/*
  pre: -
  pos: Inicializa los atributos con valores default
*/
AdminDeCeldas::AdminDeCeldas(){
  this->X1 = 4;
  this->X2 = 3;
  this->X3 = 9;
}


/*
  pre: X1, X2, y X3 deben ser menores o iguales que 26. Ademas X2 debe ser menor que X3
  pos: Inicializa los atributos con los valores de los parametros
*/
AdminDeCeldas::AdminDeCeldas(unsigned int X1, unsigned int X2, unsigned int X3){
  if( X1 > 26 || X2 > 26 ||X3 > 26){
    throw "X1, X2 y X3 deben ser menores que 26";
  }
  if( X2 > X3 ){
    throw "X2 debe ser menor que X3";
  }
  
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
  pre: -
  pos: retorna true si esta vacio
*/
bool AdminDeCeldas::estaVacio(){
  return this == NULL;
}

/*
  pre: la lista no debe estar vacia
  pos: retorna la cantidad de celdas cuyas celulas estan vivas
*/
unsigned int AdminDeCeldas::contarVivas(Lista<Celda *> * celdas){
  if(celdas->estaVacia()){
    throw "La lista de celdas esta vacia";
  }

  unsigned int celdasVivas = 0;
  celdas->iniciarCursor();
  while(celdas->avanzarCursor()){
    Celda * celda = celdas->obtenerCursor();
    if(celda->getEstadoCelula(false) == Viva){
      // cout << "#" << celda->getPlano() << ", " << celda->getFila() << ", " << celda->getColumna() << "#" << endl;
      celdasVivas++;
    }
  }

  return celdasVivas;
}

/*
  pre: la lista de celdas vecinas no puede estar vacia y tampoco la celda
  pos: actualiza la celula futura de la celda y sus genes
*/
void AdminDeCeldas::actualizarCelda(Celda * celda, Lista<Celda *> * celdasVecinas, unsigned int& nacimientos, unsigned int& fallecimientos){
  if(celda->estaVacia()){
    throw "La celda esta vacia";
  }

  unsigned int vivas = contarVivas(celdasVecinas);

  // La celda Zombie no muere y sus genes son 0
  if(celda->esZombie()){
    celda->revivirCelula(true);
    for(int i = 0; i < celda->getCantidadGenes(); i++){
      celda->setCargaGenetica(true, i + 1, 0);
    }
  }
  else if(celda->esComplementaria()){
    complementarCelda(celda, nacimientos, fallecimientos);
  }
  else if(celda->esPortal()){
    copiarCelda(celda, nacimientos, fallecimientos);
  }
  // Una célula muerta con exactamente X1 células vecinas vivas "nace"
  else if(celda->celulaMuerta() && vivas == this->X1){
    celda->revivirCelula(true);
    // cout << "v(" << celda->getPlano() << ", " << celda->getFila() << ", " << celda->getColumna() << ")" << endl;
    nacimientos++;
    this->heredarGenes(celda, true, celdasVecinas);
  }
  // Una célula viva con X2 a X3 células vecinas vivas sigue viva, en otro caso muere o permanece muerta
  else if(celda->celulaViva() && (vivas < this->X2 || vivas > this->X3)){
    celda->matarCelula(true);
    // cout << "m(" << celda->getPlano() << ", " << celda->getFila() << ", " << celda->getColumna() << ")" << endl;
    fallecimientos++;
    // this->heredarGenes(celda, true, celdasVecinas);
  }
  else if (celda->celulaViva() && celda->getComportamiento() == Decay){
    for(int i = 0; i < celda->getCantidadGenes(); i++){
      celda->setCargaGenetica(true, i + 1, 300);
    }
  }

  return;
}

/*
  pre: la lista de celdas no puede estar vacia y la celula tampoco
  pos: actualiza los genes de la celula
*/
void AdminDeCeldas::heredarGenes(Celda * celda, bool futura, Lista<Celda *> * celdas){

  if(celdas->estaVacia()){
    throw "La lista de celdas no puede estar vacia";
  }
  if(celda->estaVacia()){
    throw "La celda no puede estar vacia";
  }

  for(int i = 0; i < celda->getCantidadGenes(); i++){
    unsigned int nuevaCargaGenetica = this->actualizarGen(i + 1, celdas);
    // cout << "Antes: " << celda->getCargaGenetica(true, i+1) << endl;
    celda->setCargaGenetica(futura, i+1, nuevaCargaGenetica);
    // cout << "Despues: " << celda->getCargaGenetica(true, i + 1) << endl;
  }
}

/*
  pre: las celdas no pueden estar vacias
  pos: genera la carga genetica en base a 3 funciones seleccionadas de forma aleatoria
*/
unsigned int AdminDeCeldas::actualizarGen(unsigned int posicion, Lista<Celda *> * celdas){
  if(celdas->estaVacia()){
    throw "La lista de celdas no puede estar vacia";
  }

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
  if(celdas->estaVacia()){
    throw "La lista de celdas no puede estar vacia";
  }

  unsigned int maximoGen = 0;
  celdas->iniciarCursor();
  while(celdas->avanzarCursor()){
    Celda * celda = celdas->obtenerCursor();
    unsigned int valorGen = celda->getCargaGenetica(false, posicion);
    if(celda->esRadioactiva()){
      valorGen *= 1.05; // Sus genes se transmiten un 5% mas fuertes
    }
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
  if(celdas->estaVacia()){
    throw "La lista de celdas no puede estar vacia";
  }

  unsigned int minimoGen = -1;  // Valor maximo posible para este tipo de dato
  celdas->iniciarCursor();
  while(celdas->avanzarCursor()){
    Celda * celda = celdas->obtenerCursor();
    unsigned int valorGen = celda->getCargaGenetica(false, posicion);
    if(celda->esRadioactiva()){
      valorGen *= 1.05; // Sus genes se transmiten un 5% mas fuertes
    }
    if(minimoGen > valorGen){
      minimoGen = valorGen;
    }
  }

  return minimoGen;
}


unsigned int AdminDeCeldas::generadorPromedio(unsigned int posicion, Lista<Celda *> * celdas){
  if(celdas->estaVacia()){
    throw "La lista de celdas no puede estar vacia";
  }

  unsigned int suma = 0;
  unsigned int cantidad = 0;

  celdas->iniciarCursor();
  while(celdas->avanzarCursor()){
    Celda * celda = celdas->obtenerCursor();
    unsigned int valorGen = celda->getCargaGenetica(false, posicion);
    if(celda->esRadioactiva()){
      valorGen *= 1.05; // Sus genes se transmiten un 5% mas fuertes
    }
    suma += valorGen;
    cantidad++;
  }

  return suma/cantidad;
}

/*
  pre: la celda no tiene que estar vacia
  pos: copia los valores de la celda futura en la celda actual o al reves
*/
void AdminDeCeldas::syncCelda(Celda *celda, bool destinoFutura){
  if(celda->estaVacia()){
    throw "La celda esta vacia";
  }

  if( celda->getEstadoCelula(!destinoFutura) == Viva){
    celda->revivirCelula(destinoFutura);
  }
  else{
    celda->matarCelula(destinoFutura);
  }

  for(int i = 0; i < celda->getCantidadGenes(); i ++){
    unsigned int cargaGenetica = celda->getCargaGenetica(!destinoFutura, i + 1);
    celda->setCargaGenetica(destinoFutura, i + 1, cargaGenetica);
  }
}

/*
  pre: -
  pos: complementa una celda. Si la auxiliar esta viva la mata, y sus genes sera los de la auxiliar menos cargaMaximaGenetica.
*/
void AdminDeCeldas::complementarCelda(Celda* celda, unsigned int& nacimientos, unsigned int& fallecimientos){
  if(celda->getEstadoCelulaAuxiliar(true) == Viva && celda->celulaViva()){
    celda->matarCelula(true);
    fallecimientos++;
  }
  else if (celda->getEstadoCelulaAuxiliar(true) == Muerta && celda->celulaMuerta()) {
    celda->revivirCelula(true);
    nacimientos++;
  }

  for(int i = 0; i < celda->getCantidadGenes(); i ++){
    unsigned int cargaMaximaGenetica = celda->getCargaMaximaGenetica(true);
    unsigned int cargaGeneticaComplementaria = cargaMaximaGenetica - celda->getCargaGeneticaAuxiliar(true, i + 1);
    celda->setCargaGenetica(true, i + 1, cargaGeneticaComplementaria);
  }
}

/*
  pre: -
  pos: copia una celda. Si la auxiliar esta viva la revive, y sus genes sera los de la auxiliar.
*/
void AdminDeCeldas::copiarCelda(Celda* celda, unsigned int& nacimientos, unsigned int& fallecimientos){
  if(celda->getEstadoCelulaAuxiliar(true) == Viva && celda->celulaMuerta()){
    celda->revivirCelula(true);
    nacimientos++;
  }
  else if (celda->getEstadoCelulaAuxiliar(true) == Muerta && celda->celulaViva()){
    celda->matarCelula(true);
    fallecimientos++;
  }

  for(int i = 0; i < celda->getCantidadGenes(); i ++){
    unsigned int cargaGeneticaComplementaria = celda->getCargaGeneticaAuxiliar(true, i + 1);
    celda->setCargaGenetica(true, i + 1, cargaGeneticaComplementaria);
  }
}
#endif //ADMIN_DE_CELDAS_H_