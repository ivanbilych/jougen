#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <iostream>

#define TEST_OK do { \
        std::cout << "[OK]    Test "; \
        std::cout.fill('0'); \
        std::cout.width(2); \
        std::cout << std::right << currentTest << "/" << numberOfTests << std::endl; \
    } while (false)

#define TEST_FAIL do { \
        std::cout << "[FAIL]  Test "; \
        std::cout.fill('0'); \
        std::cout.width(2); \
        std::cout << std::right << currentTest << "/" << numberOfTests << std::endl; \
    } while (false)

#endif // TEST_COMMON_H
