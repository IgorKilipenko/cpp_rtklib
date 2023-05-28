#pragma once

#include <ctime>
#include <cstddef>
#include <string>

namespace common::datetime {
    /// time struct
    typedef struct {
        /// time (s) expressed by standard time_t
        std::time_t time;
        /// fraction of second under 1 s
        double sec;
    } gtime_t;

    static double timeoffset_ = 0.0;

    /// difference between gtime_t structs
    /// args   : gtime_t t1,t2    I   gtime_t structs
    /// return : time difference (t1-t2) (s)
    double timediff(gtime_t t1, gtime_t t2);

    /// add time to gtime_t struct
    /// args   : gtime_t t        I   gtime_t struct
    ///          double sec       I   time to add (s)
    /// return : gtime_t struct (t+sec)
    gtime_t timeadd(gtime_t t, double sec);

    /// adjust time considering week handover
    gtime_t adjweek(gtime_t t, gtime_t t0);

    /// adjust time considering week handover
    gtime_t adjday(gtime_t t, gtime_t t0);

    /// convert calendar day/time to gtime_t struct
    /// args   : double *ep       I   day/time {year,month,day,hour,min,sec}
    /// return : gtime_t struct
    /// notes  : proper in 1970-2037 or 1970-2099 (64bit time_t)
    gtime_t epoch2time(const double *ep);

    /// convert gtime_t struct to calendar day/time
    /// args   : gtime_t t        I   gtime_t struct
    ///          double *ep       O   day/time {year,month,day,hour,min,sec}
    /// return : none
    /// notes  : proper in 1970-2037 or 1970-2099 (64bit time_t)
    void time2epoch(gtime_t t, double *ep);

    /// get current time in utc
    /// args   : none
    /// return : current time in utc
    gtime_t timeget(void);

    /// time string for ver.3 (yyyymmdd hhmmss UTC)
    static void timestr_rnx(char *str) {
        gtime_t time;
        double ep[6];
        time = timeget();
        time.sec = 0.0;
        time2epoch(time, ep);
        sprintf(str, "%04.0f%02.0f%02.0f %02.0f%02.0f%02.0f UTC", ep[0], ep[1], ep[2], ep[3], ep[4], ep[5]);
    }
}