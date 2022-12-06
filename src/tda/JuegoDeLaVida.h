#ifndef JUEGO_DE_LA_VIDA_H_
#define JUEGO_DE_LA_VIDA_H_

#include <iostream>

#include "Tablero.h"
#include "../tda/AdminDeCeldas.h"
#include "BmpHandle.h"

class JuegoDeLaVida{
  private:
    Tablero * tablero;
    AdminDeCeldas * adminDeCeldas;
    unsigned int cantidadVivas;
    unsigned int cantidadNacimientosTurno;
    unsigned int cantidadFallecimientosTurno;
    unsigned int cantidadNacimientosTotales;
    unsigned int cantidadFallecimientosTotales;
    unsigned int cantidadTurnos;

  public:
    JuegoDeLaVida(int planos, int filas, int columnas);
    ~JuegoDeLaVida();
    unsigned int getCantidadVivas();
    unsigned int getCantidadNacimientosTurno();
    unsigned int getCantidadFallecimientosTurno();
    unsigned int getCantidadNacimientosTotales();
    unsigned int getCantidadFallecimientosTotales();
    unsigned int getCantidadTurnos();

    void iniciarTableroConTemplate1();
    void iniciarTableroConTemplate2();
    void iniciarTableroConTemplate3();
    void ingresoManualViva(unsigned int plano, unsigned int fila, unsigned int columna);

    void pasarTurno();
    void imprimirTablero();

    void resetNacimientosTurno();
    void resetStatsTurno();
    void imprimirStats();

    bool estaCongelado();

    void imprimirImagenDelTablero();

    bool estaVacio();
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
  this->cantidadFallecimientosTurno = 0;
  this->cantidadNacimientosTotales = 0;
  this->cantidadFallecimientosTotales = 0;
  this->cantidadTurnos = 0;
}

