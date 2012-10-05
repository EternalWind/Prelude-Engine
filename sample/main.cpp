#include "Memory\allocator.h"
#include "Core/refcore.h"
using namespace pl::Memory;


int main(int argc, char** argv) {
	Allocator allocator;
    allocator.allocate();

    return 0;
}

