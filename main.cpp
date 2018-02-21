#include <iostream>
#include "cpu.h"

using namespace std;

int main (int argc, char *argv[])
{
    if (argc != 2){
        cout << "Wrong number of argument: 1 is required but " << argc-1 << " were given" << endl;
        return 1;
    }

    Cpu cpu(argv[1]);

    return 0;
}
