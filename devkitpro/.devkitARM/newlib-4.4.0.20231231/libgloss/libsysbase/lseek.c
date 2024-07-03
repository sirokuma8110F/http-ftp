#include "config.h"
#include <_ansi.h>
#include <_syslist.h>
#include <errno.h>

#include <sys/iosupport.h>

#include <sys/iosupport.h>

//---------------------------------------------------------------------------------
_off_t _lseek_r(struct _reent * r, int fileDesc, _off_t pos, int dir) {
//---------------------------------------------------------------------------------
	_off_t ret = -1;
	unsigned int dev = 0;

	__handle * handle;

	if(fileDesc!=-1) {

		handle = __get_handle(fileDesc);

		if ( NULL == handle ) {
			r->_errno=EBADF;
			return ret;
		}

		dev = handle->device;

		if(devoptab_list[dev]->seek_r) {
			r->deviceData = devoptab_list[dev]->deviceData;
			ret = devoptab_list[dev]->seek_r( r, handle->fileStruct, pos, dir);
		} else
			r->_errno=ENOSYS;

	}
	return ret;

}
