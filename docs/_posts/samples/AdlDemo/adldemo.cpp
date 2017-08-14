//
// Demo using ADL to write to a log file
//

#include <iostream>
#include <string>
#include <vector>

namespace geo {
struct Position
{
    Position( int position ) : m_position( position ) {}
    int m_position;
};

std::ostream& operator<<( std::ostream& os, const Position& pos )
{
    return os << "Pos(" << pos.m_position << ")";
}

std::ostream& operator<<( std::ostream& os, const std::vector< Position >& positions )
{
    for( auto& pos : positions )
    {
        os << pos << ", ";
    }
    return os;
}
} // namespace geo

class Dog
{
};

std::ostream& operator<<( std::ostream& os, const Dog& dog )
{
    return os << "Wooof woof";
}

std::ostream& operator<<( std::ostream& os, const std::vector< Dog >& dogs )
{
    for( auto& dog : dogs )
    {
        os << dog << ", ";
    }
    return os;
}

namespace forlog {
struct Wrapper
{
    Wrapper( std::vector< int > vals ) : m_vals( vals ) {}
    std::vector< int > m_vals;
};

std::ostream& operator<<( std::ostream& os, const Wrapper& integers )
{
    for( auto& integer : integers.m_vals )
    {
        os << integer << ", ";
    }
    return os;
}
} // namespace forlog

namespace log {
void RunTest()
{
  geo::Position position( 20 );
  std::vector< geo::Position > positions = { 10, 30, 50 };

  std::vector< int > integers = { 10, 30, 50 };

  Dog dog;
  std::vector< Dog > dogs( 20 );

  std::cout << "A trace severity message" << '\n';
  std::cout << dog << " " << position << '\n';

  std::cout << positions << '\n';
  std::cout << dogs << '\n';

  std::cout << forlog::Wrapper( integers ) << '\n';
}
} // namespace log

int main(int argc, char* argv[])
{
  log::RunTest();
  return 0;
}
