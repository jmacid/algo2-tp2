#include <iostream>

using namespace std;

#include "../tda/JuegoDeLaVida.h"


int main (){
  try{
    JuegoDeLaVida * juegoDeLaVida = new JuegoDeLaVida();

    juegoDeLaVida->iniciarTableroConTemplate();

    juegoDeLaVida->pasarTurno();

    juegoDeLaVida->imprimirTablero();

    juegoDeLaVida->pasarTurno();

    juegoDeLaVida->imprimirTablero();
    
    delete juegoDeLaVida;

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