#include "errorlog.h"

inline void ERROR(const char *msg)
{
	printf("%s [%s]:%d %s: errno %d: %s\n", getTime(), __FILE__, __LINE__, msg, errno, strerror(errno));
}

inline void PTHREAD_ERROR(const char *msg, int err)
{
	printf("%s [%s]:%d %s: errnum %d: %s\n", getTime(), __FILE__, __LINE__, msg, err, strerror(err));
}
