//
#include <iostream>
using namespace std;
//
class CBase {
private:
	int field_1;
public:
	CBase(int v) : field_1( v ) {}
	int& get() { return field_1;  }
	virtual void print() {
		printf("CBase::field_1 : %d\n", field_1);
	}
};
//
int& funcRef() {
	int a = 42;
	return a;
}
//
auto main() -> int
{
	//	References
	{
		CBase m_base(-5);
		m_base.print();
		printf("CBase::get() : %d\n", m_base.get());

		int& ref = m_base.get();
		printf("ref : %d\n", ref);

		int& ref2 = funcRef();
		int b = -99;
		printf("ref2 : %d\n", ref2); //	Why is it work here?
	}

	//	R-value and L-value references
	{
		CBase a(10);
		CBase &a_ref1 = a;	//	lvalue reference
		//CBase&& a_ref2 = a;	//	rvalue reference

		//CBase& a_ref3 = CBase(11); //	Bad: Error:  non-const reference may only be bound to an lvalue
		CBase&& a_ref4 = CBase(11); //	ok:  temporary object (rvalue) and reference to it
		printf("a_ref4 : %d\n", a_ref4.get()); //	Why is it work here?
	}

	//
	{
		struct Beta {
			int mbeta;
		};

		Beta B;
		B.mbeta = -2;

		Beta refB = std::move(B);
		
		printf("Beta: %d, refB: %d\n", B.mbeta, refB.mbeta);
	}

	return 0;
}