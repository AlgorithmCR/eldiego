struct Fenwick{
	static const int sz=1000001;
	tipo t[sz];
	tipo sum(int a, int b){return sum(b)-sum(a-1);}
	void adjust(int p, tipo v){//valid with p in [1, sz), O(lgn)
		for(; p<sz; p+=(p&-p)) t[p]+=v; }
		tipo sum(int p){//cumulative sum in [1, p], O(lgn)
		tipo s=0;
		for(; p; p-=(p&-p)) s+=t[p];
		return s;
	}
	//get largest value with cumulative sum less than or equal to x;
	//for smallest, pass x-1 and add 1 to result
	int getind(tipo x) {//O(lgn)
	  	int idx = 0, mask = N;
	  	while(mask && idx < N) {
	   		int t = idx + mask;
			if(x >= tree[t])
		  		idx = t, x -= tree[t];
	   		mask >>= 1;
	  	}
	  	return idx;
	}
};