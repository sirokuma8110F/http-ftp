#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include <limits.h>
#include <reent.h>
#include <sys/iosupport.h>

long pathconf(const char *path, int name)
{
        int ret = -1;
        unsigned int dev = FindDevice(path);
	struct _reent *r = _REENT;

        if(dev != -1 && devoptab_list[dev]->pathconf_r) {
                r->deviceData = devoptab_list[dev]->deviceData;
                ret = devoptab_list[dev]->pathconf_r(r, path, name);
        } else
                r->_errno=ENOSYS;

        return ret;
}
