#include "FibHierarchy.hpp"
#include "stdint.h"
#include <iostream>

//-------------------------------------------Default test class
template <class T, class Base>
struct EventHandler : public Base {
public:
    virtual void OnEvent() {std::cout << typeid(T).name() << "\n"; };
    using Parent = Base;
};


int main()
{
    using TL = MakeTypeList<char, int, char, bool, bool, int, int, char, int8_t, int16_t, bool>::res;//, bool, char, int16_t, int8_t, int64_t, std::string >::res;
    using WidgetInfo = GenFibHier< TL, EventHandler, 0>;
    std::cout << "Count Branches " << CountBranchFibHier<WidgetInfo>::value-1 << "\n"; //All right
    std::cout << "Count Parametrized Classes by branch_0= " << LengthLinHierInBranch<WidgetInfo, 0>::value << "\t fib_0 " <<fib(0) << "\n";
    std::cout << "Count Parametrized Classes by branch_1= " << LengthLinHierInBranch<WidgetInfo, 1>::value << "\t fib_1 " <<fib(1) << "\n";
    std::cout << "Count Parametrized Classes by branch_2= " << LengthLinHierInBranch<WidgetInfo, 2>::value << "\t fib_2 " <<fib(2) << "\n";
    std::cout << "Count Parametrized Classes by branch_3= " << LengthLinHierInBranch<WidgetInfo, 3>::value << "\t fib_3 " <<fib(3) << "\n";
    std::cout << "Count Parametrized Classes by branch_4= " << LengthLinHierInBranch<WidgetInfo, 4>::value << "\t fib_4 " <<fib(4) << "\n";
    WidgetInfo a;

    return 0;
}
