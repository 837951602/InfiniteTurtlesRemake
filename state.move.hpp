/*
    Input:  actstate
            state = *stateaddr
            i: actpos
    Output: actposA
            movements
            localmoves
*/
#ifdef state

int _N = i+90, _E = i-9, _S = i+100, _W = i-10;
int _bN = i-10, _bE = i+1, _bS = i+10, _bW = i-1;
int N, E, S, W, bN, bE, bS, bW;
Adx tmp;
#define move(src, dst, ...) \
    (localmoves.emplace_back (src, i, EMPTY), 0), \
    localmoves.emplace_back (dst, i, __VA_ARGS__ (state.val[src])), \
    actposA.b.set(b##src), actposA.b.set(b##dst) // , printf("Moving %d %d\n", src, dst)
//printf ("Handleing %d %d\n", i, state.tile[i]);
switch (state.tile[i]) {
case4 (BeltWE)
    if (state.val[W] != EMPTY && state.val[E] == EMPTY) {
        move (W, E);
    }
case8 (BeltNE)
    if (state.val[N] != EMPTY && state.val[E] == EMPTY) {
        move (N, E);
    }
case4 (BeltWE_NS)
    if (state.val[W] != EMPTY && state.val[E] == EMPTY) {
        move (W, E);
    }
    if (state.val[N] != EMPTY && state.val[S] == EMPTY) {
        move (N, S);
    }
case8 (BeltNE_WS)
    if (state.val[N] != EMPTY && state.val[E] == EMPTY) {
        move (N, E);
    }
    if (state.val[W] != EMPTY && state.val[S] == EMPTY) {
        move (W, S);
    }
case8 (BeltWN_ES)
    if (state.val[W] != EMPTY && state.val[N] == EMPTY) {
        move (W, N);
    }
    if (state.val[E] != EMPTY && state.val[S] == EMPTY) {
        move (E, S);
    }
case8 (BeltWNE)
    if (state.val[E] == EMPTY) {
        if (state.val[W] != EMPTY) move (W, E); else
        if (state.val[N] != EMPTY) move (N, E);
    }
case8 (BeltNSE)
    if (state.val[E] == EMPTY) {
        if (state.val[N] != EMPTY) move (N, E); else
        if (state.val[S] != EMPTY) move (S, E);
    }
case8 (BeltWNSE)
    if (state.val[E] == EMPTY) {
        if (state.val[W] != EMPTY) move (W, E); else
        if (state.val[N] != EMPTY) move (N, E); else
        if (state.val[S] != EMPTY) move (S, E);
    }
case4 (TransIncr)
    if (state.val[W] != EMPTY && state.val[E] == EMPTY) {
        move (W, E, [](Token i){return i<100?i+1:i;});
    }
case4 (TransDecr)
    if (state.val[W] != EMPTY && state.val[E] == EMPTY) {
        move (W, E, [](Token i){return (signed char)i>0?i-1:i;});
    }
case4 (TransNul)
    if (state.val[W] != EMPTY && state.val[E] == EMPTY) {
        move (W, E, [](Token i){return i&128?i^EMPTY^NUL:i;});
    }
case8 (Dup) 
    if (state.val[W] != EMPTY && state.val[E] == EMPTY && state.val[S] == EMPTY) {
        move (W, E);
        sizeof move (W, S); // Not moving first
    }
case8 (Filter0)
    if (state.val[W] != EMPTY && state.val[E] == EMPTY && state.val[S] == EMPTY) {
        if (state.val[W]==0) move (W, S); else move (W, E); 
    }
case8 (FilterNul)
    if (state.val[W] != EMPTY && state.val[E] == EMPTY && state.val[S] == EMPTY) {
        if (state.val[W]==NUL) move (W, S); else move (W, E); 
    }
case8 (LockOpen)
    if (state.val[W] != EMPTY && state.val[E] == EMPTY) {
        move (W, E);
        state.tile[i] += LockClose - LockOpen;
    }
case8 (LockClose)
    if (state.val[N] != EMPTY) {
        localmoves.emplace_back (N, i, EMPTY);
        actposA.b.set(bN);
        state.tile[i] -= LockClose - LockOpen;
    }
case8 (LockBoth)
    static const int FlipXY[8] = {5,6,7,4,1,2,3,0};
    if (state.val[W] != EMPTY && state.val[E] == EMPTY) {
        move (W, E);
        state.tile[i] = LockBoth + FlipXY[state.tile[i]-LockBoth];
    }
case8 (Switch)
    if (state.val[W] != EMPTY && state.val[S] == EMPTY) {
        move (W, S);
    }
    if (state.val[E] != EMPTY) {
        localmoves.emplace_back (E, i, EMPTY);
        actposA.b.set(bE);
        actposA.b.set(i);
        state.tile[i] ^= 4;
    }
case4 (RetBlock) {
    static const int retDirect[4][8] = {
        { -9, 100, -10,  90,  -9, 100, -10,  90},
        {100, -10,  90,  -9,  90,  -9, 100, -10},
        {-10,  90,  -9, 100, -10,  90,  -9, 100},
        { 90,  -9, 100, -10, 100, -10,  90,  -9}
    }; 
    static const int bretDirect[4][8] = {
        {  1,  10,  -1, -10,   1,  10,  -1, -10},
        { 10,  -1, -10,   1, -10,   1,  10,  -1},
        { -1, -10,   1,  10,  -1, -10,   1,  10},
        {-10,   1,  10,  -1,  10,  -1, -10,   1}
    };
    int ptp = state.parentpos + retDirect[state.tile[i]-RetBlock][state.direction]; // parentTokenPos
    if (state.val[W]!=EMPTY && (*(state.parent)).val[ptp]==EMPTY) {
        localmoves.emplace_back (W, i, EMPTY);
        (*(state.parent)).movements.emplace_back (ptp, state.parentpos, state.val[W]);
        actposA.b.set(bW);
        (*(state.parent)).activeStatesA.b.set(state.parentpos + bretDirect[state.tile[i]-RetBlock][state.direction]);
    }
}
case1 (Empty)
case1 (Call) {
    state.tile[i] = ~state.extraCnt;
    tmp = summon (*(design.extra[i]), actstate, i, design.tile[i]-CallDef);
    // &state change here
    stateaddr = &*(actstate);
    localmovesptr = &(state.movements);
    state.extra[state.extraCnt++] = tmp;
}   // fall
    if (0) {
default:
        tmp = state.extra[255 & ~state.tile[i]];
    }
        switch ((*tmp).direction) {
            static const int zero = 0;
            case8 (zero) ;
        }
    State& dst = *tmp;
    actList.push_back(tmp);
    vectorMovement& remotemoves = dst.movements;
    bitset128& remoteposA = dst.activeStatesA;
#undef move
#define move(src, dst, bdst) \
    localmoves.emplace_back (src, i, EMPTY), \
    remotemoves.emplace_back (dst, i, (state.val[src])), \
    actposA.b.set(b##src), remoteposA.b.set(bdst)
    if (state.val[N] != EMPTY && dst.tile[4] == BeltWE+Sgg && dst.val[104] == EMPTY) 
        move(N, 104, 14);
    if (state.val[E] != EMPTY && dst.tile[59] == BeltWE+Wgg && dst.val[49] == EMPTY) 
        move(E, 49, 58);
    if (state.val[S] != EMPTY && dst.tile[104] == BeltWE+Ngg && dst.val[194] == EMPTY) 
        move(S, 194, 94);
    if (state.val[W] != EMPTY && dst.tile[49] == BeltWE+Egg && dst.val[40] == EMPTY)
        move(W, 40, 50);
#undef move
}
if (design.throws[N] && state.val[N]!=EMPTY) localmoves.emplace_back (N, 255, EMPTY);
if (design.throws[E] && state.val[E]!=EMPTY) localmoves.emplace_back (E, 255, EMPTY);
if (design.throws[W] && state.val[W]!=EMPTY) localmoves.emplace_back (W, 255, EMPTY);
if (design.throws[S] && state.val[S]!=EMPTY) localmoves.emplace_back (S, 255, EMPTY);
#else
#endif

