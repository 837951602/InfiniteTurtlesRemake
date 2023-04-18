typedef unsigned uint;
typedef uint AdxSto;
typedef unsigned char Token;
typedef unsigned char Tile;
/*
    Tile
      (100)  (102)   4
     (0)10 11 12 13 14 15 16 17 18
    (10)20 21 22 23 24 25 26 27 28
    (20)30 31 32 33 34 35 36 37 38
        40 41 42 43 44 45 46 47 48
     49 50 51 52 53 54 55 56 57 58 59
        60 61 62 63 64 65 66 67 68
        70 71 72 73 74 75 76 77 78
        80 81 82 83 84 85 86 87 88
        90 91 92 93 94 95 96 97 98
                   104
*/


const Tile BeltWE = 0;
const Tile BeltWE_NS = 4;
const Tile BeltNE_WS = 8;
const Tile BeltWN_ES = 128;
const Tile TransIncr = 120;
const Tile TransDecr = 16;
const Tile TransNul = 20;
const Tile Dup = 24;
const Tile Filter0 = 32;
const Tile FilterNul = 40;
const Tile LockOpen = 48;
const Tile LockClose = 56;
const Tile LockBoth = 64;
const Tile Switch = 72;
const Tile BeltNE = 80;
const Tile BeltWNE = 88;
const Tile BeltWNSE = 96;
const Tile BeltNSE = 104;
const Tile RetBlock = 112;
const Tile Call = 116;
const Tile Empty = 117;
const Tile CallDef = 240; // In definition

const Tile Egg = 0, Sgg = 1, Wgg = 2, Ngg = 3;
const Tile ENS = 0, SEW = 1, WSN = 2, NWE = 3;
const Tile ESN = 4, SWE = 5, WNS = 6, NEW = 7;

const Token NUL = 128, EMPTY = 255;

/*
    Types
        Belt straight/cross/over/mergeLR/mergeLU/mergeLUR
        Transform +1/-1/NUL
        Dup
        Filter 0/NUL
        Lock Open/Close/Both
        Switch
        RetBlock
        (null)
        (new call)
*/


#define case4(cc) break; \
    case cc+ENS: N = _N, E = _E, S = _S, W = _W; bN = _bN, bE = _bE, bS = _bS, bW = _bW; goto case##cc; \
    case cc+SEW: N = _E, E = _S, S = _W, W = _N; bN = _bE, bE = _bS, bS = _bW, bW = _bN; goto case##cc; \
    case cc+WSN: N = _S, E = _W, S = _N, W = _E; bN = _bS, bE = _bW, bS = _bN, bW = _bE; goto case##cc; \
    case cc+NWE: N = _W, E = _N, S = _E, W = _S; bN = _bW, bE = _bN, bS = _bE, bW = _bS; case##cc:
#define case8(cc) break; \
    case cc+WNS: N = _N, E = _W, S = _S, W = _E; bN = _bN, bE = _bW, bS = _bS, bW = _bE; goto case##cc; \
    case cc+NEW: N = _E, E = _N, S = _W, W = _S; bN = _bE, bE = _bN, bS = _bW, bW = _bS; goto case##cc; \
    case cc+ESN: N = _S, E = _E, S = _N, W = _W; bN = _bS, bE = _bE, bS = _bN, bW = _bW; goto case##cc; \
    case cc+SWE: N = _W, E = _S, S = _E, W = _N; bN = _bW, bE = _bS, bS = _bE, bW = _bN; goto case##cc; \
    case4(cc);
#define case1(cc) break; \
    case cc:     N = _N, E = _E, S = _S, W = _W; bN = _bN, bE = _bE, bS = _bS, bW = _bW; 

