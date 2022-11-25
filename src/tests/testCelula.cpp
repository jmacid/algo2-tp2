#include <iostream>
#include <string>

#include "../tda/Celula.h"

using namespace std;

int main() {
  try{
    Celula* cell1 = new Celula(3, 255);

    cout << "Estado celula: " << cell1->getEstado() << endl;

    cell1->actualizarGen(1, 25);
    cell1->actualizarGen(2, 125);
    cell1->actualizarGen(3, 250);

    unsigned int longuitud = cell1->getCantidadGenes();
    for(int i = 0; i < longuitud; i++){
      cout << cell1->getCargaGenetica(i+1) << endl;
    }


    delete cell1;
    
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
  return 0;
} 