#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

namespace rinex {
    /// max number of obs type in RINEX
    constexpr size_t MAXOBSTYPE = 64;

    /// signal index type
    typedef struct {
        /// number of index
        int n;
        /// signal freq-index
        int idx[MAXOBSTYPE];
        /// signal index in obs data (-1:no)
        int pos[MAXOBSTYPE];
        /// signal priority (15-0)
        uint8_t pri[MAXOBSTYPE];
        /// type (0:C,1:L,2:D,3:S)
        uint8_t type[MAXOBSTYPE];
        /// obs-code (CODE_L??)
        uint8_t code[MAXOBSTYPE];
        /// phase shift (cycle)
        double shift[MAXOBSTYPE];
    } sigind_t;

    /// set string without tail space
    void setstr(char *dst, const char *src, int n);
}

namespace rinex {
    /// satellite systems navsys in RTKLIB
    /// SYS_GPS,SYS_GLO,SYS_GAL,SYS_QZS,SYS_SBS,SYS_CMP,SYS_IRN,0
    enum class SatelliteSystemNames { SYS_GPS = 0, SYS_GLO, SYS_GAL, SYS_QZS, SYS_SBS, SYS_CMP, SYS_IRN, SYS_UNKNOW };

    struct SatelliteSystem {
        SatelliteSystemNames name;
        char code;
    };

    /*struct Hasher {
        size_t operator()(const SatelliteSystem& val) const {
            return std::hash<SatelliteSystem>
        }
    }*/

    class SatelliteSystems : public std::unordered_map<SatelliteSystemNames, char> {
    private:
        using super = std::unordered_map<SatelliteSystemNames, char>;

    public:
        // using std::unordered_map<SatelliteSystemNames, char>::unordered_map;
        using const_iterator = std::unordered_map<SatelliteSystemNames, char>::const_iterator;
        SatelliteSystems()
            : super(
                  {{SatelliteSystemNames::SYS_GPS, 'S'},
                   {SatelliteSystemNames::SYS_GLO, 'R'},
                   {SatelliteSystemNames::SYS_GAL, 'E'},
                   {SatelliteSystemNames::SYS_QZS, 'J'},
                   {SatelliteSystemNames::SYS_SBS, 'S'},
                   {SatelliteSystemNames::SYS_CMP, 'C'},
                   {SatelliteSystemNames::SYS_IRN, 'I'}}) {}

        char operator[](const SatelliteSystemNames &key) const {
            return super::at(key);
        }

        const_iterator begin() const {
            return super::begin();
        }

        const_iterator end() const {
            return super::end();
        }

        size_t size() const {
            return super::size();
        }
    };
}

namespace rinex {
    class Rinex {
    public:
        static std::vector<SatelliteSystemNames> AllAvailableSatelliteSystems() {
            return all_available_satellite_systems_;
        }

    public:
        Rinex() : navsys_(all_available_satellite_systems_.begin(), all_available_satellite_systems_.end()) {}

        const std::vector<SatelliteSystemNames> &GetNavSystems() const {
            return navsys_;
        }

    private:
        std::vector<SatelliteSystemNames> navsys_;

        inline static const std::vector<SatelliteSystemNames> all_available_satellite_systems_{
            {SatelliteSystemNames::SYS_GPS, SatelliteSystemNames::SYS_GLO, SatelliteSystemNames::SYS_GAL,
             SatelliteSystemNames::SYS_QZS, SatelliteSystemNames::SYS_SBS, SatelliteSystemNames::SYS_CMP,
             SatelliteSystemNames::SYS_IRN}};
        /// satellite system codes
        inline static const std::string syscodes{"GREJSCI"};

        /// observation type codes
        inline static const std::string obscodes{"CLDS"};

        /// RAa values (ref [3] 20.3.3.3.1.1)
        inline static const double ura_eph[] = {2.4,  3.4,   4.85,  6.85,  9.65,   13.65,  24.0,   48.0,
                                                96.0, 192.0, 384.0, 768.0, 1536.0, 3072.0, 6144.0, 0.0};
        /// URA nominal values
        inline static const double ura_nominal[] = {2.0,  2.8,   4.0,   5.7,   8.0,    11.3,   16.0,   32.0,
                                                    64.0, 128.0, 256.0, 512.0, 1024.0, 2048.0, 4096.0, 8192.0};
    };
}