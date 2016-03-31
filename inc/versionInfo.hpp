#ifndef COMMON_H
#define COMMON_H

#include <string>

#define VERSION_MAJOR "0"
#define VERSION_MINOR_HI "0"
#define VERSION_MINOR_LO "0"
#define VERSION_SUFFIX " alpha"

#ifndef COMMIT_ID
#define COMMIT_ID unknown
#endif
#define STRINGIZE(x) #x
#define STRINGIZE_VALUE_OF(x) STRINGIZE(x)
#ifndef BUILD_DATE
#define BUILD_DATE __DATE__
#endif
#ifndef BUILD_TIME
#define BUILD_TIME __TIME__
#endif

#define PROJECT_URL "https://github.com/ivanbilych/jougen"

const std::string versionMajor { VERSION_MAJOR };
const std::string versionMinorHi { VERSION_MINOR_HI };
const std::string versionMinorLo { VERSION_MINOR_LO };
const std::string versionSuffix { VERSION_SUFFIX };
const std::string programVersion { versionMajor + "." + versionMinorHi + "." + versionMinorLo + versionSuffix };
const std::string buildDate { BUILD_DATE };
const std::string buildTime { BUILD_TIME };
const std::string buildTimestamp { buildDate + " " + buildTime };
const std::string buildCommit { STRINGIZE_VALUE_OF(COMMIT_ID) };
const std::string projectURL { PROJECT_URL };

#endif // COMMON_H
