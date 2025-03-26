/* FILE: log.h */
/*...*/
typedef enum {
	/*...*/
	SYSLOG_LEVEL_FATAL,
	/*...*/
	                     = -1
}       LogLevel;

/*...*/
void	 sshfatal(const char *, const char *, int, int,
    LogLevel, const char *, const char *, ...) __attribute__((noreturn))
    __attribute__((format(printf, 7, 8)));
/*...*/
#define fatal_f(...)		sshfatal(__FILE__, __func__, __LINE__, 1, SYSLOG_LEVEL_FATAL, NULL, __VA_ARGS__)


/* FILE: monitor_wrap.c */
/*...*/
#include "log.h"
/*...*/
void
mm_request_send(int sock, enum monitor_reqtype type, struct sshbuf *m)
{
	size_t mlen = sshbuf_len(m);
	/*...*/
	if (mlen >= 0xffffffff)
		fatal_f("bad length %zu", mlen);                /* CRASH LOCATION */
	/*...*/

}
