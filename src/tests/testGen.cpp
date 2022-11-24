#include <iostream>

#include "../tda/Gen.h"

using namespace std;

int main() {
  try{
    Gen *g1 = new Gen(255, 21);
    cout << "Obtener carga: " << g1->getCargaGentica() << endl;
    Gen *g2 = new Gen(20, 25);

    delete g1;
    delete g2;
    
  }
  catch(char const* excp){
    cout << "Excepcion: " << excp << endl;
  } catch(...){
    cout << "Excepcion desconocida" << endl;
  }
  return 0;
} 