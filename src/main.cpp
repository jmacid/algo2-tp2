#include <iostream>

using namespace std;

#include "tda/JuegoDeLaVida.h"

#define MESSAGE_INIT "Elija una opcion del menu:"
#define MESSAGE_CONF_1 "[1] Configuracion 1"
#define MESSAGE_CONF_2 "[2] Configuracion 2"
#define MESSAGE_CONF_3 "[3] Configuracion 3"
#define MESSAGE_MANUAL "[4] Ingresar manualmente"

#define MESSAGE_OPCION "Opcion: "

#define MESSAGE_INGRESAR_CELULA_PLANO "Por favor ingrese el plano: "
#define MESSAGE_INGRESAR_CELULA_FILA "Por favor ingrese el fila: "
#define MESSAGE_INGRESAR_CELULA_COLUMNA "Por favor ingrese el columna: "
#define MESSAGE_INGRESAR_CELULA_CONTINUAR "Para seguir ingrtesando celulas presione S: "

#define MESSAGE_TURNOS_REINICIAR_FINALIZAR "Eliga una opcion del menu para continuar:"
#define MESSAGE_TURNO "[t] Pasar un turno"
#define MESSAGE_TURNOS "[v] Pasar varios turno"
#define MESSAGE_REINICIAR "[r] Reiniciar juego"
#define MESSAGE_FINALIZAR "[f] Finalizar juego"
#define MESSAGE_INGRESAR_CANTIDAD_TURNOS "Ingresar cantidad de turnos: "

#define MESSAGE_PLANOS "Ingrese la cantidad de planos del tablero: "
#define MESSAGE_FILAS "Ingrese la cantidad de filas del tablero: "
#define MESSAGE_COLUMNAS "Ingrese la cantidad de columnas del tablero: "

/*
  Prototipos
*/
void ingresarTamanioTablero(JuegoDeLaVida ** juegoDeLaVida);
void iniciarJuego(JuegoDeLaVida ** juegoDeLaVida, char opcionMenu);
void ingresarCelulasVivas(JuegoDeLaVida * juegoDeLaVida);
void elegirOpcionParaContinuar(bool& turno, unsigned int& cantidadTurnos, bool& reiniciar, bool& finalizar);
void finalizarJuego(JuegoDeLaVida ** juegoDeLaVida);

