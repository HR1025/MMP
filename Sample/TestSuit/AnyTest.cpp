#include "AnyTest.h"

#include <cassert>
#include <string>
#include <vector>

#include "Common/Any.h"

namespace Mmp
{

class SomeClass
{
public:
	int i;
	std::string str;
	SomeClass(int h, std::string s): i (h), str(s)
	{
	};
	bool operator==(const SomeClass& other) const
	{
		return i == other.i && str == other.str;
	}
};

void testAnyDefaultCtor()
{
	const Any value;
	assert(value.empty());
	assert(0 == AnyCast<int>(&value));
	assert(value.type() == typeid(void));
}


void testAnyConvertingCtor()
{
	std::string text = "test message";
	Any value = text;

	assert(!value.empty());
	assert(value.type() == typeid(std::string));
	assert(0 == AnyCast<int>(&value));
	assert(0 != AnyCast<std::string>(&value));
	assert(AnyCast<std::string>(value) == text);
	assert(AnyCast<std::string>(&value) != &text);
}


void testAnyCopyCtor()
{
	std::string text = "test message";
	Any original = text, copy = original;

	assert(!copy.empty());
	assert(original.type() == copy.type());
	assert(AnyCast<std::string>(original) == AnyCast<std::string>(copy));
	assert(text == AnyCast<std::string>(copy));
	assert(AnyCast<std::string>(&original) != AnyCast<std::string>(&copy));
}


void testAnyCopyAssign()
{
	std::string text = "test message";
	Any original = text, copy;
	Any* assignResult = &(copy = original);

	assert(!copy.empty());
	assert(original.type() == copy.type());
	assert(AnyCast<std::string>(original) == AnyCast<std::string>(copy));
	assert(text == AnyCast<std::string>(copy));
	assert(AnyCast<std::string>(&original) != AnyCast<std::string>(&copy));
	assert(assignResult == &copy);

	// test self assignment
	Any& ref = original;
	original = ref;
	assert(AnyCast<std::string>(original) == AnyCast<std::string>(copy));
	original = original;
	assert(AnyCast<std::string>(original) == AnyCast<std::string>(copy));
}


void testAnyConvertingAssign()
{
	std::string text = "test message";
	Any value;
	Any* assignResult = &(value = text);

	assert(!value.empty());
	assert(value.type() == typeid(std::string));
	assert(0 == AnyCast<int>(&value));
	assert(0 != AnyCast<std::string>(&value));
	assert(AnyCast<std::string>(value) == text);
	assert(AnyCast<std::string>(&value) != &text);
	assert(assignResult == &value);
}


void testAnyCastToReference()
{
	Any a(137);
	const Any b(a);

	int&                ra    = AnyCast<int &>(a);
	int const&          ra_c  = AnyCast<int const &>(a);
	// NOTE: The following two AnyCasts will trigger the
	// undefined behavior sanitizer.
	int volatile&       ra_v  = AnyCast<int volatile &>(a);
	int const volatile& ra_cv = AnyCast<int const volatile&>(a);

	// cv references to same obj
	assert(&ra == &ra_c && &ra == &ra_v && &ra == &ra_cv);

	int const &          rb_c  = AnyCast<int const &>(b);
	int const volatile & rb_cv = AnyCast<int const volatile &>(b);

	assert(&rb_c == &rb_cv); // cv references to copied const obj
	assert(&ra != &rb_c); // copies hold different objects

	++ra;
	int incremented = AnyCast<int>(a);
	assert(incremented == 138); // increment by reference changes value
}


void testAnyEmptyCopy()
{
	const Any null;
	Any copied = null, assigned;
	assigned = null;

	assert(null.empty());
	assert(copied.empty());
	assert(assigned.empty());
}


void testAnyInt()
{
	Any e;
	assert(e.empty());
	e = 0;
	assert(!e.empty());

	Any a = 13;
	assert(a.type() == typeid(int));
	int* i = AnyCast<int>(&a);
	assert(*i == 13);
	Any b = a;
	assert(b.type() == typeid(int));
	int *cpyI = AnyCast<int>(&b);
	assert(*cpyI == *i);
	*cpyI = 20;
	assert(*cpyI != *i);
	std::string* s = AnyCast<std::string>(&a);
	assert(s == NULL);

	int tmp = AnyCast<int>(a);
	const Any c = a;
	tmp = AnyCast<int>(a);
}


void testAnyComplexType()
{
	SomeClass str(13,std::string("hello"));
	Any a = str;
	Any b = a;
	assert(a.type() == typeid(SomeClass));
	assert(b.type() == typeid(SomeClass));
	SomeClass str2 = AnyCast<SomeClass>(a);
	assert(str == str2);
	const SomeClass& strCRef = RefAnyCast<SomeClass>(a);
	assert(str == strCRef);
	SomeClass& strRef = RefAnyCast<SomeClass>(a);
	assert(str == strRef);
}


void testAnyVector()
{
	std::vector<int> tmp;
	tmp.push_back(1);
	tmp.push_back(2);
	tmp.push_back(3);
	Any a = tmp;
	assert(a.type() == typeid(std::vector<int>));
	std::vector<int> tmp2 = AnyCast<std::vector<int> >(a);
	assert(tmp2.size() == 3);
	const std::vector<int>& vecCRef = RefAnyCast<std::vector<int> >(a);
	std::vector<int>& vecRef = RefAnyCast<std::vector<int> >(a);

	assert(vecRef[0] == 1);
	assert(vecRef[1] == 2);
	assert(vecRef[2] == 3);
	vecRef[0] = 0;
	assert(vecRef[0] == vecCRef[0]);
}

void AnyTest()
{
	// see Extension/poco/Foundation/testsuite/src/AnyTest.h(Poco) for more information
    testAnyDefaultCtor();
    testAnyConvertingCtor();
    testAnyCopyCtor();
    testAnyCopyAssign();
    testAnyConvertingAssign();
    testAnyCastToReference();
    testAnyEmptyCopy();
    testAnyInt();
    testAnyComplexType();
    testAnyVector();
}

} // namespace Mmp