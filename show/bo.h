#ifndef BO_H
#define BO_H
#include<stdint.h>
#include<asm/types.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<time.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<fcntl.h>
#include<netdb.h>
#include<signal.h>
#include<pthread.h>
#include<sys/stat.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/uio.h>
#include<sys/wait.h>
#include<sys/un.h>
#include<sys/select.h>
#include<sys/sysctl.h>
#include<poll.h>
#include<sys/ioctl.h>
#include<termios.h>
#include<limits.h>
#include<unistd.h>
#include<dirent.h>
#include<syslog.h>
#include<sys/mman.h>
#include<setjmp.h>
#include<stddef.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<pwd.h>
#include<sys/param.h>
#include<net/if.h>
#include<sys/param.h>

//////////////////////////////////////////
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stddef.h>
extern "C"{
#include<libavcodec/avcodec.h>
#include<libavformat/avformat.h>
#include<libswscale/swscale.h>
#include<libavutil/opt.h>
//#include<libavutil/channel_layout.h>
//#include<libavutil/common.h>
#include<libavutil/imgutils.h>

//#include "libswresample/swresample.h"

//#include<libavutil/mathematics.h>
//#include<libavutil/samplefmt.h>
}
#endif // BO_H