int main (){
  try {
    bool enJuego = true, iniciar = true;
    bool turno = true, reiniciar = false, finalizar = false;
    unsigned int cantidadTurnos = 0;
    char opcionMenu = ' ';
    JuegoDeLaVida * juegoDeLaVida = NULL;

    while(1){

      if(iniciar || reiniciar){
        iniciar = false;
        reiniciar = false;

        cout << MESSAGE_INIT << endl;
        cout << MESSAGE_CONF_1 << endl;
        cout << MESSAGE_CONF_2 << endl;
        cout << MESSAGE_CONF_3 << endl;
        cout << MESSAGE_MANUAL << endl;
        cout << MESSAGE_OPCION;

        cin >> opcionMenu;

        cout << opcionMenu << endl;

        iniciarJuego(&juegoDeLaVida, opcionMenu);

        juegoDeLaVida->imprimirStats();

        juegoDeLaVida->imprimirTablero();

        juegoDeLaVida->imprimirImagenDelTablero();
      }

      elegirOpcionParaContinuar(turno, cantidadTurnos, reiniciar, finalizar);

      if(turno && cantidadTurnos > 0){
        while(cantidadTurnos > 0){
          juegoDeLaVida->pasarTurno();
          juegoDeLaVida->imprimirStats();
          juegoDeLaVida->imprimirTablero();
          cantidadTurnos--;
        }
      }
      else if(reiniciar){
        finalizarJuego(&juegoDeLaVida);
      }
      else if(finalizar){
        finalizarJuego(&juegoDeLaVida);
        return 0;
      }
    }
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

/*
  pre: -
  pos: libera la memoria solicitada
*/
void finalizarJuego(JuegoDeLaVida ** juegoDeLaVida){
  delete *juegoDeLaVida;
  *juegoDeLaVida = NULL;
}

/*
  pre: el juego tiene que estar vacio y la opcion tiene que ser un numero entero entre 1 y 4.
  pos: inicializa el juego segun la opcion elegida
*/
void iniciarJuego(JuegoDeLaVida ** juegoDeLaVida, char opcionMenu){
  if(!(*juegoDeLaVida)->estaVacio()){
    throw "El juego tiene que estar vacio";
  }

  if(opcionMenu == '1'){
    *juegoDeLaVida = new JuegoDeLaVida();
    (*juegoDeLaVida)->iniciarTableroConTemplate1();
  }
  else if(opcionMenu == '2'){
    *juegoDeLaVida = new JuegoDeLaVida();
    (*juegoDeLaVida)->iniciarTableroConTemplate2();
  }
  else if(opcionMenu == '3'){
    *juegoDeLaVida = new JuegoDeLaVida();
    (*juegoDeLaVida)->iniciarTableroConTemplate3();
  }
  else if(opcionMenu == '4'){
    // *juegoDeLaVida = new JuegoDeLaVida();
    ingresarTamanioTablero(juegoDeLaVida);
    ingresarCelulasVivas(*juegoDeLaVida);
  }
  else{
    throw "Opcion incorrecta";
  }
}


/*
  pre: el juego no puede estar vacio
  pos: inicializa el tablero del juego con el tamanio ingresado por el usuario
*/
void ingresarTamanioTablero(JuegoDeLaVida ** juegoDeLaVida){
  if(!(*juegoDeLaVida)->estaVacio()){
    throw "El juego tiene que estar vacio";
  }

  int planos, filas, columnas;

  cout << MESSAGE_PLANOS;
  cin >> planos;

  cout << MESSAGE_FILAS;
  cin >> filas;

  cout << MESSAGE_COLUMNAS;
  cin >> columnas;

  *juegoDeLaVida = new JuegoDeLaVida(planos, filas, columnas);
}

/*
  pre: el juego no puede estar vacio
  pos: carga una celula viva en la ubicacion indicada por el usuario
*/
void ingresarCelulasVivas(JuegoDeLaVida * juegoDeLaVida){
  if(juegoDeLaVida->estaVacio()){
    throw "El juego esta vacio";
  }

  unsigned int plano, fila, columna;
  char continuar;
  bool continuarIngreso = true;
  while(continuarIngreso){
    cout << MESSAGE_INGRESAR_CELULA_PLANO;
    cin >> plano;

    cout << MESSAGE_INGRESAR_CELULA_FILA;
    cin >> fila;

    cout << MESSAGE_INGRESAR_CELULA_COLUMNA;
    cin >> columna;

    juegoDeLaVida->ingresoManualViva(plano, fila, columna);

    cout << MESSAGE_INGRESAR_CELULA_CONTINUAR;
    cin >> continuar;
    
    if(continuar != 'S' && continuar != 's'){
      continuarIngreso = false;
    }
  }
}

/*
  pre: -
  pos: despliega menu con opciones para continuar jugando, reiniciar o finalizar
*/
void elegirOpcionParaContinuar(bool& turno, unsigned int& cantidadTurnos, bool& reiniciar, bool& finalizar){
  char opcion;
  cout << MESSAGE_TURNOS_REINICIAR_FINALIZAR << endl;
  cout << MESSAGE_TURNO << endl;
  cout << MESSAGE_TURNOS << endl;
  cout << MESSAGE_REINICIAR << endl;
  cout << MESSAGE_FINALIZAR << endl;
  cout << MESSAGE_OPCION;
  cin >> opcion;

  if (opcion == 't'){
    turno = true;
    cantidadTurnos = 1;
  }
  else if (opcion == 'v'){
    turno = true;
    cout << MESSAGE_INGRESAR_CANTIDAD_TURNOS;
    cin >> cantidadTurnos;
    if(cantidadTurnos == 0)
      throw "Cantidad de turnos incorrecta";
  }
  else if (opcion == 'r'){
    reiniciar = true;    
  }
  else if (opcion == 'f'){
    finalizar = true;
  }
}