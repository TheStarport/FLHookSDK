#pragma once

class TimeUtils
{
    public:
        TimeUtils() = delete;

        template <typename Duration>
            requires IsChronoDurationV<Duration>
        static uint64 UnixTime()
        {
            return static_cast<uint64>(std::chrono::duration_cast<Duration>(std::chrono::system_clock::now().time_since_epoch()).count());
        }

        Hook static std::chrono::sys_time<std::chrono::seconds> UnixToSysTime(const int64 time)
        {
            return std::chrono::sys_time<std::chrono::seconds>(std::chrono::sys_seconds(std::chrono::seconds{ time }));
        }

        Hook static std::wstring AsTimePassed(std::chrono::seconds dur)
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
            auto const time = std::chrono::current_zone()->to_local(std::chrono::sys_seconds(total));
            return std::format(L"{0:%Y-%m-%d %H:%M:%S}", time);
        }

        static std::wstring CurrentDate() { return AsDate(std::chrono::seconds{ UnixTime<std::chrono::seconds>() }); }

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

        class Hook Stopwatch
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
