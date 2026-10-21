#pragma once

#include <cstdio>

#ifdef TTR_ASSERT
#error "TTR_ASSERT already defined somewhere else"
#endif

/*
  TTR_ASSERT(cond)
  TTR_ASSERT(cond, "Custom message")

  Development build: when cond is false, print the condition, the optional message
  and the location to stderr, then break into the debugger at the failing line.
  Production build (PRODUCTION_BUILD=1): compiled out, cond is NOT evaluated,
  so never put side effects inside the condition.
*/

// clang-format off
#if defined(_WIN32)
  #define TTR_DEBUG_BREAK() __debugbreak()
#elif defined(__clang__)
  #define TTR_DEBUG_BREAK() __builtin_debugtrap()
#else
  #include <csignal>
  #define TTR_DEBUG_BREAK() std::raise(SIGTRAP)
#endif
// clang-format on

namespace ttr::detail
{
  inline void reportAssert(const char *expression, const char *message, const char *file, int line)
  {
    std::fprintf(stderr, "TTR_ASSERT failed: %s\n", expression);
    if (message[0] != '\0')
    {
      std::fprintf(stderr, "  message: %s\n", message);
    }
    std::fprintf(stderr, "  at %s:%d\n", file, line);
  }
}

/*
  Optional message: the extra "" "" arguments fill `message` when it is not given,
  and keep the trailing `...` non-empty (required before C++20).
  TTR_EXPAND works around the old MSVC preprocessor passing __VA_ARGS__ as one argument.
*/
#define TTR_EXPAND(x) x
#define TTR_ASSERT(...) TTR_EXPAND(TTR_ASSERT_IMPL(__VA_ARGS__, "", ""))

// clang-format off
#if defined(PRODUCTION_BUILD) && PRODUCTION_BUILD
  // sizeof keeps the condition compiling (and its variables "used") without evaluating it
  #define TTR_ASSERT_IMPL(cond, message, ...) do { (void)sizeof(cond); } while (0)
#else
  #define TTR_ASSERT_IMPL(cond, message, ...)                                  \
    do {                                                                       \
      if (!(cond)) {                                                           \
        ::ttr::detail::reportAssert(#cond, message, __FILE__, __LINE__);       \
        TTR_DEBUG_BREAK();                                                     \
      }                                                                        \
    } while (0)
#endif
// clang-format on
