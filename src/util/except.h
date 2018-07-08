#include <stdexcept>
#include <sstream>


#define throw_ex(type, msg) {   \
    std::ostringstream oss;         \
    oss << msg;                     \
    throw type(oss.str());          \
}
