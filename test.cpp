#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

#define BAD_VALUE -1
#define ALOGE(x) printf(x)

int main() 
{
#define ERROR_MSG_PREFIX "%s: Invalid device name '%s'. " \
    "Should match 'device@<major>.<minor>/<type>/<id>' - "

    string name = "device@3.4/external/23";
    int major, minor, type, id;


//    if (!major || !minor || !type || !id) return -1;//INVALID_OPERATION;

    // Verify starting prefix
    const char expectedPrefix[] = "device@";

    if (name.find(expectedPrefix) != 0) {
        return BAD_VALUE;
    }

    // Extract major/minor versions
    std::string::size_type atIdx = sizeof(expectedPrefix) - 2;
    std::string::size_type dotIdx = name.find('.', atIdx);
    if (dotIdx == std::string::npos) {
        return BAD_VALUE;
    }
    std::string::size_type typeSlashIdx = name.find('/', dotIdx);
    if (typeSlashIdx == std::string::npos) {
        return BAD_VALUE;
    }

    char *endPtr;
    //errno = 0;
    long majorVal = strtol(name.c_str() + atIdx + 1, &endPtr, 10);
    //if (errno != 0) {
    //    return BAD_VALUE;
    //}
    if (endPtr != name.c_str() + dotIdx) {
        return BAD_VALUE;
    }
    long minorVal = strtol(name.c_str() + dotIdx + 1, &endPtr, 10);
    //if (errno != 0) {
    //    return BAD_VALUE;
    //}
    if (endPtr != name.c_str() + typeSlashIdx) {
        return BAD_VALUE;
    }
    //if (majorVal < 0 || majorVal > UINT16_MAX || minorVal < 0 || minorVal > UINT16_MAX) {
    //    return BAD_VALUE;
    //}

    // Extract type and id

    std::string::size_type instanceSlashIdx = name.find('/', typeSlashIdx + 1);
    if (instanceSlashIdx == std::string::npos) {
        return BAD_VALUE;
    }
    std::string typeVal = name.substr(typeSlashIdx + 1, instanceSlashIdx - typeSlashIdx - 1);

    if (instanceSlashIdx == name.size() - 1) {
        return BAD_VALUE;
    }
    std::string idVal = name.substr(instanceSlashIdx + 1);

    printf("id: %s\n", idVal.c_str());

    return 0;  
}
