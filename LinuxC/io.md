- man 1 命令
- man 2 系统
- man 3 标准
- man 7 机制  

## 标准IO  
### 1. fopen  
``` c
#include <stdio.h>

FILE *fopen(const char *pathname, const char *mode);    //打开文件并关联一个流 
int fclose(FILE *stream);   //刷新流，并关闭文件描述符
```
- **parameter**
    - **mode**
        |  参数 |           说明            |            |
        |:-----:|:----------------------- |:------------|
        |**r**  |只读                       |不存在则报错 |
        |**w**  |截短为0长度                |不存在则创建 |
        |**a**  |追加写                     |不存在则创建 |
        |**a+** |追加读写，读从开头，写从结尾 |不存在则创建 |

- **return**  
    返回值在 **堆** 上存储

### 2. fgetc/getc/getchar/fgets     
``` c
#include <stdio.h>

int fgetc(FILE *stream);
int getc(FILE *stream); //(宏函数)
int getchar(void);      //(getchar() == getc(stdin))

char *fgets(char *s, int size, FILE *stream);
```       
- **description**
    - **fgetc()** 从 **stream** 中读取下一个字符，以 **int** 返回，出错返回 **EOF**   
    - **fgets()** 从 **stream** 中读取至多 **size-1** 个字符，存储在 **s** 的缓冲区中，并在最后一个字符之后添加 **\0**  
    遇到 **size-1** / **EOF** / **\n** 停止读取。如果是 **\n** 则读入缓冲区中

- **return**  
    - **fgetc()** ， **getc()** ， **getchar()**  
        正确：**int**   
        错误：**EOF**  
    - **fgets()**  
        正确：**s**  
        错误: **NULL**

### 3. fputc/putc/putchar/fputs/puts  
```c
#include <stdio.h>

int fputc(int c, FILE *stream);
int putc(int c, FILE *stream);  //(宏函数)
int putchar(int c);             //(putchar(c) == putc(c, stdout))

int fputs(const char *s, FILE *stream);
int puts(const char *s);        //stdout 自动添加\n
```
- **description**  
    **fputc** 将 **c** 以 **unsigned char** 写入 **stream** 中  
    **fputs** 将 **s** 写到 **stream** 中，不包括 **'\0'**

- **return**  
    - **fputc()** , **putc()** , **putchar()**   
        正确 unsigned char 以int形式    
        错误 EOF   
    - **puts()** , **fputs()**  
        正确 非负数  
        错误 EOF


### 4. fread & fwrite
```c
#include <stdio.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```
- **description**
    - **fread()**   
        从 **stream** 中读取每个长为 **size** 字节的 **nmenb** 数据项，放在 **ptr** 指的位置
    - **fwrite()**  
        从 **ptr** 位置获取的每个长为 **size** 字节的 **nmenb** 数据项写入 **stream** 
- **return**  
    - success  
        写或读的项数，仅当 **size = 1** 时，返回转移的字节数
    - error or end
        the return value is a short item count (or zero).

### 5. printf & scanf
> 待续 ...

### 6. getline  
```c
#include <stdio.h>

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

// 要手动释放lineptr
```

### 7. fseek & ftell
```c
#include <stdio.h>

int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);   //获取指针位置
//文件超过2g便不再适合使用
```

### 8. fflush
```c
#include <stdio.h>

int fflush(FILE *stream);
```
- **缓冲**  
    - **全缓冲** 缓冲区满、fflush()、程序结束 ，如普通文件
    - **行缓冲** 换行刷新、缓冲区满、fflush()、程序结束，如stdout输出到终端
    - **无缓冲** 立刻刷新，如stderr

### 9. tmpfile
```c
#include <stdio.h>

FILE *tmpfile(void);
```

### 2. fsync fdatasync

### 7. fileno & fdopen
```c
#include <stdio.h>

int fileno(FILE *stream);
FILE *fdopen(int fd, const char *mode);
```

## 二、系统IO

### 1. open & close
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags, mode_t mode); //变参函数

//**************************//

#include <unistd.h>

int close(int fd);
```
- **parameter**  
    - **flags**  
        |  参数  |  说明   |
        |:-     |:-       |
        |O_RDONLY|只读    |
        |O_WRONLY|只写    |
        |O_RDWR  |读写    |        
        |以上必须有一个 |  | 
        |O_CREAT |如果文件不存在，则创建它（需配合 mode 参数指定权限） |
        |O_TRUNC |截断为0    |
        |O_APPEND|追加       |
        |O_SYNC  |同步写入，每次写都会等待数据物理写入磁盘（性能较低）|        
        |O_EXCL  |与 O_CREAT 配合使用，如果文件已存在，则 open() 失败|

    - **mode** (有O_CREAT,使用)  
        设置文件权限

### 2. read
```c
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```
### 3. write
```c
#include <unistd.h>

ssize_t write(int fd, const void *buf, size_t count);
```
### 4. lseek
```c
#include <sys/types.h>
#include <unistd.h>

 off_t lseek(int fd, off_t offset, int whence);
```
### 5. fcntl & ioctl
```c
#include <unistd.h>
#include <fcntl.h>

int fcntl(int fd, int cmd, ... /* arg */ );
```
### 6. ioctl
```c
#include <sys/ioctl.h>

int ioctl(int fd, unsigned long request, ...);
```

### 8. dup & dup2
```c
#include <unistd.h>

int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

### 9. sync 
```c
#include <unistd.h>

void sync(void);
```


## 文件系统
文件描述符(int 是数组的下标 优先使用当前范围内最小的 该数组存在该进程空间中)
fd的产生

dev/fd/ 虚拟目录由内核动态生成对应当前进程已打开的文件描述符，它提供了访问文件描述符(file descriptors)的接口。
### 目录和文件
空洞文件

1. 获取文件属性
stat，fstat，lstat

2. 文件访问权限、
st_mode

3. umask
4. 文件权限更改和管理
5. 粘住位 (t位)

6. 文件系统 fat ufs

7. 链接
ulink
link
remove
8. utime
9. 目录 创建销毁
10. 更改当前工作目录
11. 分析读取目录

### 系统数据文件和信息

/etc/passwd
/etc/shadow
/etc/group

加密

沟子函数
atexit

命令行分析
getopt

环境变量
getenv
setenv



### 进程环境

进程空间
pmap

    0xFFFFFFFFFFFF  +---------------------+ 4G
                    | 内核空间             | (用户程序不可访问)
    0x0000C0000000  +---------------------+ 3G 
                    | 命令行参数和环境变量  |
                    +---------------------+
                    | 栈区 (向下增长)      | ← %rsp (栈指针)
                    |                     |
                    |                     |
                    | 动态库映射区         |
                    |   - 动态库的代码段   |
                    |   - 动态库的数据段   |
                    |                     |
                    | 堆区 (向上增长)      | ← brk/sbrk边界
                    |                     |
                    +---------------------+
                    | 未初始化数据(BSS)    |
                    +---------------------+
                    | 初始化数据区         |
                    +---------------------+
                    | 代码区(Text)         |
                    |   - 主程序代码       |
                    |   - 静态库代码       |
    0x000008048000  +---------------------+ 
                    | 保留区               |
    0x000000000000  +---------------------+


手工装载库
dlopen
dlclose
dlerror
dlsym

2. 函数跳转
setjmp
longjmp

3. 资源获取
setrlimit
getrlimit