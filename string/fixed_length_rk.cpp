#include <bits/stdc++.h>
#include <functional>
using namespace std;
#define MAXN 100005

typedef long long ll;
typedef function<char(int)> f_getter;
typedef function<void(ll)> f_matcher;



struct RobinKarpMatchSetting {
	int p_length; //Largo pattern a buscar
	int t_length; //Largo texto en el que buscar
	f_getter t_getter; //Funcion que devuelve el iesimo elemento del texto
	f_matcher matcher; //Funcion que se activa cada vez que hay match
};

ll rk_pot[MAXN];
ll rk_p = 257, rk_M = 1000000007, rk_p_inv = 70038911; //pow(257,10**9+7-2,10**9+7)
void initRK(){
	ll p = 1;
	for (int i = 0; i < MAX_LENGTH; i++, p=(p*rk_p)%rk_M){
		rk_pot[i]=p;
	}
}

ll calcHashRK(int start, int offset, f_getter getter){
	ll r = 0;
	for (int i = start; i < start+offset; i++) r=(r+rk_pot[i-start]*getter(i))%rk_M;
	return r;
}

void RKSearch(RobinKarpMatchSetting &ms){
	ll h = calcHashRK(0,ms.p_length,ms.t_getter);
	ms.matcher(h);
	for (int i = ms.p_length; i < ms.t_length; i++){
		h = ((h-ms.t_getter(i-ms.p_length))%rk_M+rk_M)%rk_M;
		h = ( h * rk_p_inv ) % rk_M;
		h = (h + ms.t_getter(i)*rk_pot[ms.p_length-1]) % rk_M;
		ms.matcher(h);
	}
}

string text[35];
int N;

//Return 2 if not shared, 1 if shared
int evalLength(int length){
	set<ll> shared;
	RobinKarpMatchSetting ms;
	ms.t_length = text[0].size();
	ms.t_getter = [](int j)->char{return text[0][j];};
	ms.p_length = length;
	ms.matcher = [&shared](ll h){shared.insert(h);};
	RKSearch(ms);
	for (int i = 1; i < N; i++){
		set<ll> newShared;
		ms.matcher = [&shared,&newShared](ll h){if (shared.count(h)) newShared.insert(h);};
		ms.t_getter = [i](int j)->char{return text[i][j];};
		ms.t_length = text[i].size();
		RKSearch(ms);
		if (newShared.size() == 0) return 2;
		shared = newShared;
	}
	return 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	initRK();
	while (cin >> N){
		int minLength = 100005;
		for (int i = 0; i < N; i++) {
			cin >> text[i];
			minLength=min(minLength,(int)text[i].size());
		}
		cout << (lowerBound(1,minLength,evalLength,2) - 1) << "\n";
	}
}
