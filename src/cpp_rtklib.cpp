#include "cpp_rtklib.h"
#include <iostream>
#include "rinex_c.h"
#include "rinex/tests/tests.h"

void hello() {
    std::cout << "Hello" << std::endl;
}

namespace rinex {
    void TestRinex() {
        //sat2code();
        tests::Test_timeget();
    }
}