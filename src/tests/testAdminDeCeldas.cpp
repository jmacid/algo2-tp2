#include <iostream>

using namespace std;

#include "../tda/AdminDeCeldas.h"
#include "../tda/Tablero.h"

int main (){
  try{
    int filas = 3, columnas = 5, niveles = 4;

    Tablero * tablero = new Tablero(niveles, filas, columnas);
    AdminDeCeldas * adminDeCeldas = new AdminDeCeldas();

    // tablero->getCelda(1, 1, 1)->revivirCelula(false);
    tablero->getCelda(1, 1, 2)->revivirCelula(false);
    tablero->getCelda(1, 3, 1)->revivirCelula(false);
    tablero->getCelda(2, 1, 2)->revivirCelula(false);
    tablero->getCelda(4, 1, 2)->revivirCelula(false);
    tablero->getCelda(2, 2, 2)->matarCelula(false);
    tablero->getCelda(3, 3, 3)->revivirCelula(false);

    cout << tablero->getCelda(1, 1, 1)->getEstadoCelula() << endl;
    cout << tablero->getCelda(4, 3, 2)->getEstadoCelula() << endl;
    cout << tablero->getCelda(1, 3, 1)->getEstadoCelula() << endl;
    cout << tablero->getCelda(2, 1, 2)->getEstadoCelula() << endl;
    cout << tablero->getCelda(4, 1, 2)->getEstadoCelula() << endl;
    cout << tablero->getCelda(2, 2, 2)->getEstadoCelula() << endl;

    // cout << "Marcadas :" << endl;
    // Celda * c112 = tablero->getCelda(1, 1, 2);
    // cout << "!" << c112->getNivel() << ", " << c112->getFila() << ", " << c112->getColumna() << "!" << endl;
    // cout << c112->getEstadoCelula() << endl;
    // cout << tablero->getCelda(4, 3, 5)->getEstadoCelula() << endl;


    
    Lista<Celda *>* celdasVecinas111 = new Lista<Celda *>();
    tablero->getCeldasVecinas(celdasVecinas111, 1, 1, 1);
    unsigned int vivas111 = adminDeCeldas->contarVivas(celdasVecinas111);

    Lista<Celda *>* celdasVecinas222 = new Lista<Celda *>();
    tablero->getCeldasVecinas(celdasVecinas222, 2, 2, 2);
    unsigned int vivas222 = adminDeCeldas->contarVivas(celdasVecinas222);

    Lista<Celda *>* celdasVecinas333 = new Lista<Celda *>();
    tablero->getCeldasVecinas(celdasVecinas333, 3, 3, 3);
    unsigned int vivas333 = adminDeCeldas->contarVivas(celdasVecinas333);

    adminDeCeldas->actualizarCelda(tablero->getCelda(1, 1, 1), celdasVecinas111);
    adminDeCeldas->actualizarCelda(tablero->getCelda(2, 2, 2), celdasVecinas222);
    adminDeCeldas->actualizarCelda(tablero->getCelda(3, 3, 3), celdasVecinas333);

    delete celdasVecinas111;
    delete celdasVecinas222;
    delete celdasVecinas333;
    delete adminDeCeldas;
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


  cout << "Terminado" << endl;

  return 0;
}