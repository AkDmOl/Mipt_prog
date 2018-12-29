#include "typeList.hpp"

//-------------------------------------------Fib func
constexpr int fib(int n)
{
    return (n == 0 || n == 1) ? 1 : fib(n-1) + fib(n-2);
}


//-------------------------------------------Lin Gen
template <class TList, template <class AtomicType, class base> class Unit, class Root = NullType>
class GenLinHier;

template <class T1, class T2, template <class, class> class Unit, class Root>
class GenLinHier<TypeList<T1, T2>, Unit, Root> :
        public Unit<T1, GenLinHier<T2, Unit, Root>>
{
public:
    using Parent = Unit<T1, GenLinHier<T2, Unit, Root>>;
    using Type = T1;
};

template <class AtomicType, template <class, class> class Unit, class Root>
class GenLinHier<MakeTypeList<AtomicType>, Unit, Root> :
        public Unit<AtomicType, Root>
{
public:
    using Parent = Unit<AtomicType, Root>;
    using Type = AtomicType;
};

template <template <class, class> class Unit, class Root>
class GenLinHier<NullType, Unit, Root> :
public Unit<NullType, Root> {};
//-------------------------------------------



//-------------------------------------------Norm Gen
template <class TList, template <class, class> class Unit, unsigned int branchIdx>
class GenFibHier;


template <class T1, class T2, template <class, class> class Unit, unsigned int branchIdx>
class GenFibHier<TypeList<T1, T2>, Unit, branchIdx> : public GenLinHier<typename SplitByN<TypeList<T1, T2>, fib(branchIdx)>::First,//public GenScatterHierarchy<T1, Unit>,
        Unit>,
                                                      public GenFibHier<typename SplitByN<TypeList<T1, T2>, fib(branchIdx)>::Last,
                                                              Unit,
                                                              fib(branchIdx+1)>
{
public:
    using TList = TypeList<T1, T2>;
    using LeftBase = GenLinHier<typename SplitByN<TypeList<T1, T2>, fib(branchIdx)>::First,//public GenScatterHierarchy<T1, Unit>,
            Unit>;
    using RightBase = GenFibHier<typename SplitByN<TypeList<T1, T2>, fib(branchIdx)>::Last,
            Unit,
            fib(branchIdx+1)>;
};

template <template <class, class> class Unit, unsigned int branchIdx>
class GenFibHier<NullType, Unit, branchIdx> {
public: using RightBase = NullType; };
//------------------------------------------------------------------------Operations

//-------------------------------------Count Len Lin Hier
template <typename T>
struct LengthLinHier {
    enum { value = LengthLinHier<typename T::Parent>::value + 1 };
};
template <>
struct LengthLinHier<NullType> {
    enum { value = 0 };
};

//-------------------------------------Len Lin Hier per branch
template <typename T, unsigned int branchIdx>
struct LengthLinHierInBranch {
    enum { value = LengthLinHierInBranch<typename T::RightBase, branchIdx-1>::value };
};
template <typename T>
struct LengthLinHierInBranch<T, 0> {
    enum { value = (LengthLinHier<typename T::LeftBase>::value-1)/2 }; //-NullType и -промежуточные GenLinHier
};


//-------------------------------------Count branches in Fib Hier
template <typename T>
struct CountBranchFibHier {
    enum { value = CountBranchFibHier<typename T::RightBase>::value + 1 };
};
template <>
struct CountBranchFibHier<NullType> {
    enum { value = 0 };
};
//------------------------------------------------------------------------
