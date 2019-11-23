const int N=1e5+5;
const int mod=1000000007L;
lli fac[N+5],inv[N+5];

lli po(lli a,lli n)
{
    if(n==0)
        return 1;
    if(n%2)
        return (a*po(a,n-1))%mod;
    return po(a*a%mod,n/2);
}

lli nCr(lli n,lli r)
{
    if(n<0||r<0||r>n)
        return 0;
    lli ans=1;
    ans=(ans*fac[n])%mod;
    ans=(ans*inv[r])%mod;
    ans=(ans*inv[n-r])%mod;
    return ans;
}

void pre(lli n)
{
    lli i;
    fac[0]=1;
    repA(i,1,n)
        fac[i]=(i*fac[i-1])%mod;
    inv[n]=po(fac[n],mod-2);
    repD(i,n,1)
        inv[i-1]=(i*inv[i])%mod;
    assert(inv[0]==1);
}