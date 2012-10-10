#include "Memory/Allocator.h"
//#include "Core/Ptr.h"
//#include "Core/PtrBase.h"
//#include "Util/Iterator.h"
//#include "Util/TypeTraits.h"
//#include "Util/Enumerator.h"
#include "Memory/Constructor.h"
#include "Util/Enumerator.h"
//#include "Util/Array.h"

#include <vector>

using namespace std;
using namespace Prelude;


class Test
{
public:
	Test() 
	{
		x = 2;
	}
	int x;

	void * operator new(size_t size)
	{
		cout << "new new size" << endl;
		return malloc(size);
	}

};

struct Node 
{
	Node() 
	{
		a = 5;
		b = 10;
	}
	int a, b;
};

int main()
{

	typedef Node* Type;

	Node a[10];
	Util::Enumerator<Type> e(a, a + 10);

	while (e.next()) {
		cout << e->a << endl;
		cout << e.val().b << endl;
	}
		
}


