#include <assert.h>

#include <chrono>
#include <complex>
#include <iostream>

#include "../common/common.h"
#include "../common/date.h"
#include "./tests.h"

namespace rinex::tests {
    /*common::datetime::gtime_t GetTime() {
        auto currently_time = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
        std::chrono::duration millis_since_utc_epoch = currently_time.time_since_epoch();
        const auto time = std::chrono::floor<std::chrono::seconds>(millis_since_utc_epoch);
        const auto sec = std::chrono::duration_cast<std::chrono::microseconds>(millis_since_utc_epoch - time);

        return common::datetime::gtime_t{time.count(), sec.count() * 10e-7};
    }*/

    void Test_timeget() {
        const common::datetime::Date date;

        const auto time = date.GetTime();
        const auto expected_time = common::datetime::timeget();

        assert(time.time == expected_time.time);
        assert(std::abs(time.sec - expected_time.sec) <= 10e-5);
    }
}