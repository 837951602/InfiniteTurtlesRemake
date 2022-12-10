#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <bitset>
#include "state.define.h"

struct bitset128 {
    union {
        struct {
            uint64_t LOW, HIGH;
        } i;
        std::bitset<128> b;
    };
    int lowbit() {
        if (i.LOW) return __builtin_ffsll(i.LOW) -1;
        if (i.HIGH) return __builtin_ffsll(i.HIGH) -1 + 64;
        return -1;
    }
    bitset128() { i.HIGH = i.LOW = 0;}
    operator bool() {
        return i.HIGH | i.LOW;
    }
    bitset128& operator |= (bitset128 o) {
        i.HIGH |= o.i.HIGH;
        i.LOW |= o.i.LOW;
        return *this;
    }
    void clear() {
        i.LOW = i.HIGH = 0;
    }
};
using std::unordered_map;
using std::vector;
void** StateBase;
template<class T>
void reallocT(T*& p, size_t n) {
    // realloc, if fail then throw
    T* q = (T*)realloc((void*)p, n);
    if (q==0 && n!=0) throw "Unable to allocate";
    p = q;
} 
uint StateLen;
struct Adx {
    uint n;
    Adx() {}
    Adx(uint n): n(n) {}
    Adx(const Adx& o): n(o.n) {}
    struct State& operator*() const ;
    bool operator< (Adx o) const {
        return n<o.n;
    }
    bool operator== (Adx o) const {
        return n==o.n;
    }
};
template<>
struct std::hash<Adx> {
    uint operator() (const Adx& v) const {
        return v.n;
    }
};
struct Design {
    Tile tile[109];
    char zeroBefore[16] = {};
    char throws[200];
    char zeroAfter[16] = {};
    Design* extra[109];
    int extraLen;
    struct convType {
        Tile t;
        Design* d;
        convType(Tile t): t(t), d(nullptr) {}
        convType(Design& d): t(CallDef), d(&d) {}
        convType(Tile t, Design& d): t(CallDef | t), d(&d) {}
    };
    void precfg() {
        extraLen = 0;
        for (int i=0; i<200; ++i) throws[i] = 1;
        for (int i=0; i<109; ++i) {
            int N, E, W, S, bN, bE, bW, bS;
            int _N = i+90, _E = i-9, _S = i+100, _W = i-10;
            int _bN = i-10, _bE = i+1, _bS = i+10, _bW = i-1;
            switch (tile[i]) {
            case4 (BeltWE)
                throws[W] = 0;
            case4 (BeltNE)
                throws[N] = 0;
            case4 (BeltWE_NS)
                throws[W] = throws[N] = 0;
            case8 (BeltNE_WS)
                throws[W] = throws[N] = 0;
            case8 (BeltWNE)
                throws[W] = throws[N] = 0;
            case8 (BeltNSE)
                throws[S] = throws[N] = 0;
            case8 (BeltWNSE)
                throws[W] = throws[N] = throws[S] = 0;
            case4 (TransIncr)
                throws[W] = 0;
            case4 (TransDecr)
                throws[W] = 0;
            case4 (TransNul)
                throws[W] = 0;
            case8 (Dup)
                throws[W] = 0;
            case8 (Filter0)
                throws[W] = 0;
            case8 (FilterNul)
                throws[W] = 0;
            case8 (LockOpen)
                throws[W] = throws[N] = 0;
            case8 (LockClose)
                throws[W] = throws[N] = 0;
            case8 (LockBoth)
                throws[W] = throws[N] = 0;
            case8 (Switch)
                throws[W] = throws[E] = 0;
            case4 (RetBlock) 
                throws[W] = 0;
            case8 (CallDef)
                ++extraLen;
                throws[N] &= (*extra[i]).tile[4] == RetBlock+Ngg;
                throws[E] &= (*extra[i]).tile[59] == RetBlock+Egg;
                throws[S] &= (*extra[i]).tile[104] == RetBlock+Sgg;
                throws[W] &= (*extra[i]).tile[49] == RetBlock+Wgg;
            }
        }
    }
    Design(
        convType x0,convType x1,convType x2,convType x3,convType x4,convType x5,convType x6,convType x7,convType x8,
        convType x9,convType x10,convType x11,convType x12,convType x13,convType x14,convType x15,convType x16,convType x17,
        convType x18,convType x19,convType x20,convType x21,convType x22,convType x23,convType x24,convType x25,convType x26,
        convType x27,convType x28,convType x29,convType x30,convType x31,convType x32,convType x33,convType x34,convType x35,
        convType x36,convType x37,convType x38,convType x39,convType x40,convType x41,convType x42,convType x43,convType x44,
        convType x45,convType x46,convType x47,convType x48,convType x49,convType x50,convType x51,convType x52,convType x53,
        convType x54,convType x55,convType x56,convType x57,convType x58,convType x59,convType x60,convType x61,convType x62,
        convType x63,convType x64,convType x65,convType x66,convType x67,convType x68,convType x69,convType x70,convType x71,
        convType x72,convType x73,convType x74,convType x75,convType x76,convType x77,convType x78,convType x79,convType x80,
        int Ntype, int Etype, int Stype, int Wtype) {
        tile[10]=x0.t, tile[11]=x1.t, tile[12]=x2.t, tile[13]=x3.t, tile[14]=x4.t, tile[15]=x5.t, tile[16]=x6.t, tile[17]=x7.t, tile[18]=x8.t, tile[20]=x9.t, tile[21]=x10.t, tile[22]=x11.t, tile[23]=x12.t, tile[24]=x13.t, tile[25]=x14.t, tile[26]=x15.t, tile[27]=x16.t, tile[28]=x17.t, tile[30]=x18.t, tile[31]=x19.t, tile[32]=x20.t, tile[33]=x21.t, tile[34]=x22.t, tile[35]=x23.t, tile[36]=x24.t, tile[37]=x25.t, tile[38]=x26.t, tile[40]=x27.t, tile[41]=x28.t, tile[42]=x29.t, tile[43]=x30.t, tile[44]=x31.t, tile[45]=x32.t, tile[46]=x33.t, tile[47]=x34.t, tile[48]=x35.t, tile[50]=x36.t, tile[51]=x37.t, tile[52]=x38.t, tile[53]=x39.t, tile[54]=x40.t, tile[55]=x41.t, tile[56]=x42.t, tile[57]=x43.t, tile[58]=x44.t, tile[60]=x45.t, tile[61]=x46.t, tile[62]=x47.t, tile[63]=x48.t, tile[64]=x49.t, tile[65]=x50.t, tile[66]=x51.t, tile[67]=x52.t, tile[68]=x53.t, tile[70]=x54.t, tile[71]=x55.t, tile[72]=x56.t, tile[73]=x57.t, tile[74]=x58.t, tile[75]=x59.t, tile[76]=x60.t, tile[77]=x61.t, tile[78]=x62.t, tile[80]=x63.t, tile[81]=x64.t, tile[82]=x65.t, tile[83]=x66.t, tile[84]=x67.t, tile[85]=x68.t, tile[86]=x69.t, tile[87]=x70.t, tile[88]=x71.t, tile[90]=x72.t, tile[91]=x73.t, tile[92]=x74.t, tile[93]=x75.t, tile[94]=x76.t, tile[95]=x77.t, tile[96]=x78.t, tile[97]=x79.t, tile[98]=x80.t;
        extra[10]=x0.d, extra[11]=x1.d, extra[12]=x2.d, extra[13]=x3.d, extra[14]=x4.d, extra[15]=x5.d, extra[16]=x6.d, extra[17]=x7.d, extra[18]=x8.d, extra[20]=x9.d, extra[21]=x10.d, extra[22]=x11.d, extra[23]=x12.d, extra[24]=x13.d, extra[25]=x14.d, extra[26]=x15.d, extra[27]=x16.d, extra[28]=x17.d, extra[30]=x18.d, extra[31]=x19.d, extra[32]=x20.d, extra[33]=x21.d, extra[34]=x22.d, extra[35]=x23.d, extra[36]=x24.d, extra[37]=x25.d, extra[38]=x26.d, extra[40]=x27.d, extra[41]=x28.d, extra[42]=x29.d, extra[43]=x30.d, extra[44]=x31.d, extra[45]=x32.d, extra[46]=x33.d, extra[47]=x34.d, extra[48]=x35.d, extra[50]=x36.d, extra[51]=x37.d, extra[52]=x38.d, extra[53]=x39.d, extra[54]=x40.d, extra[55]=x41.d, extra[56]=x42.d, extra[57]=x43.d, extra[58]=x44.d, extra[60]=x45.d, extra[61]=x46.d, extra[62]=x47.d, extra[63]=x48.d, extra[64]=x49.d, extra[65]=x50.d, extra[66]=x51.d, extra[67]=x52.d, extra[68]=x53.d, extra[70]=x54.d, extra[71]=x55.d, extra[72]=x56.d, extra[73]=x57.d, extra[74]=x58.d, extra[75]=x59.d, extra[76]=x60.d, extra[77]=x61.d, extra[78]=x62.d, extra[80]=x63.d, extra[81]=x64.d, extra[82]=x65.d, extra[83]=x66.d, extra[84]=x67.d, extra[85]=x68.d, extra[86]=x69.d, extra[87]=x70.d, extra[88]=x71.d, extra[90]=x72.d, extra[91]=x73.d, extra[92]=x74.d, extra[93]=x75.d, extra[94]=x76.d, extra[95]=x77.d, extra[96]=x78.d, extra[97]=x79.d, extra[98]=x80.d;
        tile[0]=Empty, tile[1]=Empty, tile[2]=Empty, tile[3]=Empty, tile[5]=Empty, tile[6]=Empty, tile[7]=Empty, tile[8]=Empty, tile[9]=Empty, tile[19]=Empty, tile[29]=Empty, tile[39]=Empty, tile[69]=Empty, tile[79]=Empty, tile[89]=Empty, tile[99]=Empty, tile[100]=Empty, tile[101]=Empty, tile[102]=Empty, tile[103]=Empty, tile[105]=Empty, tile[106]=Empty, tile[107]=Empty, tile[108]=Empty;
        tile[4]=Ntype==1?RetBlock|Ngg:BeltWE|Sgg;
        tile[49]=Wtype==1?RetBlock|Wgg:BeltWE|Egg;
        tile[59]=Etype==1?RetBlock|Egg:BeltWE|Wgg;
        tile[104]=Stype==1?RetBlock|Sgg:BeltWE|Ngg;
        precfg();
    }
};
struct Movement {
    unsigned char pos, ref;
    Token val;
    Movement(unsigned char pos, unsigned char ref, Token val): pos(pos), ref(ref), val(val) {}
};
struct vectorMovement {
    Movement* ptr = 0;
    int siz = 0, prsiz = 0;
    int size() { return siz; }
    void push_back(Movement x) {
        if (siz == prsiz) {
            reallocT(ptr, (prsiz = 2*siz+1)*sizeof(*ptr));
        }
        ptr[siz++] = x;
    }
    void emplace_back(unsigned char pos, unsigned char ref, Token val) {
        push_back(Movement(pos, ref, val));
    }
    void clear() { siz = 0;}
    Movement* begin() { return ptr; }
    Movement* end() { return ptr+siz; }
};
struct State {
    Token val[2*10*10];
    Tile tile[109];
    unsigned char parentpos, direction, extraCnt;
    const Design* design;
    Adx parent;
    bitset128 activeStates, activeStatesA;
    vectorMovement movements;
    Adx extra[0];
};
State& Adx::operator*() const { return *(State*)(StateBase+n); }

