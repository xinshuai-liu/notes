## 并发

### 多进程
进程标识符 pid_t

号是顺次下向

#include <sys/types.h>
#include <unistd.h>
getpid
getppid
fork
wait
waitpid
exec函数族

system()

系统时间
times

//守护进程
setsid
getpgid

系统日志syslogd
openlog
syslog
closelog

父子进程的区别
不同
    返回值
    pid ，ppid
    未决信号和文件锁不继承
    资源利用量清0


init进程是所有进程的祖先进程



### 信号
#### 1 概念  
信号是软件中断  

同步和异步  
异步事件处理方法：查询和通知


信号会打断系统调用






signal()
信号的不可靠
可重入函数
    所有系统调用都是可重入的
    一部分库函数可重入 如memcpy

信号的响应过程
    信号从收到到响应有一个不可避免的延迟
    思考
        如何忽略一个信号
        标准信号为什么要丢失



常用函数
kill
raise
alarm
pause
abort
system
sleep

信号集
信号屏蔽字和pending集的处理

扩展
    sigsuspend
    sigaction
    setitimer

实时信号


### 多线程

