#include <functional>
//Retorna argmax de una funcion unimodal 'f' en el rango [left,right]
double ternarySearch(double l, double r, function<double(double)> f){
	for(int i = 0; i < 300; i++){
		double m1 = l+(r-l)/3, m2 = r-(r-l)/3;
		if (f(m1) < f(m2))	l = m1;	else r = m2;		
	}
	return (left + right)/2;
}
