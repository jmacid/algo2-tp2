#include <iostream>

using namespace std;

#include "../tda/Tablero.h"

int main (){

  int filas = 3, columnas = 5, niveles = 4;

  Tablero * tablero = new Tablero(columnas, filas, niveles);
  
  tablero->getCelda(1, 1, 1)->revivirCelula();

  cout << tablero->getCelda(1, 1, 1)->getEstadoCelula() << endl;
  cout << tablero->getCelda(2, 2, 2)->getEstadoCelula() << endl;

  delete tablero;

  cout << "El juego ha terminado" << endl;

  return 0;
}