template<typename T>
struct bit{
// Ref - https://codeforces.com/contest/1208/submission/59476716
	lli n;
	vector<T> fen;
	bit(): n(0) {}
	bit(lli _n) : n(_n), fen(_n+10) {}
	void add(lli p,T val){
		for(;p <= n;p += p & -p)
			fen[p] += val;
	}
	T sum(lli p){
		T ans = 0;
		for(;p > 0;p -= p & -p)
			ans += fen[p];
		return ans;
	}
};


1D BIT:

lli bit[N];

void update(lli idx, lli val)
{
	while(idx<=n)
	{
		bit[idx]+=val;
		idx+=idx&-idx;
	}
}

lli pref(lli idx)
{
	lli ans=0;
	while(idx>0)
	{
		ans+=bit[idx];
		idx-=idx&-idx;
	}
	return ans;
}

lli rsum(lli l, lli r)
{
	return pref(r) - pref(l-1);
}

----------------------------------------------------------------------------------------------------------------------

struct BIT
{
	lli N;
	vector<lli> bit;

	void init(lli n)
	{
		N = n;
		bit.assign(n + 1, 0);
	}

	void update(lli idx, lli val)
	{
		while(idx <= N)
		{
			bit[idx] += val;
			idx += idx & -idx;
		}
	}

	void updateMax(lli idx, lli val)
	{
		while(idx <= N)
		{
			bit[idx] = max(bit[idx], val);
			idx += idx & -idx;
		}
	}

	lli pref(lli idx)
	{
		lli ans = 0;
		while(idx > 0)
		{
			ans += bit[idx];
			idx -= idx & -idx;
		}
		return ans;
	}

	lli rsum(lli l, lli r)
	{
		return pref(r) - pref(l - 1);
	}

	lli prefMax(lli idx)
	{
		lli ans = -2e9;
		while(idx > 0)
		{
			ans = max(ans, bit[idx]);
			idx -= idx & -idx;
		}
		return ans;
	}
};

Multiple BIT:

lli bit[2][N];

void update(lli i, lli idx, lli k)
{
	while(idx<=n)
	{
		bit[i][idx]+=k;
		idx+=idx&-idx;
	}
}

lli pref(lli i, lli idx)
{
	lli ans=0;
	while(idx>0)
	{
		ans+=bit[i][idx];
		idx-=idx&-idx;
	}
	return ans;
}

lli rsum(lli i, lli l, lli r)
{
	return pref(i, r) - pref(i, l-1);
}

//Problem 1: https://codeforces.com/contest/1073/problem/D
//Solution 1: https://codeforces.com/contest/1073/submission/44863255

//Problem 2: https://www.hackerrank.com/contests/university-codesprint-4/challenges/unique-art/problem
//Solution 2: http://p.ip.fi/T9YM
