#include <iostream>
#include <string>
using namespace std;

#include "../tda/BmpHandle.h"


int main (){
  try{

    BmpHandle* bmpHandle = new BmpHandle(10, 10);

    bmpHandle->iniciar();
    bmpHandle->imprimirCuadradito(0, 0, 255, 0, 0);
    string nombreArchivo = "test";
    bmpHandle->finalizar(nombreArchivo);
    
    
    delete bmpHandle;

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