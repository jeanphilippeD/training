// cpp11_vs2017.cpp : Defines the entry point for the console application.
//

#include "catch.hpp"
#include <map>
#include <string>

struct LifeTime;

struct Valid
{
    int m_valid = 0;
    int m_constructed = 0;
};
std::ostream& operator<<( std::ostream& os, const Valid& value )
{
    return os << "Valid{" << value.m_valid << "," << value.m_constructed << "}";
}
bool operator==( const Valid& v1, const Valid& v2 )
{
    return v1.m_valid == v2.m_valid && v1.m_constructed == v2.m_constructed;
}

static const int Destroyed = 0;
static const int Constructed = 1;

static std::map< const LifeTime*, Valid > s_live;
struct Fixture
{
    Fixture()
    {
        s_live.clear();
    }
};

struct LifeTime
{
    LifeTime()
    {
        s_live[ this ].m_valid++;
        s_live[ this ].m_constructed++;
    }

    ~LifeTime()
    {
        s_live[ this ].m_valid--;
    }

    LifeTime( const LifeTime& t ) : LifeTime()
    {
    }

    LifeTime& operator=( const LifeTime& t )
    {
    }

    Valid Check() const
    {
        return s_live[ this ];
    }
};

struct StructTest1
{
    LifeTime Get() const
    {
        return m_value;
    };
    const LifeTime& GetCRef() const
    {
        return m_value;
    };

    LifeTime m_value;
};

LifeTime GetLifeTime()
{
    char a[ 20 ]; // add padding to avoid same address
    (void)a;
    return LifeTime{};
}

StructTest1 GetStructTest1()
{
    char a[ 20 ]; // add padding to avoid same address
    (void)a;
    return StructTest1{};
}

void Check( const Valid& actual, const Valid& expected, int numLive )
{
    CHECK( actual == expected );
    CHECK( s_live.size() == numLive );
}

TEST_CASE_METHOD( Fixture, "LifeTime", "[test]" )
{
    LifeTime    t1;
    const auto& ref = t1;

    CHECK( ref.Check() == Valid{ Constructed, 1 } );
    CHECK( s_live.size() == 1 );
}

TEST_CASE_METHOD( Fixture, "From Struct ref", "[test]" )
{
    StructTest1 s1;
    const auto& ref = s1.GetCRef();

    CHECK( ref.Check() == Valid{ Constructed, 1 } );
    CHECK( s_live.size() == 1 );
}

TEST_CASE_METHOD( Fixture, "From Struct copy", "[test]" )
{
    StructTest1 s1;
    const auto& ref = s1.Get();

    CHECK( ref.Check() == Valid{ Constructed, 1 } );
    CHECK( s_live.size() == 2 );
}

TEST_CASE_METHOD( Fixture, "temporary LifeTime", "[test]" )
{
    const auto& ref = LifeTime{};

    CHECK( ref.Check() == Valid{ Constructed, 1 } );
    CHECK( s_live.size() == 1 );
}

TEST_CASE_METHOD( Fixture, "temporary From Struct ref", "[test]" )
{
    const auto& ref = StructTest1{}.GetCRef();

    CHECK( ref.Check() == Valid{ Destroyed, 1 } ); // use after free
    CHECK( s_live.size() == 1 );
}

TEST_CASE_METHOD( Fixture, "temporary From Struct copy", "[test]" )
{
    const auto& ref = StructTest1{}.Get();

    CHECK( ref.Check() == Valid{ Constructed, 1 } );
    CHECK( s_live.size() == 2 );
}

TEST_CASE_METHOD( Fixture, "temporary From Struct bound ref", "[test]" )
{
    const auto& s1 = StructTest1{};
    const auto& ref = s1.GetCRef();

    CHECK( ref.Check() == Valid{ Constructed, 1 } );
    CHECK( s_live.size() == 2 );
}

TEST_CASE_METHOD( Fixture, "temporary From Struct bound copy", "[test]" )
{
    const auto& s1 = StructTest1{};
    const auto& ref = s1.Get();

    CHECK( ref.Check() == Valid{ Constructed, 1 } );
    CHECK( s_live.size() == 3 );
}

TEST_CASE_METHOD( Fixture, "returned temporary LifeTime", "[test]" )
{
    const auto& ref = GetLifeTime();

    CHECK( ref.Check() == Valid{ Constructed, 1 } );
    CHECK( s_live.size() == 1 );
}

TEST_CASE_METHOD( Fixture, "returned temporary From Struct ref", "[test]" )
{
    const auto& ref = GetStructTest1().GetCRef();

    CHECK( ref.Check() == Valid{ Destroyed, 1 } ); // use after free
    CHECK( s_live.size() == 2 );
}

TEST_CASE_METHOD( Fixture, "returned temporary From Struct copy", "[test]" )
{
    const auto& ref = GetStructTest1().Get();

    CHECK( ref.Check() == Valid{ Constructed, 1 } );
    CHECK( s_live.size() == 3 );
}

TEST_CASE_METHOD(
    Fixture,
    "returned temporary From Struct bound ref",
    "[test]" )
{
    const auto& s1 = GetStructTest1();
    const auto& ref = s1.GetCRef();

    CHECK( ref.Check() == Valid{ Constructed, 1 } );
    CHECK( s_live.size() == 2 );
}

TEST_CASE_METHOD(
    Fixture,
    "returned temporary From Struct bound copy",
    "[test]" )
{
    const auto& s1 = GetStructTest1();
    const auto& ref = s1.Get();

    CHECK( ref.Check() == Valid{ Constructed, 1 } );
    CHECK( s_live.size() == 3 );
}

TEST_CASE_METHOD(
    Fixture,
    "In Expression returned temporary LifeTime",
    "[test]" )
{
    Check( GetLifeTime().Check(), Valid{ Constructed, 1 }, 1 );
}

TEST_CASE_METHOD(
    Fixture,
    "In Expression returned temporary From Struct ref",
    "[test]" )
{
    Check( GetStructTest1().GetCRef().Check(), Valid{ Constructed, 1 }, 2 );
}

TEST_CASE_METHOD(
    Fixture,
    "In Expression returned temporary From Struct copy",
    "[test]" )
{
    Check( GetStructTest1().Get().Check(), Valid{ Constructed, 1 }, 3 );
}
