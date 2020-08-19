#include <stdio.h>
#include <math.h>
#include <iostream>

#define BUF_SIZE  256
#define EPS       1e-12

class Complejo {
  double _re, _im;
  
public:
  Complejo(double, double);
  Complejo(double);
  Complejo(void);
  
  void display(const char *);
  void display(void);
  
  // esto lo copie de los slides, sin el friend el compilador se queja
  // aun cuando defino los operadores como metodos de la clase Complejo
  friend Complejo operator+(Complejo);
  friend Complejo operator-(Complejo);
  
  friend Complejo operator+(Complejo, Complejo);
  friend Complejo operator-(Complejo, Complejo);
  friend Complejo operator*(Complejo, Complejo);
  friend Complejo operator/(Complejo, Complejo);
  
  struct InvalidFormat { };
  
};
  
  
// no me gustan que una variable i sea double,
// me habra quedado un "complejo" (pun) de haber tenido que lidiar con fortran 77
Complejo::Complejo(double real, double imag) {
  _re = real;
  _im = imag;
}


Complejo::Complejo(double real) {
  _re = real;
  _im = 0;
}

Complejo::Complejo(void) {
  _re = 0;
  _im = 0;
}

void Complejo::display(const char *fmt) {
  
  char full_fmt[BUF_SIZE];
  
  if (fmt[0] != '%') {
    throw InvalidFormat{};
  }

  if (fabs(_re) < EPS && fabs(_im) < EPS) {
    printf("0");
  } else if (fabs(_re) < EPS) {
    
    snprintf(full_fmt, BUF_SIZE-1, "%si", fmt);
    printf(full_fmt, _im);
    
  } else if (fabs(_im) < EPS) {
    
    snprintf(full_fmt, BUF_SIZE-1, "%s", fmt);
    printf(full_fmt, _re);
    
  } else if (_im > 0) {
    // TODO: habria que atrapar el caso en el que _im == 1 y no escribir el 1
    snprintf(full_fmt, BUF_SIZE-1, "%s + %si", fmt, fmt);
    printf(full_fmt, _re, +_im);
    
  } else {
    // TODO: idem
    snprintf(full_fmt, BUF_SIZE-1, "%s - %si", fmt, fmt);
    printf(full_fmt, _re, -_im);
  }
  
  return;
}


void Complejo::display(void) {
  display("%g");
  return;
}


Complejo operator+(Complejo a) {
  return a;
}

Complejo operator-(Complejo a) {
  return Complejo(-a._re, -a._im);
}

Complejo operator+(Complejo a, Complejo b) {
  return Complejo(a._re + b._re, a._im + b._im);
}

Complejo operator-(Complejo a, Complejo b) {
  return Complejo(a._re - b._re, a._im - b._im);
}

Complejo operator*(Complejo a, Complejo b) {
  return Complejo(a._re*b._re - a._im*b._im, a._re*b._im + a._im*b._re);
}

Complejo operator/(Complejo a, Complejo b) {
  double k = 1.0/(b._re*b._re + b._im*b._im);
  return Complejo(k*(a._re*b._re + a._im*b._im), k*(a._re*b._im - a._im*b._re));
}


int main(void) {
  
  Complejo a = Complejo(1,2);
  Complejo b = Complejo(1,-2);
  Complejo i = Complejo(0,1);
  
  // aca hay que overloadear el operador << para que se pueda hacer
  // std:cout << "a = " << a << "\n";
  std::cout << "a = ";
  a.display();
  std::cout << "\n";
  
  std::cout << "b = ";
  b.display();
  std::cout << "\n";
  
  std::cout << "+a = ";
  (+a).display();
  std::cout << "\n";
  
  std::cout << "-a = ";
  (-a).display();
  std::cout << "\n";
  
  std::cout << "a+b = ";
  (a+b).display();
  std::cout << "\n";
  
  std::cout << "a*b = ";
  (a*b).display();
  std::cout << "\n";

  std::cout << "a/b = ";
  (a/b).display("%.2f");
  std::cout << "\n";
  
  std::cout << "i^2 = ";
  (i*i).display();
  std::cout << "\n";
  
  std::cout << "-1/i = ";
  (Complejo(-1)/Complejo(0,1)).display();
  std::cout << "\n";
  
}
