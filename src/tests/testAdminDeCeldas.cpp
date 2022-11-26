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

    cout << tablero->getCelda(1, 1, 1)->getEstadoCelula(false) << endl;
    cout << tablero->getCelda(4, 3, 2)->getEstadoCelula(false) << endl;
    cout << tablero->getCelda(1, 3, 1)->getEstadoCelula(false) << endl;
    cout << tablero->getCelda(2, 1, 2)->getEstadoCelula(false) << endl;
    cout << tablero->getCelda(4, 1, 2)->getEstadoCelula(false) << endl;
    cout << tablero->getCelda(2, 2, 2)->getEstadoCelula(false) << endl;

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

    cout << tablero->getCelda(1, 1, 1)->getCargaGenetica(false, 1) << endl;
    cout << tablero->getCelda(2, 2, 2)->getCargaGenetica(false, 1) << endl;
    cout << tablero->getCelda(3, 3, 3)->getCargaGenetica(false, 1) << endl;
    // sync
    adminDeCeldas->syncCelda(tablero->getCelda(1, 1, 1));
    adminDeCeldas->syncCelda(tablero->getCelda(2, 2, 2));
    adminDeCeldas->syncCelda(tablero->getCelda(3, 3, 3));

    cout << tablero->getCelda(1, 1, 1)->getCargaGenetica(false, 1) << endl;
    cout << tablero->getCelda(2, 2, 2)->getCargaGenetica(false, 1) << endl;
    cout << tablero->getCelda(3, 3, 3)->getCargaGenetica(false, 1) << endl;

    // Otra pasada solo en 1 1 1
    Lista<Celda *>* celdasVecinas1112 = new Lista<Celda *>();
    tablero->getCeldasVecinas(celdasVecinas1112, 1, 1, 1);
    unsigned int vivas1112 = adminDeCeldas->contarVivas(celdasVecinas1112);
    adminDeCeldas->actualizarCelda(tablero->getCelda(1, 1, 1), celdasVecinas111);
     cout << tablero->getCelda(1, 1, 1)->getCargaGenetica(false, 1) << endl;
    adminDeCeldas->syncCelda(tablero->getCelda(1, 1, 1));
    cout << tablero->getCelda(1, 1, 1)->getCargaGenetica(false, 1) << endl;


    delete celdasVecinas111;
    delete celdasVecinas222;
    delete celdasVecinas333;
    delete celdasVecinas1112;
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