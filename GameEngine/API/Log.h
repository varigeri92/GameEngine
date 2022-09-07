#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

#define LOG_ENABLE
#ifdef  LOG_ENABLE

#define NC   "\033[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define CYN  "\x1B[34m"
#define REDB "\x1B[31m"
#define YEL  "\x1B[33m"

#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#define LOG_INFO(msg) \
    std::cout << CYN << "  [I]" << NC <<":: " << msg << GRN << " " << __FILENAME__ << "(" << __LINE__ << ")" NC << std::endl

#define LOG_WARN(msg) \
    std::cout << YEL << "  [W]" << NC <<":: " << msg << GRN << " " <<  __FILENAME__ << " (" << __LINE__ << ")" NC << std::endl

#define LOG_ERROR(msg) \
    std::cout << RED << "  [E]" << NC <<":: " << msg << GRN << " " << __FILENAME__ << " (" << __LINE__ << ")" NC << std::endl

#define ASSERT(cond,msg) \
    assert(cond && std::cout << RED << "[ASSERTION FAILED!]" << NC <<":: " << msg << GRN << " " << __FILENAME__ << " (" << __LINE__ << ")" NC << std::endl<<std::endl)

#define VK_I(msg) \
    std::cout << CYN << "  [validation layer]" << NC ":: " << msg << " " << __FILENAME__ << " (" << __LINE__ << ")" << std::endl
#define VK_W(msg) \
    std::cout << YEL << "  [validation layer]" << NC ":: " << msg << " " << __FILENAME__ << " (" << __LINE__ << ")" << std::endl
#define VK_E(msg) \
    std::cout << RED << "  [validation layer]" << NC ":: " << msg << " " << __FILENAME__ << " (" << __LINE__ << ")" << std::endl

#define VK_CHECK(result, msg) \
    if(result != 0){ \
        if(result < 0){\
            std::cout << RED << " [VK_Critical]" << NC ":: result:" << result << " -> " << msg << " " << __FILENAME__ << " (" << __LINE__ << ")" << std::endl<<std::endl;\
            abort();\
        } \
        std::cout << RED << " [VK_Error]" << NC ":: result:" << result << " -> " << msg << " " << __FILENAME__ << " (" << __LINE__ << ")" << std::endl<<std::endl;\
    }\

#else
  
#define LOG_INFO(msg) 
#define LOG_WARN(msg) 
#define LOG_ERROR(msg) 
#define ASSERT(cond,msg) 
#define VK_I(msg) 
#define VK_W(msg) 
#define VK_E(msg) 
#define VK_CHECK(result, msg)

#endif //  LOG_ENABLE

