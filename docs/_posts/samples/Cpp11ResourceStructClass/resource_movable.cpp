#include "catch.hpp"
#include <string>

namespace {
class ResourceTest1
{
public:
    ResourceTest1() = default;
    ResourceTest1( const std::string& strValue )
    : m_strValue( new std::string( strValue ) )
    {
    }

    ResourceTest1( const ResourceTest1& other ) = delete;
    ResourceTest1& operator=( const ResourceTest1& other ) = delete;

    ResourceTest1( ResourceTest1&& other )
    {
        std::swap( m_strValue, other.m_strValue );
    }

    ResourceTest1& operator=( ResourceTest1&& other )
    {
        std::swap( m_strValue, other.m_strValue );
    }

    const std::string* StrValue() const
    {
        return m_strValue;
    }

    ~ResourceTest1()
    {
        delete m_strValue;
    }

private:
    std::string* m_strValue = nullptr;
};
} // namespace

TEST_CASE( "Use ResourceTest1 Resource-Movable", "[resource-movable]" )
{
    ResourceTest1 t1;
    CHECK( t1.StrValue() == nullptr );
}

TEST_CASE( "Use ResourceTest non own Resource-Movable", "[resource-movable]" )
{
    std::string val = "t1";
    ResourceTest1 t1{val};
    CHECK( *t1.StrValue() == val );
}

//TEST_CASE( "Use ResourceTest copy Resource-Movable", "[resource-movable]" )
//{
//    std::string val = "t1";
//    ResourceTest1 t1{val};
//    ResourceTest1 t2{ t1 };
//
//    CHECK( *t1.StrValue() == val );
//    // CHECK( t2 == t1 );
//}

TEST_CASE( "Use ResourceTest move Resource-Movable", "[resource-movable]" )
{
    std::string val = "t1";
    ResourceTest1 t1{val};
    ResourceTest1 t2{ ResourceTest1{val} };

    CHECK( *t2.StrValue() == val );
    // CHECK( t2 == t1 );
}
