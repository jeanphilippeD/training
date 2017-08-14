//
// Demo writting function object equivalent to lambda
//

#include "assert.h"
#include <iostream>
#include <string>

void Test()
{
    // lambda:
    const auto l1 = []() { std::cout << "lambda"; };
    l1();

    // function object:
    struct OurLambda
    {
        void operator()() const
        {
            std::cout << "Our lambda";
        };
    };
    OurLambda l2;
    l2();
}


void TestNullary()
{
    // lambda:
    const auto l1 = []() { return "lambda"; };
    std::cout << l1();

    // function object:
    struct OurLambda
    {
        const char* operator()() const
        {
            return "Our lambda";
        };
    };
    OurLambda l2;
    std::cout << l2();
}

void TestUnary()
{
    // lambda:
    const auto l1 = [](std::string str) { return str; };
    std::cout << l1( "lambda" );

    // function object:
    struct OurLambda
    {
        std::string operator()( std::string str) const
        {
            return str;
        };
    };
    OurLambda l2;
    std::cout << l2("lambda2");
}

struct Ident
{
    template< typename T >
    T operator()( T val ){ return val; }
};

void TestUnaryTempl()
{
    // lambda:
    auto l1 = [](auto val){ return val; };
    std::cout << l1("lambda");
    std::cout << l1(1);

    // function object:
    std::cout << Ident()("Our lambda");
    std::cout << Ident()(2);
}


void TestNullaryClosure()
{
    // lambda:
    std::string val ( "lambda" );
    auto        l1 = [val]() { return val; };
    std::cout << l1();

    // function object:
    struct OurLambda
    {
        OurLambda( std::string val ) : m_val( val )
        {}

        std::string operator()() const
        {
            return m_val;
        };

        std::string m_val;
    };
    std::string val2 ( "Our lambda" );
    OurLambda l2( val2 );
    std::cout << l2();
}


void TestNullaryClosureReference()
{
    // lambda:
    std::string val ( "lambda" );
    auto        l1 = [&val]() { val += "Mod"; };
    l1();
    std::cout << val;

    // function object:
    struct OurLambda
    {
        OurLambda( std::string& val ) : m_val( val )
        {}

        void operator()() const
        {
            m_val += "mod";
        };

        std::string& m_val;
    };
    std::string val2 ( "Our lambda" );
    OurLambda l2( val2 );
    l2();
    std::cout << val2;
}

template< typename T1, typename T2, typename T3 >
struct Overload3Impl : T1, T2, T3
{
    Overload3Impl( T1 fun1, T2 fun2, T3 fun3 )
    : T1( fun1 ), T2( fun2 ), T3( fun3 )
    {
    }

    using T1::operator();
    using T2::operator();
    using T3::operator();
};

template< typename T1, typename T2, typename T3 >
Overload3Impl< T1, T2, T3 > Overload3( T1 fun1, T2 fun2, T3 fun3 )
{
    return Overload3Impl< T1, T2, T3 >( fun1, fun2, fun3 );
}

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0051r0.pdf std::overload
// http://fit.readthedocs.io/en/latest/include/fit/match.html?highlight=overload fit::match
void TestOverloadedClosures()
{
   // lambda:
   std::string val( "lambda" );
   auto l1 = Overload3( // std::overload(
       [val](){ return val; },
       [val]( std::string str ){ return val + str; },
       [val]( int i ){ return val + ( i == 1 ? "one" : "notOne" ); }
      );
  std::cout << l1() << ", " << l1( "Str" ) << l1( 1 );

  // function object:
  struct Func
  {
      Func( const std::string val ) : m_val( val ) {}
      std::string operator()(){ return m_val; }
      std::string operator()( const char* str ){ return m_val + str; }
      std::string operator()( int i ){ return i == 0 ? "zero" : "non zero"; }

  private:
      std::string m_val;
  };
  std::string val2( "Our lambda" );
  auto l2 = Func( val2 );
  std::cout << l2() << ", " << l2( "Str" ) << ", " << l2( 1 );
}


#define RUN( name ) std::cout << "Run: " << #name << "\n" ; name() ; std::cout << "\n"

int main(int argc, char* argv[])
{
    RUN( Test );
    RUN( TestNullary );
    RUN( TestNullaryClosure );
    RUN( TestNullaryClosureReference );
    RUN( TestUnary );
    RUN( TestUnaryTempl );
    RUN( TestOverloadedClosures );
    return 0;
}
