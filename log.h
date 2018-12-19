#include <iostream>

#ifdef DEBUG
# define DEBUG_PREFIX "[DEBUG|" << __FILE__ << ":" << __LINE__ << "] "
# define LOG(str) std::cerr << DEBUG_PREFIX << str << std::endl
#else
# define LOG(str)
#endif
