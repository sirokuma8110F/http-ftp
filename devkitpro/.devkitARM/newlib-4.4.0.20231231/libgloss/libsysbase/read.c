#include "config.h"
#include <_ansi.h>
#include <_syslist.h>
#include <stdio.h>
#include <errno.h>

#include <sys/iosupport.h>

//---------------------------------------------------------------------------------
_ssize_t _read_r(struct _reent *r, int fileDesc, void *ptr, size_t len) {
//---------------------------------------------------------------------------------
	int ret = -1;
	unsigned int dev = 0;

	__handle * handle = NULL;

	if(fileDesc!=-1) {
		handle = __get_handle(fileDesc);

		if ( NULL == handle ) {
			r->_errno=EBADF;
			return ret;
		}

		dev = handle->device;

		if(devoptab_list[dev]->read_r) {
			r->deviceData = devoptab_list[dev]->deviceData;
			ret = devoptab_list[dev]->read_r(r,handle->fileStruct,ptr,len);
		} else
			r->_errno=ENOSYS;
	}
	return ret;
}
