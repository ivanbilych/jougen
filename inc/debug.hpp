#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#ifdef DEBUG
#define NO_LOGS     0
#define LOG_ERR     1
#define LOG_WARN    2
#define LOG_INFO    3
#define LOG_DEBUG   4
#define LOG_OBJ     5

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL LOG_OBJ
#endif

#else
#define DEBUG_LEVEL NO_LOGS
#endif // DEBUG

#if DEBUG_LEVEL > 0
#define PRINT_ERR(x)   do { std::cerr << "[ERROR] " << x << std::endl; } while (false)
#else
#define PRINT_ERR(x)
#endif

#if DEBUG_LEVEL > 1
#define PRINT_WARN(x)  do { std::cout << "[WARN]  " << x << std::endl; } while (false)
#else
#define PRINT_WARN(x)
#endif

#if DEBUG_LEVEL > 2
#define PRINT_INFO(x)  do { std::cout << "[INFO]  " << x << std::endl; } while (false)
#else
#define PRINT_INFO(x)
#endif

#if DEBUG_LEVEL > 3
#define PRINT_DEBUG(x) do { std::cout << "[DEBUG] " << x << std::endl; } while (false)
#else
#define PRINT_DEBUG(x)
#endif

#if DEBUG_LEVEL > 4
#define PRINT_OBJ(x)   do { std::cout << "[OBJ]   " << x << std::endl; } while (false)
#else
#define PRINT_OBJ(x)
#endif

#define PRINT(x)       do { std::cout << "[MSG]   " << x << std::endl; } while (false)
#define PRINT_TEST(x)  do { std::cout << "[TEST]  " << x << std::endl; } while (false)

#define NAME_ID "\"" << getName() << "\" (" << getId() << ")"
#define NAME_ID_CLASS(x) "\"" << (x).getName() << "\" (" << (x).getId() << ")"

#endif // DEBUG_H
