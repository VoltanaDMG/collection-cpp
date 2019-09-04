#include <windows.h>
#include <sys/timeb.h>

//struct timespec { long tv_sec; long tv_nsec; };    //header part
int clock_gettime(int, struct timespec *spec)      //C-file part
{  __int64 wintime; GetSystemTimeAsFileTime((FILETIME*)&wintime);
   wintime      -=116444736000000000LL;  //1jan1601 to 1jan1970
   spec->tv_sec  =wintime / 10000000LL;           //seconds
   spec->tv_nsec =wintime % 10000000LL *100;      //nano-seconds
   return 0;
}