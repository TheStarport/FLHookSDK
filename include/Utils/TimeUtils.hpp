#pragma once

class TimeUtils
{
    public:
        TimeUtils() = delete;

        template <typename Duration>
            requires IsChronoDurationV<Duration>
        static Duration UnixTimeAsDuration()
        {
            return std::chrono::duration_cast<Duration>(std::chrono::system_clock::now().time_since_epoch());
        }

        template <typename Duration = std::chrono::milliseconds>
            requires IsChronoDurationV<Duration>
        static int64 UnixTime()
        {
            return static_cast<int64>(UnixTimeAsDuration<Duration>().count());
        }

        static std::chrono::sys_time<std::chrono::seconds> UnixToSysTime(const int64 time)
        {
            return std::chrono::sys_time(std::chrono::sys_seconds(std::chrono::seconds{ time }));
        }

        // Returns number of days since civil 1970-01-01.  Negative values indicate
        //    days prior to 1970-01-01.
        // Preconditions:  y-m-d represents a date in the civil (Gregorian) calendar
        //                 m is in [1, 12]
        //                 d is in [1, last_day_of_month(y, m)]
        //                 y is "approximately" in
        //                   [numeric_limits<Int>::min()/366, numeric_limits<Int>::max()/366]
        //                 Exact range of validity is:
        //                 [civil_from_days(numeric_limits<Int>::min()),
        //                  civil_from_days(numeric_limits<Int>::max()-719468)]
        template <class Int>
        static constexpr Int DaysFromCivil(Int y, unsigned m, unsigned d) noexcept
        {
            static_assert(std::numeric_limits<unsigned>::digits >= 18, "This algorithm has not been ported to a 16 bit unsigned integer");
            static_assert(std::numeric_limits<Int>::digits >= 20, "This algorithm has not been ported to a 16 bit signed integer");
            y -= m <= 2;
            const Int era = (y >= 0 ? y : y - 399) / 400;
            const unsigned yoe = static_cast<unsigned>(y - era * 400);           // [0, 399]
            const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; // [0, 365]
            const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;          // [0, 146096]
            return era * 146097 + static_cast<Int>(doe) - 719468;
        }

