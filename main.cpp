#include <unistd.h>
#include <time.h>
#include <string.h>

#include "states.cpp"

#define DesignChoose 4
#if DesignChoose == 1
Design mainDesign(
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, BeltNE | SEW, TransIncr | Wgg, Dup | WNS, BeltWE | Wgg, BeltNE | WSN, Empty, Empty, 
    Empty, Empty, BeltWE | Sgg, Empty, Empty, Empty, BeltWE | Ngg, Empty, Empty, 
    BeltWE, BeltWE, BeltWNE, BeltWE, Dup | ENS,  Dup | ENS, Dup | ESN, BeltWE, BeltWE, 
    Empty, Empty, Empty, BeltNE | SEW, Switch | SEW, BeltWE | Sgg, Empty, Empty, Empty, 
    Empty, Empty, Empty, BeltWE | Sgg, BeltNE | NEW, BeltNE | WNS, Empty, Empty, Empty, 
    Empty, Empty, Empty, BeltWE | Sgg, BeltWE | Sgg, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, BeltNE | ENS, BeltWNSE | Sgg, Empty, Empty, Empty, Empty,
    0, 1, 1, 0);
#elif DesignChoose == 2
Design mainDesign(
    Empty, Empty, Empty, Empty, BeltWE | Sgg, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, BeltWE | Sgg, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, BeltWE | Sgg, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, BeltWE | Sgg, Empty, Empty, Empty, Empty, 
    BeltWE, {Ngg, mainDesign}, BeltWE, BeltWE, BeltWE_NS, BeltWE, BeltWE, BeltWE, BeltWE, 
    Empty, Empty, Empty, Empty, BeltWE | Sgg, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, BeltWE | Sgg, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, BeltWE | Sgg, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, BeltWE | Sgg, Empty, Empty, Empty, Empty, 
    0, 1, 1, 0);
#elif DesignChoose == 3
Design mainDesign(
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    BeltNE | ESN, BeltNE | SWE, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    BeltWNE | NEW, BeltNE | WNS, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Filter0 | ESN, TransDecr, Dup, mainDesign, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, {Sgg, mainDesign}, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    0, 1, 1, 0);
#elif DesignChoose == 4
Design mainDesign(
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    BeltWE, BeltWE, BeltWE, BeltWE, mainDesign, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    0, 1, 1, 0);
#endif
    
Design baseDesign(
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, BeltWE | SEW, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, BeltWE | SEW, Empty, Empty, Empty, Empty, 
    Empty, Empty, BeltWE, BeltWE, mainDesign, BeltWE, BeltWE, Empty, Empty, 
    Empty, Empty, Empty, Empty, BeltWE | SEW, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, BeltWE | SEW, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, LockClose, Empty, Empty, Empty, Empty, 
    Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
    0, 0, 0, 0);

size_t physical_memory_used_by_process()
{
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != nullptr) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            int len = strlen(line);

            const char* p = line;
            for (; std::isdigit(*p) == false; ++p) {}

            line[len - 3] = 0;
            result = atoi(p);

            break;
        }
    }

    fclose(file);

    return result;
}

int main() {
    Adx base = summon (baseDesign, 0);
    modify (base, 44, 23);
    printState();
    //while (1) { usleep(500000);
    #if 0
    while (getchar()>0) {
        printf ("\033c");
        step();
        printState();
    }
    #else
    for (int i=0; i<100; ++i) {
        clock_t clk = clock();
        for (int j=0; j<10000; ++j) step();
        printf ("Step %4d: %8d us %10lld KB %10lldKB\n", i, clock() - clk, StateLen * sizeof(void*)/1024, physical_memory_used_by_process());
    }
    //getchar();
    #endif
}
