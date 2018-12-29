class NullType{};

template <typename T, typename U>
struct TypeList
{
    using head = T;
    using tail = U;
};

template<typename ...>
struct MakeTypeList
{
};

template <typename T, typename ... U>
struct MakeTypeList<T,U...>
{
    using res = TypeList<T, typename MakeTypeList<U...>::res >;
};

template <>
struct MakeTypeList<>
{
    using res = NullType;
};
//------------------------------------------------------------------------------Operations with TypeList
//-------------------------------------------Len
template <typename TypeList>
struct Length {
    enum { value = Length<typename TypeList::tail>::value + 1 };
};
template <>
struct Length<NullType> {
    enum { value = 0 };
};

//-------------------------------------------TypeAt
template<typename TypeList, unsigned int i>
struct TypeAt //<MakeTypeList<Head, Tail>, i>
{
    using Result = typename TypeAt<typename TypeList::tail, i - 1>::Result;
};

template<class Head, class Tail>
struct TypeAt<TypeList<Head, Tail>, 0>
{
    using Result = Head;
};
//-------------------------------------------


//-------------------------------------------IndexOf
template<typename TypeList, class T>
struct IndexOf //<Typelist, T>
{
private:
    enum { temp = IndexOf<typename TypeList::tail, T>::value };
public:
    enum { value = temp == -1 ? -1 : 1 + temp };
};


template<class T>
struct IndexOf<NullType, T>
{
    enum { value = -1 };
};
template<class T, class Tail>
struct IndexOf<TypeList<T, Tail>, T>
{
    enum { value = 0 };
};

//-------------------------------------------

//-------------------------------------------Append
template<typename TL, typename T>
struct Append //<Typelist<Head, Tail>, T>
{
    using Result = TypeList<typename TL::head,
            typename Append<typename TL::tail, T>::Result>;
};

template<>
struct Append<NullType, NullType>
{
    using Result = NullType;
};

template<class T>
struct Append<NullType, T>
{
    using Result = TypeList<T, NullType>;
};

template<class Head, class Tail>
struct Append<NullType, TypeList<Head, Tail>>
{
    using Result = TypeList<Head, Tail>;
};

//-------------------------------------------

//-------------------------------------------Erase
template<typename TL, typename T>
struct Erase
{
    using Result = TypeList<typename TL::head,
            typename Erase<typename TL::tail, T>::Result>;
};

template<typename T>
struct Erase<NullType, T>
{
    using Result = NullType;
};

template<class T, class Head, class Tail>
struct Erase<TypeList<T, TypeList<Head, Tail>>, T>
{
    using Result = TypeList<Head, Tail>;
};
//-------------------------------------------

//-------------------------------------------Split TypeList by n
template<typename TL, unsigned int i>
struct SplitByN //<MakeTypeList<Head, Tail>, i>
{
    using First = TypeList<typename TL::head,
            typename SplitByN<typename TL::tail, i - 1>::First >;
    using Last = typename SplitByN<typename TL::tail, i - 1>::Last;
};

template<class Head, class Tail>
struct SplitByN<TypeList<Head, Tail>, 1>
{
    using First = TypeList<Head, NullType>;
    using Last = TypeList<typename Tail::head, typename Tail::tail>;
};

template<class Head, class Tail>
struct SplitByN<TypeList<Head, Tail>, 0>
{
    using First = TypeList<Head, NullType>;
    using Last = TypeList<typename Tail::head, typename Tail::tail>;
};

template<class Head>
struct SplitByN<TypeList<Head, NullType>, 1>
{
    using First = TypeList<Head, NullType>;
    using Last = NullType;
};

template<unsigned int i>
struct SplitByN<NullType, i>
{
    using First = NullType;
    using Last = NullType;
};
//-------------------------------------------
//------------------------------------------------------------------------------
