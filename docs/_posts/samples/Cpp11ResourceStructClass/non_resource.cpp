// cpp11_vs2017.cpp : Defines the entry point for the console application.
//

#include "catch.hpp"
#include <string>

namespace {
struct StructTest1
{
    std::string m_strValue;
    int m_intValue = 0;
};
} // namespace

TEST_CASE( "Use StructTest1 Non-Resource", "[struct-non-resource]" )
{
    StructTest1 t1;
    CHECK( t1.m_strValue == std::string() );
    CHECK( t1.m_intValue == 0 );
}


TEST_CASE( "Build StructTest1 Non-Resource", "[struct-non-resource]" )
{
    StructTest1 t1{ "aa", 12 }; // GCCC 4.8 in C++11 issue
    CHECK( t1.m_strValue == std::string{"aa"} );
    CHECK( t1.m_intValue == 12 );
}


namespace {
class classTest1
{
public:
    classTest1() = default;

    explicit classTest1( const std::string& strVal )
    : m_strValue{ strVal }
    {
    }

    classTest1( const std::string& strVal, int intVal )
    : m_strValue{ strVal }, m_intValue{ intVal }
    {
    }

    const std::string& StrValue() const
    {
        return m_strValue;
    }

    int IntValue() const
    {
        return m_intValue;
    }
private:
    std::string m_strValue;
    int m_intValue = 0;
};
} // namespace

classTest1 Id( const classTest1& cl )
{
    return cl;
}

TEST_CASE( "Use classTest1 Non-Resource", "[struct-non-resource]" )
{
    classTest1 t1;
    CHECK( t1.StrValue() == std::string() );
    CHECK( t1.IntValue() == 0 );
}

TEST_CASE( "Build classTest1 Non-Resource", "[struct-non-resource]" )
{
    classTest1 t1{ "aa", 12 };
    CHECK( t1.StrValue() == std::string("aa") );
    CHECK( t1.IntValue() == 12 );
}


TEST_CASE( "Use in fct classTest1 - 1 Non-Resource", "[struct-non-resource]" )
{
    auto t1 = Id( classTest1{} );
    CHECK( t1.StrValue() == std::string() );
    CHECK( t1.IntValue() == 0 );
}


TEST_CASE( "Use in fct classTest1 - 1b Non-Resource", "[struct-non-resource]" )
{
    auto t1 = Id( {} );
    CHECK( t1.StrValue() == std::string() );
    CHECK( t1.IntValue() == 0 );
}

TEST_CASE( "Use in fct classTest1 - 2 Non-Resource", "[struct-non-resource]" )
{
    auto t1 = Id(classTest1{ "aa", 12 });
    CHECK( t1.StrValue() == std::string("aa") );
    CHECK( t1.IntValue() == 12 );
}

TEST_CASE( "Use in fct classTest1 - 2b Non-Resource", "[struct-non-resource]" )
{
    auto t1 = Id({ "aa", 12 });
    CHECK( t1.StrValue() == std::string("aa") );
    CHECK( t1.IntValue() == 12 );
}

TEST_CASE( "Use in fct classTest1 - 3 Non-Resource", "[struct-non-resource]" )
{
    auto t1 = Id(classTest1{ "aa"});
    CHECK( t1.StrValue() == std::string("aa") );
    CHECK( t1.IntValue() == 0 );
}

//TEST_CASE( "Use in fct classTest1 - 3b Non-Resource", "[struct-non-resource]" )
//{
//    auto t1 = Id({ "aa"});
//    CHECK( t1.StrValue() == std::string("aa") );
//    CHECK( t1.IntValue() == 0 );
//}

//TEST_CASE( "Use in fct classTest1 - 3c Non-Resource", "[struct-non-resource]" )
//{
//    auto t1 = Id( std::string{ "aa" } );
//    CHECK( t1.StrValue() == std::string("aa") );
//    CHECK( t1.IntValue() == 0 );
//}
