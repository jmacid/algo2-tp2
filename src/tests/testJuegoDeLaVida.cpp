#include <iostream>

using namespace std;

#include "../tda/JuegoDeLaVida.h"


int main (){
  try{
    JuegoDeLaVida * juegoDeLaVida = new JuegoDeLaVida();

    juegoDeLaVida->iniciarTableroConTemplate();

    // Turno 1
    juegoDeLaVida->pasarTurno();

    juegoDeLaVida->imprimirStats();

    juegoDeLaVida->imprimirTablero();

    cout << "Imprimiendo...." << endl;
    juegoDeLaVida->imprimirImagenDelTablero();
    
    // // Turno 2
    // juegoDeLaVida->pasarTurno();

    // juegoDeLaVida->imprimirStats();

    // juegoDeLaVida->imprimirTablero();

    // // Turno 3
    // juegoDeLaVida->pasarTurno();

    // juegoDeLaVida->imprimirStats();

    // juegoDeLaVida->imprimirTablero();

    // // Turno 4
    // juegoDeLaVida->pasarTurno();

    // juegoDeLaVida->imprimirStats();

    // juegoDeLaVida->imprimirTablero();
    
    // // Turno 5
    // juegoDeLaVida->pasarTurno();

    // juegoDeLaVida->imprimirStats();

    // juegoDeLaVida->imprimirTablero();
    
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