/*
  pre: -
  pos: libera la memoria solicitada y destruye el objeto
*/
JuegoDeLaVida::~JuegoDeLaVida(){
  delete this->tablero;
  delete this->adminDeCeldas;
  this->tablero = NULL;
  this->adminDeCeldas = NULL;
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
  pos: retorna la cantidad de Fallecimientos en el turno
*/
unsigned int JuegoDeLaVida::getCantidadFallecimientosTurno(){
  return this->cantidadFallecimientosTurno;
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
  pos: retorna la cantidad de Fallecimientos totales
*/
unsigned int JuegoDeLaVida::getCantidadFallecimientosTotales(){
  return this->cantidadFallecimientosTotales;
}

/*
  pre: -
  pos: retorna la cantidad de turnos
*/
unsigned int JuegoDeLaVida::getCantidadTurnos(){
  return this->cantidadTurnos;
}

/*
  pre: -
  pos: inicializa el juego con valores predeterminados
*/
void JuegoDeLaVida::iniciarTableroConTemplate1(){
  this->tablero->getCelda(1, 1, 2)->revivirCelula(false);
  this->tablero->getCelda(1, 3, 1)->revivirCelula(false);
  this->tablero->getCelda(2, 1, 2)->revivirCelula(false);
  this->tablero->getCelda(4, 1, 2)->revivirCelula(false);
  this->tablero->getCelda(2, 2, 2)->matarCelula(false);
  this->tablero->getCelda(3, 3, 3)->revivirCelula(false);

  this->tablero->getCelda(1, 1, 1)->revivirCelula(false);
  this->tablero->getCelda(2, 1, 1)->setRadioactiva();

  this->tablero->syncTablero(this->adminDeCeldas, true);

  this->cantidadVivas = 6;
}

/*
  pre: -
  pos: inicializa el juego con valores predeterminados
*/
void JuegoDeLaVida::iniciarTableroConTemplate2(){
  this->tablero->getCelda(1, 1, 2)->revivirCelula(false);
  this->tablero->getCelda(1, 3, 1)->revivirCelula(false);
  this->tablero->getCelda(2, 1, 2)->revivirCelula(false);
  this->tablero->getCelda(4, 1, 2)->revivirCelula(false);
  this->tablero->getCelda(2, 2, 2)->matarCelula(false);
  this->tablero->getCelda(3, 3, 3)->revivirCelula(false);

  this->tablero->getCelda(1, 1, 1)->revivirCelula(false);
  this->tablero->getCelda(2, 1, 1)->setRadioactiva();
  this->tablero->getCelda(1, 1, 1)->setPortal(this->tablero->getCelda(2, 2, 2));

  this->tablero->syncTablero(this->adminDeCeldas, true);

  this->cantidadVivas = 6;
}

/*
  pre: -
  pos: inicializa el juego con valores predeterminados
*/
void JuegoDeLaVida::iniciarTableroConTemplate3(){
  this->tablero->getCelda(1, 1, 2)->revivirCelula(false);
  this->tablero->getCelda(1, 3, 1)->revivirCelula(false);
  this->tablero->getCelda(2, 1, 2)->revivirCelula(false);
  this->tablero->getCelda(4, 1, 2)->revivirCelula(false);
  this->tablero->getCelda(2, 2, 2)->matarCelula(false);
  this->tablero->getCelda(3, 3, 3)->revivirCelula(false);

  this->tablero->getCelda(1,1,1)->setZombie();

  this->tablero->syncTablero(this->adminDeCeldas, true);

  this->cantidadVivas = 6;
}

/*
  pre: los parametros deben estar dentro del rango del tablero
  pos: revive la celula en la ubicacion solicitada

*/
void JuegoDeLaVida::ingresoManualViva(unsigned int plano, unsigned int fila, unsigned int columna){
  this->tablero->getCelda(plano, fila, columna)->revivirCelula(false);
  this->cantidadVivas += 1;
}

/*
  pre: -
  pos: evoluciona el juego en un turno. Esto implica que actualiza sus argumentos
*/
void JuegoDeLaVida::pasarTurno(){  

  this->resetStatsTurno();

  this->tablero->actualizarTablero(this->adminDeCeldas, this->cantidadNacimientosTurno, this->cantidadFallecimientosTurno);
  this->tablero->syncTablero(this->adminDeCeldas, false);

  this->cantidadVivas += this->cantidadNacimientosTurno - this->cantidadFallecimientosTurno;
  this->cantidadNacimientosTotales += this->cantidadNacimientosTurno;
  this->cantidadFallecimientosTotales += this->cantidadFallecimientosTurno;
  
  this->cantidadTurnos++;

}

/*
  pre: -
  pos: imprime el tablero entero
*/
void JuegoDeLaVida::imprimirTablero(){
  this->tablero->imprimirTablero();
}

/*
  pre: -
  pos: pone a cantidadNacimientosTurno en 0
*/
void JuegoDeLaVida::resetNacimientosTurno(){
  this->cantidadNacimientosTurno = 0;
}

/*
  pre: -
  pos: pone a los contadores por turno en cero
*/
void JuegoDeLaVida::resetStatsTurno(){
  this->cantidadNacimientosTurno = 0;
  this->cantidadFallecimientosTurno = 0;
}

/*
  pre: -
  pos: imprime las estadisticas
*/
void JuegoDeLaVida::imprimirStats(){
  char congelado = this->estaCongelado() == 1 ? 'S' : 'N';
  cout << "Celulas vivas: " << this->getCantidadVivas() << endl;
  cout << "Nacimientos turno: " << this->getCantidadNacimientosTurno() << endl;
  cout << "Fallecimientos turno: " << this->getCantidadFallecimientosTurno() << endl;
  cout << "Nacimientos TOTALES: " << this->getCantidadNacimientosTotales() << endl;
  cout << "Fallecimientos TOTALES: " << this->getCantidadFallecimientosTotales() << endl;
  cout << "Juego congelado: " << congelado << endl;
}

/*
  pre: -
  pos: retorna true si el juego no ha sufrido ni nacimientos ni fallecimientos en el ultimo turno
*/
bool JuegoDeLaVida::estaCongelado(){
  return this->cantidadNacimientosTurno == 0 && this->cantidadFallecimientosTurno == 0 && this->cantidadTurnos != 0;
}

/*
  pre: -
  pos: imprime una imagen de cada nivel del tablero
*/
void JuegoDeLaVida::imprimirImagenDelTablero(){
  this->tablero->imprimirImagenDelTablero();
}

/*
  pre: -
  pos: retorna true si esta vacio
*/
bool JuegoDeLaVida::estaVacio(){
  return this == NULL;
}


#endif // JUEGO_DE_LA_VIDA_H_