        // Returns year/month/day triple in civil calendar
        // Preconditions:  z is number of days since 1970-01-01 and is in the range:
        //                   [numeric_limits<Int>::min(), numeric_limits<Int>::max()-719468].
        template <class Int>
        static constexpr std::tuple<Int, unsigned, unsigned> CivilFromDays(Int z) noexcept
        {
            static_assert(std::numeric_limits<unsigned>::digits >= 18, "This algorithm has not been ported to a 16 bit unsigned integer");
            static_assert(std::numeric_limits<Int>::digits >= 20, "This algorithm has not been ported to a 16 bit signed integer");
            z += 719468;
            const Int era = (z >= 0 ? z : z - 146096) / 146097;
            const unsigned doe = static_cast<unsigned>(z - era * 146097);               // [0, 146096]
            const unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365; // [0, 399]
            const Int y = static_cast<Int>(yoe) + era * 400;
            const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100); // [0, 365]
            const unsigned mp = (5 * doy + 2) / 153;                      // [0, 11]
            const unsigned d = doy - (153 * mp + 2) / 5 + 1;              // [1, 31]
            const unsigned m = mp + (mp < 10 ? 3 : -9);                   // [1, 12]
            return std::tuple<Int, unsigned, unsigned>(y + (m <= 2), m, d);
        }

        template <class Int>
        static constexpr unsigned WeekdayFromDays(Int z) noexcept
        {
            return static_cast<unsigned>(z >= -4 ? (z + 4) % 7 : (z + 5) % 7 + 6);
        }

        template <class To, class Rep, class Period>
        static To round_down(const std::chrono::duration<Rep, Period>& d)
        {
            To t = std::chrono::duration_cast<To>(d);
            if (t > d)
            {
                --t;
            }
            return t;
        }

        template <class Duration>
            requires IsChronoDurationV<Duration>
        static std::tm MakeUtcTm(std::chrono::time_point<std::chrono::system_clock, Duration> tp)
        {
            using namespace std;
            using namespace std::chrono;
            typedef duration<int, ratio_multiply<hours::period, ratio<24>>> days;
            // t is time duration since 1970-01-01
            Duration t = tp.time_since_epoch();
            // d is days since 1970-01-01
            days d = round_down<days>(t);
            // t is now time duration since midnight of day d
            t -= d;
            auto [year, month, day] = CivilFromDays(d.count());
            // start filling in the tm with calendar info
            std::tm tm = { 0 };
            tm.tm_year = year - 1900;
            tm.tm_mon = month - 1;
            tm.tm_mday = day;
            tm.tm_wday = WeekdayFromDays(d.count());
            tm.tm_yday = d.count() - DaysFromCivil(year, 1, 1);
            // Fill in the time
            tm.tm_hour = duration_cast<hours>(t).count();
            t -= hours(tm.tm_hour);
            tm.tm_min = duration_cast<minutes>(t).count();
            t -= minutes(tm.tm_min);
            tm.tm_sec = duration_cast<seconds>(t).count();
            return tm;
        }

        static std::wstring AsTimePassed(std::chrono::seconds dur)
        {
            using Days = std::chrono::duration<int, std::ratio<86400>>;
            const auto d = duration_cast<Days>(dur);
            dur -= d;
            const auto h = duration_cast<std::chrono::hours>(dur);
            dur -= h;
            const auto m = duration_cast<std::chrono::minutes>(dur);
            dur -= m;
            const auto s = duration_cast<std::chrono::seconds>(dur);

            const auto dc = d.count();
            const auto hc = h.count();
            const auto mc = m.count();
            const auto sc = s.count();

            std::wstringstream ss;
            ss.fill('0');
            if (dc)
            {
                ss << d.count() << "d ";
            }
            if (dc || hc)
            {
                if (dc)
                {
                    ss << std::setw(2);
                } // pad if second set of numbers
                ss << h.count() << "h ";
            }
            if (dc || hc || mc)
            {
                if (dc || hc)
                {
                    ss << std::setw(2);
                }
                ss << m.count() << "m ";
            }
            if (dc || hc || mc || sc)
            {
                if (dc || hc || mc)
                {
                    ss << std::setw(2);
                }
                ss << s.count() << 's';
            }

            return ss.str();
        }

        static std::wstring AsDate(const std::chrono::seconds total)
        {
            const auto time = std::chrono::time_point{ std::chrono::sys_seconds(total) };
            return std::format(L"{0:%Y-%m-%d %H:%M:%S}", time);
        }

        static std::wstring CurrentDateTimeString() { return AsDate(UnixTimeAsDuration<std::chrono::seconds>()); }

        template <typename T>
        static std::chrono::microseconds ToMicroseconds(T duration)
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(duration);
        }

        template <typename T>
        static std::chrono::milliseconds ToMilliseconds(T duration)
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        }

        template <typename T>
        static std::chrono::seconds ToSeconds(T duration)
        {
            return std::chrono::duration_cast<std::chrono::seconds>(duration);
        }

        template <typename T>
        static std::chrono::minutes ToMinutes(T duration)
        {
            return std::chrono::duration_cast<std::chrono::minutes>(duration);
        }

        template <typename T>
        static std::chrono::hours ToHours(T duration)
        {
            return std::chrono::duration_cast<std::chrono::hours>(duration);
        }

        template <typename T>
        static std::chrono::nanoseconds ToNanoseconds(T duration)
        {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
        }

        class Stopwatch
        {
                Stopwatch(const Stopwatch&) = delete;
                Stopwatch& operator=(const Stopwatch&) = delete;
                bool running;           // is the timer running?
                double start;           // start tick count
                double finish;          // end tick count
                const double frequency; // cached frequency value

                static double Counter() noexcept
                {
                    LARGE_INTEGER li;
                    ::QueryPerformanceCounter(&li);
                    return static_cast<double>(li.QuadPart);
                }

                static double Frequency() noexcept
                {
                    LARGE_INTEGER li;
                    ::QueryPerformanceFrequency(&li);
                    return static_cast<double>(li.QuadPart);
                }

                double ElapsedSeconds(const double start, const double finish) const noexcept { return ((finish - start)) / frequency; }

            public:
                // Initialize the stopwatch to a safe initial state
                Stopwatch() noexcept : running{ false }, start{ 0 }, finish{ 0 }, frequency{ Frequency() } {}

                // Clear the stopwatch state
                void Reset() noexcept
                {
                    finish = start = 0;
                    running = false;
                }

                void Start() noexcept
                {
                    running = true;
                    finish = 0;

                    start = Counter();
                }

                void Stop() noexcept
                {
                    finish = Counter();
                    running = false;
                }

                [[nodiscard]]
                double ElapsedSeconds() const noexcept
                {
                    if (running)
                    {
                        const double current{ Counter() };
                        return ElapsedSeconds(start, current);
                    }

                    return ElapsedSeconds(start, finish);
                }
        };
};
