#include "Memory/allocator.h"
#include "Core/Ptr.h"
using namespace pl::Memory;
using namespace pl::Core;

int main(int argc, char** argv) {
	Allocator allocator;
    allocator.allocate();
    Ptr<int> ptr;

    return 0;
}

