// Credits @tfg
//https://codeforces.com/contest/1100/submission/48339644

struct Gauss {
	static const lli me = 62;
	lli table[me];

	Gauss() {
		for(lli i = 0; i < me; i++) {
			table[i] = 0;
		}
	}

	lli size() {
		lli ans = 0;
		for(lli i = 0; i < me; i++) {
			if(table[i]) ans++;
		}
		return ans;
	}

	bool can(lli x) {
		for(lli i = me-1; i >= 0; i--) {
			x = std::min(x, x ^ table[i]);
		}
		return x == 0;
	}

	void add(lli x) {
		for(lli i = me-1; i >= 0 && x; i--) {
			if(table[i] == 0) {
				table[i] = x;
				x = 0;
			} else {
				x = std::min(x, x ^ table[i]);
			}
		}
	}

	lli best() {
		lli x = 0;
		for(lli i = me-1; i >= 0; i--) {
			x = std::max(x, x ^ table[i]);
		}
		return x;
	}

	void merge(Gauss &other)
	{
		for(lli i = me-1; i >= 0; i--)
			add(other.table[i]);
	}
};
