#include <iostream>

using namespace std;

// #include "../tda/Lista.h"
#include "../tda/Tablero.h"
#include "../tda/Celda.h"

int main (){
  try{

    int filas = 3, columnas = 5, niveles = 4;

    Tablero * tablero = new Tablero(niveles, filas, columnas);

    tablero->getCelda(1, 1, 1)->revivirCelula();

    cout << tablero->getCelda(1, 1, 1)->getEstadoCelula() << endl;
    cout << tablero->getCelda(2, 2, 2)->getEstadoCelula() << endl;

    // Lista<Celda *>* celdasVecinas = new Lista<Celda *>();
    tablero->getCeldasVecinas(1, 1, 1);

    // Test circulares
    int nivelCircular = tablero->calcularNivelCircular(1,-1);
    int columanCircular = tablero->calcularColumnaCircular(5,0);
    int filaCircular = tablero->calcularFilaCircular(3,1);
    int nivelCircular2 = tablero->calcularNivelCircular(4,1);
    int columanCircular2 = tablero->calcularColumnaCircular(5,1);
    int filaCircular2 = tablero->calcularFilaCircular(1,-1);

    // delete celdasVecinas;
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