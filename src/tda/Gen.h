#ifndef GEN_H_
#define GEN_H_

class Gen {
  private:
    unsigned int cargaGenetica;
    unsigned int maximaCargaGenetica;

    void verificar(unsigned int maximaCargaGenetica, unsigned int cargaGenetica);
  
  public:
    Gen(unsigned int maximaCargaGenetica, unsigned int cargaGenetica);
    ~Gen();
    unsigned int getCargaGentica();
    void setCargaGentica(unsigned int cargaGenetica);
    unsigned int getMaximoCargaGenetica();
};

/*
  pre: el rango de carga debe estar entre 0 y maximaCargaGenetica. maximaCargaGenetica debe ser mayor o igual a cero.
  pos: crea el gen con el valor de la carga y el maximo indicado
*/
Gen::Gen(unsigned int maximaCargaGenetica, unsigned int cargaGenetica){
  verificar(maximaCargaGenetica, cargaGenetica);
    this->maximaCargaGenetica = maximaCargaGenetica;
  this->cargaGenetica = cargaGenetica;
}

/* 
  pre: -
  pos: detruye el objeto
*/
Gen::~Gen(){}

unsigned int Gen::getCargaGentica(){
  return this->cargaGenetica;
}

/*
  pre: la carga genetica no puede ser mayor al maximo ni menor a cero
  pos: asigna el valor de la carga genetica
*/
void Gen::setCargaGentica(unsigned int cargaGenetica){
  this->verificar(this->maximaCargaGenetica, cargaGenetica);
  this->cargaGenetica = cargaGenetica;
}

/*
  pre: -
  pos: retorna el maximo de la carga genetica
*/
unsigned int Gen::getMaximoCargaGenetica(){
  return this->maximaCargaGenetica; 
}

/*
  pre: -
  pos: tira una excepcion cuando maximaCargaGenetica o cargaGenetica no respeta los rangos
*/
void Gen::verificar(unsigned int maximaCargaGenetica, unsigned int cargaGenetica){
  if(maximaCargaGenetica < 0)
    throw "La maxima carga genetica debe ser mayor a cero";

  if(cargaGenetica > maximaCargaGenetica)
    throw "El rango de cargaGenetica debe estar entre 0 y 255";
}

#endif // GEN_H_