template <typename T>
inline void read(T& x){
    int f = 1; x = 0; char s = getchar();
    while (s < '0' || s > '9') { if (s == '-') f = -1; s = getchar(); }
    while (s <= '9' && s >= '0') x = x * 10 + (s ^ 48), s = getchar();
    x *= f;
}

template <typename T> 
inline void print(T x){
    if(x < 0){ putchar('-'); x = -x; }
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

inline void sread(string& s){
    char ch = getchar();
    while(ch == ' ' || ch == '\n' || ch == '\t') ch = getchar();
    while(ch != ' ' && ch != '\n' && ch != '\t') s += ch, ch = getchar();
}

inline void sprint(const string& s){ for(auto &ch : s) putchar(ch); }