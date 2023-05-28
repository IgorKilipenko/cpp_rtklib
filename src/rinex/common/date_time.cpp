#include <sys/time.h>

#include <chrono>
#include <cmath>
#include <ctime>
#include <type_traits>

#include "./common.h"
#include "./date.h"

namespace common::datetime {
    double timediff(gtime_t t1, gtime_t t2) {
        return difftime(t1.time, t2.time) + t1.sec - t2.sec;
    }

    gtime_t timeadd(gtime_t t, double sec) {
        double tt;

        t.sec += sec;
        tt = std::floor(t.sec);
        t.time += (int)tt;
        t.sec -= tt;
        return t;
    }

    gtime_t adjweek(gtime_t t, gtime_t t0) {
        double tt = timediff(t, t0);
        if (tt < -302400.0)
            return timeadd(t, 604800.0);
        if (tt > 302400.0)
            return timeadd(t, -604800.0);
        return t;
    }

    gtime_t adjday(gtime_t t, gtime_t t0) {
        double tt = timediff(t, t0);
        if (tt < -43200.0)
            return timeadd(t, 86400.0);
        if (tt > 43200.0)
            return timeadd(t, -86400.0);
        return t;
    }

    gtime_t epoch2time(const double *ep) {
        const int doy[] = {1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
        gtime_t time = {0};
        int days, sec, year = (int)ep[0], mon = (int)ep[1], day = (int)ep[2];

        if (year < 1970 || 2099 < year || mon < 1 || 12 < mon)
            return time;

        /// leap year if year%4==0 in 1901-2099
        days = (year - 1970) * 365 + (year - 1969) / 4 + doy[mon - 1] + day - 2 + (year % 4 == 0 && mon >= 3 ? 1 : 0);
        sec = (int)std::floor(ep[5]);
        time.time = (time_t)days * 86400 + (int)ep[3] * 3600 + (int)ep[4] * 60 + sec;
        time.sec = ep[5] - sec;
        return time;
    }

    void time2epoch(gtime_t t, double *ep) {
        /// # of days in a month
        const int mday[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 28, 31, 30,
                            31, 30, 31, 31, 30, 31, 30, 31, 31, 29, 31, 30, 31, 30, 31, 31,
                            30, 31, 30, 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int days, sec, mon, day;

        /// leap year if year%4==0 in 1901-2099
        days = (int)(t.time / 86400);
        sec = (int)(t.time - (time_t)days * 86400);
        for (day = days % 1461, mon = 0; mon < 48; mon++) {
            if (day >= mday[mon])
                day -= mday[mon];
            else
                break;
        }
        ep[0] = 1970 + days / 1461 * 4 + mon / 12;
        ep[1] = mon % 12 + 1;
        ep[2] = day + 1;
        ep[3] = sec / 3600;
        ep[4] = sec % 3600 / 60;
        ep[5] = sec % 60 + t.sec;
    }

    gtime_t timeget(void) {
        gtime_t time;
        double ep[6] = {0};

#ifdef WIN32
        SYSTEMTIME ts;

        GetSystemTime(&ts); /* utc */
        ep[0] = ts.wYear;
        ep[1] = ts.wMonth;
        ep[2] = ts.wDay;
        ep[3] = ts.wHour;
        ep[4] = ts.wMinute;
        ep[5] = ts.wSecond + ts.wMilliseconds * 1E-3;
#else
        struct timeval tv;
        struct tm *tt;

        if (!gettimeofday(&tv, NULL) && (tt = gmtime(&tv.tv_sec))) {
            ep[0] = tt->tm_year + 1900;
            ep[1] = tt->tm_mon + 1;
            ep[2] = tt->tm_mday;
            ep[3] = tt->tm_hour;
            ep[4] = tt->tm_min;
            ep[5] = tt->tm_sec + tv.tv_usec * 1E-6;
        }
#endif
        time = epoch2time(ep);

#ifdef CPUTIME_IN_GPST /* cputime operated in gpst */
        time = gpst2utc(time);
#endif
        return timeadd(time, timeoffset_);
    }
}
