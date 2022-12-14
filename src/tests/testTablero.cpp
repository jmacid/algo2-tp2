#include <iostream>

using namespace std;

// #include "../tda/Lista.h"
#include "../tda/Tablero.h"
#include "../tda/Celda.h"

int main (){
  try{

    int filas = 3, columnas = 5, planos = 4;

    Tablero * tablero = new Tablero(planos, filas, columnas);

    tablero->getCelda(1, 1, 1)->revivirCelula(false);

    cout << tablero->getCelda(1, 1, 1)->getEstadoCelula(false) << endl;
    cout << tablero->getCelda(2, 2, 2)->getEstadoCelula(false) << endl;

    Lista<Celda *>* celdasVecinas = new Lista<Celda *>();
    tablero->getCeldasVecinas(celdasVecinas, 1, 1, 1);

    // Test circulares
    int nivelCircular = tablero->calcularNivelCircular(1,-1);
    int columanCircular = tablero->calcularColumnaCircular(5,0);
    int filaCircular = tablero->calcularFilaCircular(3,1);
    int nivelCircular2 = tablero->calcularNivelCircular(4,1);
    int columanCircular2 = tablero->calcularColumnaCircular(5,1);
    int filaCircular2 = tablero->calcularFilaCircular(1,-1);

    delete celdasVecinas;
    delete tablero;
  }
  catch(char const* excp){
    cout << "Excepcion: " << excp << endl;
  }
  catch(string message){
    cout << "Excepcion: " << message << endl;
  }
  catch(...){
    cout << "Excepcion desconocida" << endl;
  }




  cout << "El juego ha terminado" << endl;

  return 0;
}