
#ifndef TIMESPEC_CHRONO_CONVERSIONS_HPP_
#define TIMESPEC_CHRONO_CONVERSIONS_HPP_

#include <chrono>
#include <time.h>

template <class TickType, class Period = std::ratio<1>>
constexpr std::chrono::duration<TickType, Period> /*std::chrono::duration<TickType, Period>*/
timespecToChronoDuration(const timespec &ts) {
  return std::chrono::duration_cast<std::chrono::duration<TickType, Period>>(
      std::chrono::seconds(ts.tv_sec) + std::chrono::nanoseconds(ts.tv_nsec));
}

template <class TickType, class Period = std::ratio<1>>
constexpr timespec
chronoDurationToTimespec(std::chrono::duration<TickType, Period> duration) {
  std::chrono::seconds durAsSec =
      std::chrono::duration_cast<std::chrono::seconds>(duration);
  std::chrono::nanoseconds durAsNsec =
      std::chrono::duration_cast<std::chrono::nanoseconds>(duration - durAsSec);

  return {.tv_sec = durAsSec.count(), .tv_nsec = durAsNsec.count()};
}

template <class ClockType, class TickType, class Period = std::ratio<1>>
constexpr std::chrono::time_point<ClockType,
                                 std::chrono::duration<TickType, Period>> timespecToChronoTimePoint(const timespec &ts) {
  return std::chrono::time_point<ClockType,
                                 std::chrono::duration<TickType, Period>>{
      timespecToChronoDuration<TickType, Period>(ts)};
}

template <class ClockType, class TickType, class Period = std::ratio<1>>
constexpr timespec timepointToTimespec(
    std::chrono::time_point<ClockType, std::chrono::duration<TickType, Period>>
        tp) {
  auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(tp);
  auto nsecs = std::chrono::time_point_cast<std::chrono::nanoseconds>(tp) -
               std::chrono::time_point_cast<std::chrono::nanoseconds>(seconds);

  return {.tv_sec = seconds.time_since_epoch().count(),
          .tv_nsec = nsecs.count()};
}

#endif // TIMESPEC_CHRONO_CONVERSIONS_HPP_
