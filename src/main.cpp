#include "cpp_rtklib.h"
#include <chrono>
#include <cmath>
#include <iostream>

int main() {
    hello();
    rinex::TestRinex();

    /*auto currently_time = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
    std::chrono::duration millis_since_utc_epoch = currently_time.time_since_epoch();
    const auto sec = std::chrono::floor<std::chrono::seconds>(millis_since_utc_epoch);
    std::cout << sec.count() << std::endl;
    std::cout << std::chrono::duration_cast<std::chrono::microseconds> (millis_since_utc_epoch - sec).count() * 10e-7 << std::endl;*/
    return 0;
}