vector<Adx> actList;

vector<Adx> StateList;
Adx summon(const Design& design, Adx parent, unsigned char parentpos = 54, unsigned char direction = 0) {
    Adx dstpos = StateLen;
    StateList.push_back (dstpos);
    // printf ("SIZING: %d %d %d\n", sizeof(State), sizeof(Adx)*design.extraLen, (sizeof(State) + sizeof(Adx)*design.extraLen + sizeof(void*) - 1) / sizeof(void*));
    StateLen += (sizeof(State) + sizeof(Adx)*design.extraLen + sizeof(void*) - 1) / sizeof(void*);
    //printf ("LEN=%lld\n", StateLen);
    reallocT (StateBase, StateLen * sizeof(void*));
    State& dst = *dstpos;
    for (int i=0; i<109; ++i) dst.tile[i] = design.tile[i]>200?Call:design.tile[i];
    for (int i=0; i<2*10*10; ++i) dst.val[i] = 255;
    dst.parent = parent;
    dst.parentpos = parentpos;
    dst.direction = direction;
    dst.design = &design;
    dst.extraCnt = 0;
    return dstpos;
}
void step() {
    #define state (*stateaddr)
    
    for (size_t actID=0, actLen = actList.size(); actID<actLen; ++actID) { 
        Adx actstate = actList[actID];
        State* stateaddr = &*actstate;
        const Design& design = *(state.design);
        vectorMovement* localmovesptr = &(state.movements);
        #define localmoves (*localmovesptr)
        bitset128 actpos = state.activeStates;
        state.activeStates.clear();
        if (!(bool)actpos) continue;
        bitset128 actposA = state.activeStatesA;
        for (int i; (i=actpos.lowbit())!=-1; actpos.b.reset(i)) {
            #include "state.move.hpp"
        }
        state.activeStatesA = actposA;
    }
    size_t actDst = 0;
    for (size_t actID=0, actLen = actList.size(); actID<actLen; ++actID) { 
        Adx actstate = actList[actID];
        State* stateaddr = &*actstate;
        if (state.movements.size()) actList[actDst++] = actList[actID]; else continue;
        for (auto &i: state.movements) {
            state.val[i.pos] = i.val;
        }
        state.activeStates = state.activeStatesA;
        state.activeStatesA.clear();
        state.movements.clear();
    }
    actList.resize(actDst);
    #undef state
    #undef localmoves
}

