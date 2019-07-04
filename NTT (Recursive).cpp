namespace ntt{
#define re(i, n)    for(lli i = 0; i < (n); ++i)
#define reA(i, a, n)  for(lli i = a; i <= (n); ++i)
#define reD(i, a, n)  for(lli i = a; i >= (n); --i)
#define SZZ(x) (lli)(x).size()

const lli MAGIC = 200; // (factor 10 optimization for |a|,|b| = 10)

const lli mod = (119LL << 23) + 1, root = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.
// Credits - https://www.codechef.com/viewsolution/20497234
lli modpow(lli a, lli e) {
		if (e == 0) return 1;
			lli x = modpow(a * a % mod, e >> 1);
				return e & 1 ? x * a % mod : x;
}

typedef vector<lli> vl;
void ntt(lli* x, lli* temp, lli* roots, lli N, lli skip) {
	if (N == 1) return;
	lli n2 = N/2;
	ntt(x     , temp, roots, n2, skip*2);
	ntt(x+skip, temp, roots, n2, skip*2);
	re(i,N) temp[i] = x[i*skip];
	re(i,n2) {
		lli s = temp[2*i], t = temp[2*i+1] * roots[skip*i];
		x[skip*i] = (s + t) % mod; x[skip*(i+n2)] = (s - t) % mod;
	}
}
void ntt(vl& x, bool inv = false) {
	lli e = modpow(root, (mod-1) / SZZ(x));
	if (inv) e = modpow(e, mod-2);
	vl roots(SZZ(x), 1), temp = roots;
	reA(i,1,SZZ(x)-1) roots[i] = roots[i-1] * e % mod;
	ntt(&x[0], &temp[0], &roots[0], SZZ(x), 1);
}

void conv(vl &c,vl a, vl b) {
    lli s = SZZ(a) + SZZ(b) - 1; if (s <= 0) { c.clear(); return ;}
	lli L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;

    if (s <= MAGIC) { // (factor 10 optimization for |a|,|b| = 10)
    	c.clear();c.resize(s,0);
		re(i,SZZ(a)) re(j,SZZ(b))
			c[i + j] = (c[i + j] + a[i] * b[j]) % mod;
		return;
	}

    a.resize(n,0); ntt(a);
	b.resize(n,0); ntt(b);
	c.clear();c.resize(n,0);
    lli d = modpow(n, mod-2);
	re(i,n) c[i] = a[i] * b[i] % mod * d % mod;
	ntt(c, true); c.resize(s);
    for(auto &x:c)
    {
        if(x<0)
            x+=mod;
    }
}

// a*a
void conv2(vl &c,vl a) {
    lli s = 2*SZZ(a) - 1; if (s <= 0) { c.clear(); return ;}
	lli L = s > 1 ? 32 - __builtin_clz(s - 1) : 0, n = 1 << L;

    if (s <= MAGIC) { // (factor 10 optimization for |a|,|b| = 10)
        c.clear();c.resize(s,0);
		re(i,SZZ(a)) re(j,SZZ(a))
			c[i + j] = (c[i + j] + a[i] * a[j]) % mod;
		return;
	}

	a.resize(n,0); ntt(a);
    c.clear();c.resize(n,0);
    lli d = modpow(n, mod-2);
	re(i,n) c[i] = a[i] * a[i] % mod * d % mod;
	ntt(c, true); c.resize(s);
    for(auto &x:c)
    {
        if(x<0)
            x+=mod;
    }
}
}
