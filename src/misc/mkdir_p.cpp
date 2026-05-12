
/* mkdir_p equivalent to GNU/Linux shell command "mkdir -p" */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

using namespace std;

/* HX-DOS / some MinGW targets do not have ENOTSUP */
#ifndef ENOTSUP
# define ENOTSUP EINVAL
#endif

#if defined (WIN32)
# include <direct.h>

# ifndef S_ISDIR
#  define S_ISDIR(x) (x & _S_IFDIR)
# endif

/* Windows uses \\ (though since Windows 7 or so, / is also accepted apparently) */
# define PSEP '\\'

int _wmkdir_p(const wchar_t *pathname) {
	errno = ENOSYS;
	return -1;
}
#else

// NTS: If the compile target uses backslash for path separator (DOS/WINDOWS) then this can change for those targets
# define PSEP '/'

int mkdir_p(const char *pathname, mode_t mode) {
	return -1;
}
#endif

