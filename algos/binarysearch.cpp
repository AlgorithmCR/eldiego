#include <functional>
//C++11
//Busca el minimo x (minX <= x <= maxX) tal que f(x) >= value
int lowerBound(int minX, int maxX, function<int(int)> f, int value){
	int low = minX, hi = maxX+1, mid;
	while(low < hi){
		mid = (low+hi)/2;
		int v = f(mid);
		if (v >= value) hi = mid;
		else low = mid+1;
	}
	return low;
}

//Busca el minimo x (minX <= x <= maxX) tal que f(x) > value
int upperBound(int minX, int maxX, function<int(int)> f, int value){
	int low = minX, hi = maxX+1, mid;
	while(low < hi){
		mid = (low+hi)/2;
		int v = f(mid);
		if (v <= value) low = mid+1;
		else hi = mid;
	}
	return low;
}
#define SEARCH_ERROR 1e-9
//Busca el minimo x (minX <= x <= maxX) tal que x cumpla el predicado p(x) con error menor a SEARCH_ERROR
double realLowerBound(double minX, double maxX, function<bool(double)> p) {
	double lo = minX, hi = maxX, mid = 0.0, ans = 0.0;
	int iterations = (int)floor(log2((maxX-minX)/SEARCH_ERROR)+7); //Calcula iteraciones para cumplir con SEARCH_ERROR
	forn (i, iterations) {
		mid = (lo + hi) / 2.0;
		if (p(mid)) { ans = mid; hi = mid; }
		else lo = mid;
	}
	return ans;
}

//Retorna argmax de una funcion unimodal 'f' en el rango [right,left]
//Dependiendo del if en el SEARCH_ERROR minimiza el error del f(argmax) o de argmax
double ternarySearch(double right, double left, function<double(double)> f){
	double leftThird, rightThird;
	while(true){
		if (abs(f(right) - f(left)) < SEARCH_ERROR){//Quitar f() si se quiere minimizar el error de argmax
			return (left + right)/2;
		}

		leftThird=left+(right-left)/3;
		rightThird=right -  (right - left)/3;

		if (f(leftThird) > f(rightThird)){ //Cambiar por '<' si se quiere minimizar (argmin)
			left = leftThird;
		} else {
			right = rightThird;
		}

	}
}
