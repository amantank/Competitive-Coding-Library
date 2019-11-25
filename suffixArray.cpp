// Untested.

#include <bits/stdc++.h>
using namespace std;

#define fo(i,n)   for(i=0;i<(n);++i)
#define repA(i,j,n)   for(i=(j);i<=(n);++i)
#define repD(i,j,n)   for(i=(j);i>=(n);--i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define endl "\n"

typedef long long int lli;
typedef long double mytype;
typedef pair<lli,lli> ii;
typedef vector<ii> vii;
typedef vector<lli> vi;

// Credits - https://codeforces.com/contest/963/submission/37425722

void count_sort(vector<pair<lli, int>> &b, int bits) { // (optional)
	//this is just 3 times faster than stl sort for N=10^6
	int mask = (1 << bits) - 1;
    for(int it = 0; it < 2; ++it)
	{
		int move = it * bits;
		vi q(1 << bits), w(sz(q) + 1);
		for(int i = 0; i < sz(b); ++i)
			q[(b[i].first >> move) & mask]++;
		partial_sum(q.begin(), q.end(), w.begin() + 1);
		vector<pair<lli, int>> res(b.size());
        for(int i = 0; i < sz(b); ++i)
			res[w[(b[i].first >> move) & mask]++] = b[i];
		swap(b, res);
	}
}
struct SuffixArray {
	vi a;
	string s;
	SuffixArray(const string& _s) : s(_s + '\0') {
		int N = sz(s);
		vector<pair<lli, int>> b(N);
		a.resize(N);
		for(int i = 0; i < N; ++i)
		{
			b[i].first = s[i];
			b[i].second = i;
		}

		int q = 8;
		while ((1 << q) < N) q++;
		for (int moc = 0;; moc++) {
			count_sort(b, q); // sort(all(b)) can be used as well
			a[b[0].second] = 0;
			for(int i = 1; i < N; ++i)
				a[b[i].second] = a[b[i - 1].second] +
					(b[i - 1].first != b[i].first);

			if ((1 << moc) >= N) break;
			for(int i = 0; i < N; ++i)  {
				b[i].first = (lli)a[i] << q;
				if (i + (1 << moc) < N)
					b[i].first += a[i + (1 << moc)];
				b[i].second = i;
			}
		}
		rep(i,0,sz(a)) a[i] = b[i].second;
	}
	int lower_bound(string t){
		int l = 1,r=sz(a);
		while(l<r){
			int m = (l+r)/2;
			if(s.substr(a[m],min(sz(s)-1-a[m],sz(t)+1)) >= t) r = m;
			else l = m+1;
		}
		return l;
	}
	int upper_bound(string t){
		int l = 1,r=sz(a);
		while(l<r){
			int m = (l+r)/2;
			if(s.substr(a[m],min(sz(a)-1-a[m],sz(t))) > t) r = m;
			else l = m+1;
		}
		return l;
	}
	vi lcp() {
		// longest common prefixes: res[i] = lcp(a[i], a[i-1])
		int n = sz(a), h = 0;
		vi inv(n), res(n);
		for(int i = 0; i <n; ++i)  inv[a[i]] = i;
		for(int i = 0; i <n; ++i)  if (inv[i] > 0) {
			int p0 = a[inv[i] - 1];
			while (s[i + h] == s[p0 + h]) h++;
			res[inv[i]] = h;
			if(h > 0) h--;
		}
		return res;
	}
};

int main() {
	return 0;
}
