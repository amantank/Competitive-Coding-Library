// #include <atcoder/convolution>
// #include <atcoder/modint>
// using namespace atcoder;
// using mint = modint998244353;

// Ref - https://www.codechef.com/viewsolution/41909444 Line 850 - 886.
template <class T>
vector<T> polyInverse(vector<T>& h,int len){
    auto add=[](vector<T> a,vector<T> b) -> vector<T>
        {
            if(sz(a)<sz(b))
                a.swap(b);
            for(lli i=0;i<sz(b);++i)
                a[i]+=b[i];
            return a;
        };
    auto conv=[&](const vector<T> &a,const vector<T> &b) -> vector<T>
        {
            return convolution(a,b);
        };
    int n=1;
    while(n<len)
        n*=2;
    if(sz(h)<n) h.resize(n,T(0));
    vector<T> ans;
    ans.pb(h[0].pow(mod-2));
    for(int l = 2;l<=n;l*=2){
        vector<T> a = ans;
        vector<T> h0 = vector<T>(h.begin(),h.begin()+l/2);
        vector<T> h1 = vector<T>(h.begin()+l/2,h.begin()+l);
        vector<T> c = conv(a,h0);
        if(sz(c)<l/2+1) c.resize(l/2+1,T(0));
        c = vector<T>(c.begin()+l/2,c.end());
        vector<T> tem = add(c,conv(a,h1));
        tem.resize(l/2,T(0));
        vector<T> b = conv(a,tem);
        b.resize(l/2,T(0));
        for(auto i:b) ans.pb(-i);
    }
    // while(sz(ans)>1&&ans.back()==0) ans.pop_back();
    while(sz(h)>1&&h.back()==0) h.pop_back();
    return ans;
}