#include <atcoder/modint>
using namespace atcoder;
//using mint = modint998244353;
//using mint = modint1000000007;
std::ostream& operator << (std::ostream& out, const mint& rhs) {
        return out<<rhs.val();
    }

// Ref - https://www.codechef.com/viewsolution/41909444 Line 827 - 850.
const int N=2e6+5;
array<mint,N+1> fac,inv;

mint nCr(lli n,lli r)
{
    if(n<0||r<0||r>n)
        return 0;
    return fac[n]*inv[r]*inv[n-r];
}

void pre(lli n)
{
    fac[0]=1;
    for(int i=1;i<=n;++i)
        fac[i]=i*fac[i-1];
    inv[n]=fac[n].pow(mint(-2).val());
    for(int i=n;i>0;--i)
        inv[i-1]=i*inv[i];
    assert(inv[0]==mint(1));
}
