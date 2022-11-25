#include <iostream>

using namespace std;

#include "../tda/AdminDeCeldas.h"
#include "../tda/Tablero.h"

int main (){
  try{
    int filas = 3, columnas = 5, niveles = 4;

    Tablero * tablero = new Tablero(niveles, filas, columnas);
    AdminDeCeldas * adminDeCeldas = new AdminDeCeldas();

    tablero->getCelda(1, 1, 1)->revivirCelula();
    tablero->getCelda(1, 1, 2)->revivirCelula();
    tablero->getCelda(1, 3, 1)->revivirCelula();
    tablero->getCelda(2, 1, 2)->revivirCelula();
    tablero->getCelda(4, 1, 2)->revivirCelula();
    tablero->getCelda(2, 2, 2)->matarCelula();
    // tablero->getCelda(1, 1, 2)->revivirCelula();

    cout << tablero->getCelda(1, 1, 1)->getEstadoCelula() << endl;
    cout << tablero->getCelda(4, 3, 2)->getEstadoCelula() << endl;
    cout << tablero->getCelda(1, 3, 1)->getEstadoCelula() << endl;
    cout << tablero->getCelda(2, 1, 2)->getEstadoCelula() << endl;
    cout << tablero->getCelda(4, 1, 2)->getEstadoCelula() << endl;
    cout << tablero->getCelda(2, 2, 2)->getEstadoCelula() << endl;

    cout << "Marcadas :" << endl;
    Celda * c112 = tablero->getCelda(1, 1, 2);
    cout << "!" << c112->getNivel() << ", " << c112->getFila() << ", " << c112->getColumna() << "!" << endl;
    cout << c112->getEstadoCelula() << endl;
    cout << tablero->getCelda(4, 3, 5)->getEstadoCelula() << endl;
    cout << tablero->getCelda(4, 3, 1)->getEstadoCelula() << endl;

    Lista<Celda *>* celdasVecinas = new Lista<Celda *>();
    tablero->getCeldasVecinas(celdasVecinas, 1, 1, 1);
    unsigned int vivas = adminDeCeldas->contarVivas(celdasVecinas);

    delete adminDeCeldas;
    delete tablero;
    delete celdasVecinas;

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


  cout << "Terminado" << endl;

  return 0;
}