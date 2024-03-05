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
        //obs_t obs;
        //nav_t nav;
        //sta_t sta;
        //readrnx("./1000251B.23O", 0, "", &obs, &nav, &sta );
        tests::Test_timeget();
    }
}