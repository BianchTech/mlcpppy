#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <variant>
#include <charconv>

// Template types
template<typename T>
using Vec = std::vector<T>;

// TYPES
using String = std::string;
using IFStream = std::ifstream;
using ValueType = std::variant<long, double, String>;

// IOSTREAM
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