void printState() {
    for (Adx objptr: StateList) {
        printf ("Screen %d:\n", objptr.n);
        State& obj = *objptr;
        for (int i=0; i<19; ++i) {
            for (int j=0; j<19; ++j) {
                if (i%2 == 0 && j%2 == 0) {
                    printf ("    ");
                } else if (i%2 && j%2==0) {
                    int v = obj.val[i/2*10+j/2];
                    printf (v==255?"\033[40;36m%4d\033[0m":"\033[40;37m%4d\033[0m", v);
                } else if (i%2==0 && j%2) {
                    int v = obj.val[i/2*10+j/2+100];
                    printf (v==255?"\033[40;36m%4d\033[0m":"\033[40;37m%4d\033[0m", v);
                } else if (i%2 && j%2) {
                    int v = obj.tile[i/2*10+j/2+10];
                    printf (v==117?"\033[40;36m%4d\033[0m":"\033[40;35m%4d\033[0m", v);
                }
            }
            putchar ('\n');
        }
    }
}

void modify(Adx ps, int p, int v) {
    State& s = *ps;
    s.val[p] = v;
    bitset128& w = (*ps).activeStates;
    actList.push_back(ps);
    if (p > 99) {
        w.b.set(p-100);
        w.b.set(p-90);
    } else  {
        w.b.set(p+10);
        w.b.set(p+9);
    } 
}

