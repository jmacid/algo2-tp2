#include <iostream>

#include "../tda/Celula.h"

using namespace std;

int main() {
  try{
    Celula* cell1 = new Celula(3, 255);

    cout << "Estado celula: " << cell1->getEstado() << endl;

    unsigned int longuitud = cell1->getCantidadGenes();
    for(int i = 0; i < longuitud; i++){
      cout << cell1->getCargaGenetica(i+1) << endl;
    }

    delete cell1;
    
  }
  catch(char const* excp){
    cout << "Excepcion: " << excp << endl;
  } catch(...){
    cout << "Excepcion desconocida" << endl;
  }
  return 0;
} 