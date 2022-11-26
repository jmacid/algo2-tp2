#ifndef JUEGO_DE_LA_VIDA_H_
#define JUEGO_DE_LA_VIDA_H_

#include "Tablero.h"
#include "../tda/AdminDeCeldas.h"

class JuegoDeLaVida{
  private:
    Tablero * tablero;
    AdminDeCeldas * adminDeCeldas;
    unsigned int cantidadVivas;
    unsigned int cantidadNacimientosTurno;
    unsigned int cantidadDefuncionesTurno;
    unsigned int cantidadNacimientosTotales;
    unsigned int cantidadDefuncionesTotales;
    unsigned int cantidadTurnos;

  public:
    JuegoDeLaVida(int planos, int filas, int columnas);
    ~JuegoDeLaVida();
    unsigned int getCantidadVivas();
    unsigned int getCantidadNacimientosTurno();
    unsigned int getCantidadDefuncionesTurno();
    unsigned int getCantidadNacimientosTotales();
    unsigned int getCantidadDefuncionesTotales();
    unsigned int getCantidadTurnos();

    void iniciarTableroConTemplate();
    void pasarTurno();
    void imprimirTablero();
};


/*
  pre: -
  pos: inicializa las variable en cero y el tablero con 3 filas, 5 columnas y 3 planos
*/
JuegoDeLaVida::JuegoDeLaVida(int planos = 4, int filas = 3, int columnas = 5){
  this->tablero = new Tablero(planos, filas, columnas);
  this->adminDeCeldas = new AdminDeCeldas();
  this->cantidadVivas = 0;
  this->cantidadNacimientosTurno = 0;
  this->cantidadDefuncionesTurno = 0;
  this->cantidadNacimientosTotales = 0;
  this->cantidadDefuncionesTotales = 0;
  this->cantidadTurnos = 0;
}

/*
  pre: -
  pos: libera la memoria solicitada y destruye el objeto
*/
JuegoDeLaVida::~JuegoDeLaVida(){
  delete this->tablero;
  delete this->adminDeCeldas;
}


/*
  pre: -
  pos: retorna la cantidad de celdas vivas
*/
unsigned int JuegoDeLaVida::getCantidadVivas(){
  return this->cantidadVivas;
}
/*
  pre: -
  pos: retorna la cantidad de nacimientos en el turno
*/
unsigned int JuegoDeLaVida::getCantidadNacimientosTurno(){
  return this->cantidadNacimientosTurno;
}
/*
  pre: -
  pos: retorna la cantidad de defunciones en el turno
*/
unsigned int JuegoDeLaVida::getCantidadDefuncionesTurno(){
  return this->cantidadDefuncionesTotales;
}
/*
  pre: -
  pos: retorna la cantidad de de nacimientos totales
*/
unsigned int JuegoDeLaVida::getCantidadNacimientosTotales(){
  return this->cantidadNacimientosTotales;
}
/*
  pre: -
  pos: retorna la cantidad de defunciones totales
*/
unsigned int JuegoDeLaVida::getCantidadDefuncionesTotales(){
  return this->cantidadDefuncionesTotales;
}
/*
  pre: -
  pos: retorna la cantidad de turnos
*/
unsigned int JuegoDeLaVida::getCantidadTurnos(){
  return this->cantidadTurnos;
}


void JuegoDeLaVida::iniciarTableroConTemplate(){
  this->tablero->getCelda(1, 1, 2)->revivirCelula(false);
  this->tablero->getCelda(1, 3, 1)->revivirCelula(false);
  this->tablero->getCelda(2, 1, 2)->revivirCelula(false);
  this->tablero->getCelda(4, 1, 2)->revivirCelula(false);
  this->tablero->getCelda(2, 2, 2)->matarCelula(false);
  this->tablero->getCelda(3, 3, 3)->revivirCelula(false);
}

/*
  pre: -
  pos: evoluciona el juego en un turno. Esto implica que actualiza sus argumentos
*/
void JuegoDeLaVida::pasarTurno(){  

  this->tablero->actualizarTablero(this->adminDeCeldas);
  this->tablero->syncTablero(this->adminDeCeldas);
  
  this->cantidadTurnos++;

}

/*
  pre: -
  pos: imprime el tablero entero
*/
void JuegoDeLaVida::imprimirTablero(){
  this->tablero->imprimirTablero();
}

#endif // JUEGO_DE_LA_VIDA_H_