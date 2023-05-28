#pragma once

#include <chrono>
#include <type_traits>

#include "./common.h"

namespace common::datetime {
    class Date {
    public:
        template <typename Rep, std::enable_if_t<std::chrono::__is_duration<Rep>::value, bool> = true>
        static Rep NowUtc() {
            auto currently_time = std::chrono::time_point_cast<Rep>(std::chrono::system_clock::now());
            return currently_time.time_since_epoch();
        }

        gtime_t GetTime() const {
            // auto currently_time =
            //     std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
            // std::chrono::duration millis_since_utc_epoch = currently_time.time_since_epoch();
            const auto millis_since_utc_epoch = NowUtc<std::chrono::microseconds>();
            const auto time = std::chrono::floor<std::chrono::seconds>(millis_since_utc_epoch);
            const auto sec = std::chrono::duration_cast<std::chrono::microseconds>(millis_since_utc_epoch - time);

            return common::datetime::gtime_t{time.count(), sec.count() * 10e-7};
        }
    };
}