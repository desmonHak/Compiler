%define sys_restart_syscall     0x00     ; sys_restart_syscall  0x00    -       -       -       -       -       kernel/signal.c:2475
%define sys_exit        0x01     ; sys_exit     0x01    int error_code  -       -       -       -       kernel/exit.c:935
%define sys_fork        0x02     ; sys_fork     0x02    -       -       -       -       -       kernel/fork.c:2116
%define sys_read        0x03     ; sys_read     0x03    unsigned int fd char __user *buf        size_t count    -       -     fs/read_write.c:566
%define sys_write       0x04     ; sys_write    0x04    unsigned int fd const char __user *buf  size_t count    -       -     fs/read_write.c:581
%define sys_open        0x05     ; sys_open     0x05    const char __user *filename     int flags       umode_t mode    -     fs/fhandle.c:257
%define sys_close       0x06     ; sys_close    0x06    unsigned int fd -       -       -       -       fs/open.c:1153
%define sys_waitpid     0x07     ; sys_waitpid  0x07    pid_t pid       int __user *stat_addr   int options     -       -     kernel/exit.c:1692
%define sys_creat       0x08     ; sys_creat    0x08    const char __user *pathname     umode_t mode    -       -       -     fs/open.c:1115
%define sys_link        0x09     ; sys_link     0x09    const char __user *oldname      const char __user *newname      -     fs/namei.c:4313
%define sys_unlink      0x0a     ; sys_unlink   0x0a    const char __user *pathname     -       -       -       -       fs/namei.c:4097
%define sys_execve      0x0b     ; sys_execve   0x0b    const char __user *filename     const char __user *const __user *argv const char __user *const __user *envp    -       -       fs/exec.c:1919
%define sys_chdir       0x0c     ; sys_chdir    0x0c    const char __user *filename     -       -       -       -       fs/open.c:434
%define sys_time        0x0d     ; sys_time     0x0d    time_t __user *tloc     -       -       -       -       kernel/sys.c:903
%define sys_mknod       0x0e     ; sys_mknod    0x0e    const char __user *filename     umode_t mode    unsigned dev    -     fs/namei.c:3785
%define sys_chmod       0x0f     ; sys_chmod    0x0f    const char __user *filename     umode_t mode    -       -       -     fs/open.c:575
%define sys_lchown16    0x10     ; sys_lchown16 0x10    const char __user *filename     old_uid_t user  old_gid_t group -     kernel/uid16.c:26
%define not implemented 0x11     ; not implemented      0x11    -       -       -       -       -       :
%define sys_stat        0x12     ; sys_stat     0x12    const char __user *filename     struct __old_kernel_stat __user *statbuf       -       -       -       fs/stat.c:244
%define sys_lseek       0x13     ; sys_lseek    0x13    unsigned int fd off_t offset    unsigned int whence     -       -     fs/read_write.c:304
%define sys_getpid      0x14     ; sys_getpid   0x14    -       -       -       -       -       kernel/sys.c:838
%define sys_mount       0x15     ; sys_mount    0x15    char __user *dev_name   char __user *dir_name   char __user *type     unsigned long flags      void __user *data       fs/namespace.c:3034
%define sys_oldumount   0x16     ; sys_oldumount        0x16    char __user *name       -       -       -       -       fs/namespace.c:1728
%define sys_setuid16    0x17     ; sys_setuid16 0x17    old_uid_t uid   -       -       -       -       kernel/uid16.c:51
%define sys_getuid16    0x18     ; sys_getuid16 0x18    -       -       -       -       -       kernel/uid16.c:201
%define sys_stime       0x19     ; sys_stime    0x19    time_t __user *tptr     -       -       -       -       kernel/time/time.c:83
%define sys_ptrace      0x1a     ; sys_ptrace   0x1a    long request    long pid        unsigned long addr      unsigned long data     -       kernel/ptrace.c:1121
%define sys_alarm       0x1b     ; sys_alarm    0x1b    unsigned int seconds    -       -       -       -       kernel/time/itimer.c:285
%define sys_fstat       0x1c     ; sys_fstat    0x1c    unsigned int fd struct __old_kernel_stat __user *statbuf        -     fs/stat.c:270
%define sys_pause       0x1d     ; sys_pause    0x1d    -       -       -       -       -       kernel/signal.c:3618
%define sys_utime       0x1e     ; sys_utime    0x1e    char __user *filename   struct utimbuf __user *times    -       -     fs/utimes.c:24
%define not implemented 0x1f     ; not implemented      0x1f    -       -       -       -       -       :
%define not implemented 0x20     ; not implemented      0x20    -       -       -       -       -       :
%define sys_access      0x21     ; sys_access   0x21    const char __user *filename     int mode        -       -       -     fs/open.c:429
%define sys_nice        0x22     ; sys_nice     0x22    int increment   -       -       -       -       kernel/sched/core.c:3852
%define not implemented 0x23     ; not implemented      0x23    -       -       -       -       -       :
%define sys_sync        0x24     ; sys_sync     0x24    -       -       -       -       -       fs/sync.c:108
%define sys_kill        0x25     ; sys_kill     0x25    pid_t pid       int sig -       -       -       kernel/signal.c:2953
%define sys_rename      0x26     ; sys_rename   0x26    const char __user *oldname      const char __user *newname      -     fs/namei.c:4642
%define sys_mkdir       0x27     ; sys_mkdir    0x27    const char __user *pathname     umode_t mode    -       -       -     fs/namei.c:3841
%define sys_rmdir       0x28     ; sys_rmdir    0x28    const char __user *pathname     -       -       -       -       fs/namei.c:3944
%define sys_dup 0x29     ; sys_dup      0x29    unsigned int fildes     -       -       -       -       fs/file.c:925
%define sys_pipe        0x2a     ; sys_pipe     0x2a    int __user *fildes      -       -       -       -       fs/pipe.c:861
%define sys_times       0x2b     ; sys_times    0x2b    struct tms __user *tbuf -       -       -       -       kernel/sys.c:903
%define not implemented 0x2c     ; not implemented      0x2c    -       -       -       -       -       :
%define sys_brk 0x2d     ; sys_brk      0x2d    unsigned long brk       -       -       -       -       mm/mmap.c:182
%define sys_setgid16    0x2e     ; sys_setgid16 0x2e    old_gid_t gid   -       -       -       -       kernel/uid16.c:41
%define sys_getgid16    0x2f     ; sys_getgid16 0x2f    -       -       -       -       -       kernel/uid16.c:211
%define sys_signal      0x30     ; sys_signal   0x30    int sig __sighandler_t handler  -       -       -       kernel/signal.c:3601
%define sys_geteuid16   0x31     ; sys_geteuid16        0x31    -       -       -       -       -       kernel/uid16.c:206
%define sys_getegid16   0x32     ; sys_getegid16        0x32    -       -       -       -       -       kernel/uid16.c:216
%define sys_acct        0x33     ; sys_acct     0x33    const char __user *name -       -       -       -       kernel/acct.c:273
%define sys_umount      0x34     ; sys_umount   0x34    char __user *name       int flags       -       -       -       fs/namespace.c:1683
%define not implemented 0x35     ; not implemented      0x35    -       -       -       -       -       :
%define sys_ioctl       0x36     ; sys_ioctl    0x36    unsigned int fd unsigned int cmd        unsigned long arg       -     fs/ioctl.c:692
%define sys_fcntl       0x37     ; sys_fcntl    0x37    unsigned int fd unsigned int cmd        unsigned long arg       -     fs/fcntl.c:448
%define not implemented 0x38     ; not implemented      0x38    -       -       -       -       -       :
%define sys_setpgid     0x39     ; sys_setpgid  0x39    pid_t pid       pid_t pgid      -       -       -       kernel/sys.c:953
%define not implemented 0x3a     ; not implemented      0x3a    -       -       -       -       -       :
%define sys_olduname    0x3b     ; sys_olduname 0x3b    struct oldold_utsname __user *  -       -       -       -       kernel/sys.c:1214
%define sys_umask       0x3c     ; sys_umask    0x3c    int mask        -       -       -       -       kernel/sys.c:1754
%define sys_chroot      0x3d     ; sys_chroot   0x3d    const char __user *filename     -       -       -       -       fs/open.c:482
%define sys_ustat       0x3e     ; sys_ustat    0x3e    unsigned dev    struct ustat __user *ubuf       -       -       -     fs/statfs.c:232
%define sys_dup2        0x3f     ; sys_dup2     0x3f    unsigned int oldfd      unsigned int newfd      -       -       -     fs/file.c:910
%define sys_getppid     0x40     ; sys_getppid  0x40    -       -       -       -       -       kernel/sys.c:855
%define sys_getpgrp     0x41     ; sys_getpgrp  0x41    -       -       -       -       -       kernel/sys.c:1054
%define sys_setsid      0x42     ; sys_setsid   0x42    -       -       -       -       -       kernel/sys.c:1100
%define sys_sigaction   0x43     ; sys_sigaction        0x43    int     const struct old_sigaction __user *     struct old_sigaction __user *  -       -       arch/mips/kernel/signal.c:554
%define sys_sgetmask    0x44     ; sys_sgetmask 0x44    -       -       -       -       -       kernel/signal.c:3579
%define sys_ssetmask    0x45     ; sys_ssetmask 0x45    int newmask     -       -       -       -       kernel/signal.c:3585
%define sys_setreuid16  0x46     ; sys_setreuid16       0x46    old_uid_t ruid  old_uid_t euid  -       -       -       kernel/uid16.c:46
%define sys_setregid16  0x47     ; sys_setregid16       0x47    old_gid_t rgid  old_gid_t egid  -       -       -       kernel/uid16.c:36
%define sys_sigsuspend  0x48     ; sys_sigsuspend       0x48    int unused1     int unused2     old_sigset_t mask       -     kernel/signal.c:3692
%define sys_sigpending  0x49     ; sys_sigpending       0x49    old_sigset_t __user *set        -       -       -       -     kernel/signal.c:3340
%define sys_sethostname 0x4a     ; sys_sethostname      0x4a    char __user *name       int len -       -       -       kernel/sys.c:1249
%define sys_setrlimit   0x4b     ; sys_setrlimit        0x4b    unsigned int resource   struct rlimit __user *rlim      -     kernel/sys.c:1602
%define sys_old_getrlimit       0x4c     ; sys_old_getrlimit    0x4c    unsigned int resource   struct rlimit __user *rlim    kernel/sys.c:1389
%define sys_getrusage   0x4d     ; sys_getrusage        0x4d    int who struct rusage __user *ru        -       -       -     kernel/sys.c:1728
%define sys_gettimeofday        0x4e     ; sys_gettimeofday     0x4e    struct timeval __user *tv       struct timezone __user *tz     -       -       -       kernel/time/time.c:144
%define sys_settimeofday        0x4f     ; sys_settimeofday     0x4f    struct timeval __user *tv       struct timezone __user *tz     -       -       -       kernel/time/time.c:235
%define sys_getgroups16 0x50     ; sys_getgroups16      0x50    int gidsetsize  old_gid_t __user *grouplist     -       -     kernel/uid16.c:153
%define sys_setgroups16 0x51     ; sys_setgroups16      0x51    int gidsetsize  old_gid_t __user *grouplist     -       -     kernel/uid16.c:176
%define sys_old_select  0x52     ; sys_old_select       0x52    struct sel_arg_struct __user *arg       -       -       -     fs/select.c:784
%define sys_symlink     0x53     ; sys_symlink  0x53    const char __user *old  const char __user *new  -       -       -     fs/namei.c:4154
%define sys_lstat       0x54     ; sys_lstat    0x54    const char __user *filename     struct __old_kernel_stat __user *statbuf       -       -       -       fs/stat.c:257
%define sys_readlink    0x55     ; sys_readlink 0x55    const char __user *path char __user *buf        int bufsiz      -     fs/stat.c:418
%define sys_uselib      0x56     ; sys_uselib   0x56    const char __user *library      -       -       -       -       fs/exec.c:120
%define sys_swapon      0x57     ; sys_swapon   0x57    const char __user *specialfile  int swap_flags  -       -       -     mm/swapfile.c:3087
%define sys_reboot      0x58     ; sys_reboot   0x58    int magic1      int magic2      unsigned int cmd        void __user *arg       -       kernel/reboot.c:280
%define sys_old_readdir 0x59     ; sys_old_readdir      0x59    unsigned int    struct old_linux_dirent __user *        unsigned int   -       -       fs/readdir.c:125
%define sys_old_mmap    0x5a     ; sys_old_mmap 0x5a    struct mmap_arg_struct __user *arg      -       -       -       -     mm/mmap.c:1535
%define sys_munmap      0x5b     ; sys_munmap   0x5b    unsigned long addr      size_t len      -       -       -       mm/mmap.c:2735
%define sys_truncate    0x5c     ; sys_truncate 0x5c    const char __user *path long length     -       -       -       fs/open.c:153
%define sys_ftruncate   0x5d     ; sys_ftruncate        0x5d    unsigned int fd unsigned long length    -       -       -     fs/open.c:213
%define sys_fchmod      0x5e     ; sys_fchmod   0x5e    unsigned int fd umode_t mode    -       -       -       fs/open.c:544
%define sys_fchown16    0x5f     ; sys_fchown16 0x5f    unsigned int fd old_uid_t user  old_gid_t group -       -       kernel/uid16.c:31
%define sys_getpriority 0x60     ; sys_getpriority      0x60    int which       int who -       -       -       kernel/sys.c:253
%define sys_setpriority 0x61     ; sys_setpriority      0x61    int which       int who int niceval     -       -       kernel/sys.c:183
%define not implemented 0x62     ; not implemented      0x62    -       -       -       -       -       :
%define sys_statfs      0x63     ; sys_statfs   0x63    const char __user * path        struct statfs __user *buf       -     fs/statfs.c:176
%define sys_fstatfs     0x64     ; sys_fstatfs  0x64    unsigned int fd struct statfs __user *buf       -       -       -     fs/statfs.c:197
%define sys_ioperm      0x65     ; sys_ioperm   0x65    unsigned long   unsigned long   int     -       -       not found:
%define sys_socketcall  0x66     ; sys_socketcall       0x66    int call        unsigned long __user *args      -       -     net/socket.c:2426
%define sys_syslog      0x67     ; sys_syslog   0x67    int type        char __user *buf        int len -       -       kernel/printk/printk.c:1541
%define sys_setitimer   0x68     ; sys_setitimer        0x68    int which       struct itimerval __user *value  struct itimerval __user *ovalue        -       -       kernel/time/itimer.c:292
%define sys_getitimer   0x69     ; sys_getitimer        0x69    int which       struct itimerval __user *value  -       -     kernel/time/itimer.c:107
%define sys_newstat     0x6a     ; sys_newstat  0x6a    const char __user *filename     struct stat __user *statbuf     -     fs/stat.c:333
%define sys_newlstat    0x6b     ; sys_newlstat 0x6b    const char __user *filename     struct stat __user *statbuf     -     fs/stat.c:344
%define sys_newfstat    0x6c     ; sys_newfstat 0x6c    unsigned int fd struct stat __user *statbuf     -       -       -     fs/stat.c:371
%define sys_uname       0x6d     ; sys_uname    0x6d    struct old_utsname __user *     -       -       -       -       kernel/sys.c:1195
%define sys_iopl        0x6e     ; sys_iopl     0x6e    unsigned int    -       -       -       -       arch/x86/kernel/ioport.c:109
%define sys_vhangup     0x6f     ; sys_vhangup  0x6f    -       -       -       -       -       fs/open.c:1172
%define not implemented 0x70     ; not implemented      0x70    -       -       -       -       -       :
%define sys_vm86old     0x71     ; sys_vm86old  0x71    struct vm86_struct __user *     -       -       -       -       arch/x86/kernel/vm86_32.c:209
%define sys_wait4       0x72     ; sys_wait4    0x72    pid_t pid       int __user *stat_addr   int options     struct rusage __user *ru       -       kernel/exit.c:1673
%define sys_swapoff     0x73     ; sys_swapoff  0x73    const char __user *specialfile  -       -       -       -       mm/swapfile.c:2526
%define sys_sysinfo     0x74     ; sys_sysinfo  0x74    struct sysinfo __user *info     -       -       -       -       kernel/sys.c:2475
%define sys_ipc 0x75     ; sys_ipc      0x75    -       -       -       -       -       ipc/syscall.c:17
%define sys_fsync       0x76     ; sys_fsync    0x76    unsigned int fd -       -       -       -       fs/sync.c:226
%define sys_sigreturn   0x77     ; sys_sigreturn        0x77    -       -       -       -       -       arch/s390/kernel/signal.c:217
%define sys_clone       0x78     ; sys_clone    0x78    unsigned long   unsigned long   int __user *    unsigned long   int __user *   kernel/fork.c:2137
%define sys_setdomainname       0x79     ; sys_setdomainname    0x79    char __user *name       int len -       -       -     kernel/sys.c:1300
%define sys_newuname    0x7a     ; sys_newuname 0x7a    struct new_utsname __user *name -       -       -       -       kernel/sys.c:1175
%define sys_modify_ldt  0x7b     ; sys_modify_ldt       0x7b    int     void __user *   unsigned long   -       -       not found:
%define sys_adjtimex    0x7c     ; sys_adjtimex 0x7c    struct timex __user *txc_p      -       -       -       -       kernel/time/time.c:301
%define sys_mprotect    0x7d     ; sys_mprotect 0x7d    unsigned long start     size_t len      unsigned long prot      -     mm/mprotect.c:512
%define sys_sigprocmask 0x7e     ; sys_sigprocmask      0x7e    int how old_sigset_t __user *set        old_sigset_t __user *oset      -       -       kernel/signal.c:3373
%define not implemented 0x7f     ; not implemented      0x7f    -       -       -       -       -       :
%define sys_init_module 0x80     ; sys_init_module      0x80    void __user *umod       unsigned long len       const char __user *uargs       -       -       kernel/module.c:3816
%define sys_delete_module       0x81     ; sys_delete_module    0x81    const char __user *name_user    unsigned int flags    kernel/module.c:954
%define not implemented 0x82     ; not implemented      0x82    -       -       -       -       -       :
%define sys_quotactl    0x83     ; sys_quotactl 0x83    unsigned int cmd        const char __user *special      qid_t id      void __user *addr        -       fs/quota/quota.c:836
%define sys_getpgid     0x84     ; sys_getpgid  0x84    pid_t pid       -       -       -       -       kernel/sys.c:1024
%define sys_fchdir      0x85     ; sys_fchdir   0x85    unsigned int fd -       -       -       -       fs/open.c:460
%define sys_bdflush     0x86     ; sys_bdflush  0x86    int func        long data       -       -       -       fs/buffer.c:3354
%define sys_sysfs       0x87     ; sys_sysfs    0x87    int option      unsigned long arg1      unsigned long arg2      -     fs/filesystems.c:186
%define sys_personality 0x88     ; sys_personality      0x88    unsigned int personality        -       -       -       -     kernel/exec_domain.c:51
%define not implemented 0x89     ; not implemented      0x89    -       -       -       -       -       :
%define sys_setfsuid16  0x8a     ; sys_setfsuid16       0x8a    old_uid_t uid   -       -       -       -       kernel/uid16.c:103
%define sys_setfsgid16  0x8b     ; sys_setfsgid16       0x8b    old_gid_t gid   -       -       -       -       kernel/uid16.c:108
%define sys_llseek      0x8c     ; sys_llseek   0x8c    unsigned int fd unsigned long offset_high       unsigned long offset_low       loff_t __user *result   unsigned int whence     fs/read_write.c:330
%define sys_getdents    0x8d     ; sys_getdents 0x8d    unsigned int fd struct linux_dirent __user *dirent      unsigned int count     -       -       fs/readdir.c:213
%define sys_select      0x8e     ; sys_select   0x8e    int n   fd_set __user *inp      fd_set __user *outp     fd_set __user *exp     struct timeval __user *tvp      fs/select.c:679
%define sys_flock       0x8f     ; sys_flock    0x8f    unsigned int fd unsigned int cmd        -       -       -       fs/locks.c:1996
%define sys_msync       0x90     ; sys_msync    0x90    unsigned long start     size_t len      int flags       -       -     mm/msync.c:32
%define sys_readv       0x91     ; sys_readv    0x91    unsigned long fd        const struct iovec __user *vec  unsigned long vlen     -       -       fs/read_write.c:1097
%define sys_writev      0x92     ; sys_writev   0x92    unsigned long fd        const struct iovec __user *vec  unsigned long vlen     -       -       fs/read_write.c:1103
%define sys_getsid      0x93     ; sys_getsid   0x93    pid_t pid       -       -       -       -       kernel/sys.c:1061
%define sys_fdatasync   0x94     ; sys_fdatasync        0x94    unsigned int fd -       -       -       -       fs/sync.c:231
%define sys_sysctl      0x95     ; sys_sysctl   0x95    struct __sysctl_args __user *args       -       -       -       -     kernel/sysctl_binary.c:1419
%define sys_mlock       0x96     ; sys_mlock    0x96    unsigned long start     size_t len      -       -       -       mm/mlock.c:711
%define sys_munlock     0x97     ; sys_munlock  0x97    unsigned long start     size_t len      -       -       -       mm/mlock.c:729
%define sys_mlockall    0x98     ; sys_mlockall 0x98    int flags       -       -       -       -       mm/mlock.c:790
%define sys_munlockall  0x99     ; sys_munlockall       0x99    -       -       -       -       -       mm/mlock.c:821
%define sys_sched_setparam      0x9a     ; sys_sched_setparam   0x9a    pid_t pid       struct sched_param __user *param      kernel/sched/core.c:4422
%define sys_sched_getparam      0x9b     ; sys_sched_getparam   0x9b    pid_t pid       struct sched_param __user *param      kernel/sched/core.c:4496
%define sys_sched_setscheduler  0x9c     ; sys_sched_setscheduler       0x9c    pid_t pid       int policy      struct sched_param __user *param       -       -       kernel/sched/core.c:4407
%define sys_sched_getscheduler  0x9d     ; sys_sched_getscheduler       0x9d    pid_t pid       -       -       -       -     kernel/sched/core.c:4467
%define sys_sched_yield 0x9e     ; sys_sched_yield      0x9e    -       -       -       -       -       kernel/sched/core.c:4813
%define sys_sched_get_priority_max      0x9f     ; sys_sched_get_priority_max   0x9f    int policy      -       -       -     kernel/sched/core.c:5045
%define sys_sched_get_priority_min      0xa0     ; sys_sched_get_priority_min   0xa0    int policy      -       -       -     kernel/sched/core.c:5072
%define sys_sched_rr_get_interval       0xa1     ; sys_sched_rr_get_interval    0xa1    pid_t pid       struct timespec __user *interval       -       -       -       kernel/sched/core.c:5101
%define sys_nanosleep   0xa2     ; sys_nanosleep        0xa2    struct timespec __user *rqtp    struct timespec __user *rmtp  kernel/time/hrtimer.c:1546
%define sys_mremap      0xa3     ; sys_mremap   0xa3    unsigned long addr      unsigned long old_len   unsigned long new_len unsigned long flags      unsigned long new_addr  mm/mremap.c:523
%define sys_setresuid16 0xa4     ; sys_setresuid16      0xa4    old_uid_t ruid  old_uid_t euid  old_uid_t suid  -       -     kernel/uid16.c:56
%define sys_getresuid16 0xa5     ; sys_getresuid16      0xa5    old_uid_t __user *ruid  old_uid_t __user *euid  old_uid_t __user *suid -       -       kernel/uid16.c:62
%define sys_vm86        0xa6     ; sys_vm86     0xa6    unsigned long   unsigned long   -       -       -       arch/x86/kernel/vm86_32.c:215
%define not implemented 0xa7     ; not implemented      0xa7    -       -       -       -       -       :
%define sys_poll        0xa8     ; sys_poll     0xa8    struct pollfd __user *ufds      unsigned int nfds       int timeout   fs/select.c:1016
%define not implemented 0xa9     ; not implemented      0xa9    -       -       -       -       -       :
%define sys_setresgid16 0xaa     ; sys_setresgid16      0xaa    old_gid_t rgid  old_gid_t egid  old_gid_t sgid  -       -     kernel/uid16.c:79
%define sys_getresgid16 0xab     ; sys_getresgid16      0xab    old_gid_t __user *rgid  old_gid_t __user *egid  old_gid_t __user *sgid -       -       kernel/uid16.c:86
%define sys_prctl       0xac     ; sys_prctl    0xac    int option      unsigned long arg2      unsigned long arg3      unsigned long arg4     unsigned long arg5      kernel/sys.c:2187
%define sys_rt_sigreturn        0xad     ; sys_rt_sigreturn     0xad    -       -       -       -       -       arch/arc/kernel/signal.c:154
%define sys_rt_sigaction        0xae     ; sys_rt_sigaction     0xae    int     const struct sigaction __user * struct sigaction __user *      size_t  -       kernel/signal.c:3421
%define sys_rt_sigprocmask      0xaf     ; sys_rt_sigprocmask   0xaf    int how sigset_t __user *set    sigset_t __user *oset size_t sigsetsize        -       kernel/signal.c:2569
%define sys_rt_sigpending       0xb0     ; sys_rt_sigpending    0xb0    sigset_t __user *set    size_t sigsetsize       -     kernel/signal.c:2659
%define sys_rt_sigtimedwait     0xb1     ; sys_rt_sigtimedwait  0xb1    const sigset_t __user *uthese   siginfo_t __user *uinfconst struct timespec __user *uts        size_t sigsetsize       -       kernel/signal.c:2883
%define sys_rt_sigqueueinfo     0xb2     ; sys_rt_sigqueueinfo  0xb2    pid_t pid       int sig siginfo_t __user *uinfo -     kernel/signal.c:3065
%define sys_rt_sigsuspend       0xb3     ; sys_rt_sigsuspend    0xb3    sigset_t __user *unewset        size_t sigsetsize     kernel/signal.c:3648
%define sys_pread64     0xb4     ; sys_pread64  0xb4    unsigned int fd char __user *buf        size_t count    loff_t pos    fs/read_write.c:598
%define sys_pwrite64    0xb5     ; sys_pwrite64 0xb5    unsigned int fd const char __user *buf  size_t count    loff_t pos    fs/read_write.c:618
%define sys_chown16     0xb6     ; sys_chown16  0xb6    const char __user *filename     old_uid_t user  old_gid_t group -     kernel/uid16.c:21
%define sys_getcwd      0xb7     ; sys_getcwd   0xb7    char __user *buf        unsigned long size      -       -       -     fs/dcache.c:3443
%define sys_capget      0xb8     ; sys_capget   0xb8    cap_user_header_t header        cap_user_data_t dataptr -       -     kernel/capability.c:150
%define sys_capset      0xb9     ; sys_capset   0xb9    cap_user_header_t header        const cap_user_data_t data      -     kernel/capability.c:224
%define sys_sigaltstack 0xba     ; sys_sigaltstack      0xba    const struct sigaltstack __user *uss    struct sigaltstack __user *uoss        -       -       -       kernel/signal.c:3245
%define sys_sendfile    0xbb     ; sys_sendfile 0xbb    int out_fd      int in_fd       off_t __user *offset    size_t count  fs/read_write.c:1462
%define not implemented 0xbc     ; not implemented      0xbc    -       -       -       -       -       :
%define not implemented 0xbd     ; not implemented      0xbd    -       -       -       -       -       :
%define sys_vfork       0xbe     ; sys_vfork    0xbe    -       -       -       -       -       kernel/fork.c:2128
%define sys_getrlimit   0xbf     ; sys_getrlimit        0xbf    unsigned int resource   struct rlimit __user *rlim      -     kernel/sys.c:1324
%define sys_mmap_pgoff  0xc0     ; sys_mmap_pgoff       0xc0    -       -       -       -       -       mm/mmap.c:1476
%define sys_truncate64  0xc1     ; sys_truncate64       0xc1    const char __user *path loff_t length   -       -       -     fs/open.c:227
%define sys_ftruncate64 0xc2     ; sys_ftruncate64      0xc2    unsigned int fd loff_t length   -       -       -       fs/open.c:232
%define sys_stat64      0xc3     ; sys_stat64   0xc3    const char __user *filename     struct stat64 __user *statbuf   -     fs/stat.c:467
%define sys_lstat64     0xc4     ; sys_lstat64  0xc4    const char __user *filename     struct stat64 __user *statbuf   -     fs/stat.c:479
%define sys_fstat64     0xc5     ; sys_fstat64  0xc5    unsigned long fd        struct stat64 __user *statbuf   -       -     fs/stat.c:491
%define sys_lchown      0xc6     ; sys_lchown   0xc6    const char __user *filename     uid_t user      gid_t group     -     fs/open.c:659
%define sys_getuid      0xc7     ; sys_getuid   0xc7    -       -       -       -       -       kernel/sys.c:866
%define sys_getgid      0xc8     ; sys_getgid   0xc8    -       -       -       -       -       kernel/sys.c:878
%define sys_geteuid     0xc9     ; sys_geteuid  0xc9    -       -       -       -       -       kernel/sys.c:872
%define sys_getegid     0xca     ; sys_getegid  0xca    -       -       -       -       -       kernel/sys.c:884
%define sys_setreuid    0xcb     ; sys_setreuid 0xcb    uid_t ruid      uid_t euid      -       -       -       kernel/sys.c:470
%define sys_setregid    0xcc     ; sys_setregid 0xcc    gid_t rgid      gid_t egid      -       -       -       kernel/sys.c:337
%define sys_getgroups   0xcd     ; sys_getgroups        0xcd    int gidsetsize  gid_t __user *grouplist -       -       -     kernel/groups.c:153
%define sys_setgroups   0xce     ; sys_setgroups        0xce    int gidsetsize  gid_t __user *grouplist -       -       -     kernel/groups.c:190
%define sys_fchown      0xcf     ; sys_fchown   0xcf    unsigned int fd uid_t user      gid_t group     -       -       fs/open.c:665
%define sys_setresuid   0xd0     ; sys_setresuid        0xd0    uid_t ruid      uid_t euid      uid_t suid      -       -     kernel/sys.c:588
%define sys_getresuid   0xd1     ; sys_getresuid        0xd1    uid_t __user *ruid      uid_t __user *euid      uid_t __user *suid     -       -       kernel/sys.c:653
%define sys_setresgid   0xd2     ; sys_setresgid        0xd2    gid_t rgid      gid_t egid      gid_t sgid      -       -     kernel/sys.c:675
%define sys_getresgid   0xd3     ; sys_getresgid        0xd3    gid_t __user *rgid      gid_t __user *egid      gid_t __user *sgid     -       -       kernel/sys.c:727
%define sys_chown       0xd4     ; sys_chown    0xd4    const char __user *filename     uid_t user      gid_t group     -     fs/open.c:654
%define sys_setuid      0xd5     ; sys_setuid   0xd5    uid_t uid       -       -       -       -       kernel/sys.c:541
%define sys_setgid      0xd6     ; sys_setgid   0xd6    gid_t gid       -       -       -       -       kernel/sys.c:394
%define sys_setfsuid    0xd7     ; sys_setfsuid 0xd7    uid_t uid       -       -       -       -       kernel/sys.c:754
%define sys_setfsgid    0xd8     ; sys_setfsgid 0xd8    gid_t gid       -       -       -       -       kernel/sys.c:793
%define sys_pivot_root  0xd9     ; sys_pivot_root       0xd9    const char __user *new_root     const char __user *put_old    fs/namespace.c:3118
%define sys_mincore     0xda     ; sys_mincore  0xda    unsigned long start     size_t len      unsigned char __user * vec    mm/mincore.c:224
%define sys_madvise     0xdb     ; sys_madvise  0xdb    unsigned long start     size_t len      int behavior    -       -     mm/madvise.c:793
%define sys_getdents64  0xdc     ; sys_getdents64       0xdc    unsigned int fd struct linux_dirent64 __user *dirent    unsigned int count     -       -       fs/readdir.c:296
%define sys_fcntl64     0xdd     ; sys_fcntl64  0xdd    unsigned int fd unsigned int cmd        unsigned long arg       -     fs/fcntl.c:472
%define not implemented 0xde     ; not implemented      0xde    -       -       -       -       -       :
%define not implemented 0xdf     ; not implemented      0xdf    -       -       -       -       -       :
%define sys_gettid      0xe0     ; sys_gettid   0xe0    -       -       -       -       -       kernel/sys.c:844
%define sys_readahead   0xe1     ; sys_readahead        0xe1    int fd  loff_t offset   size_t count    -       -       mm/readahead.c:576
%define sys_setxattr    0xe2     ; sys_setxattr 0xe2    const char __user *path const char __user *name const void __user *value       size_t size     int flags       fs/xattr.c:483
%define sys_lsetxattr   0xe3     ; sys_lsetxattr        0xe3    const char __user *path const char __user *name const void __user *value       size_t size     int flags       fs/xattr.c:490
%define sys_fsetxattr   0xe4     ; sys_fsetxattr        0xe4    int fd  const char __user *name const void __user *value      size_t size      int flags       fs/xattr.c:497
%define sys_getxattr    0xe5     ; sys_getxattr 0xe5    const char __user *path const char __user *name void __user *value    size_t size      -       fs/xattr.c:577
%define sys_lgetxattr   0xe6     ; sys_lgetxattr        0xe6    const char __user *path const char __user *name void __user *value     size_t size     -       fs/xattr.c:583
%define sys_fgetxattr   0xe7     ; sys_fgetxattr        0xe7    int fd  const char __user *name void __user *value      size_t size    -       fs/xattr.c:589
%define sys_listxattr   0xe8     ; sys_listxattr        0xe8    const char __user *path char __user *list       size_t size   fs/xattr.c:653
%define sys_llistxattr  0xe9     ; sys_llistxattr       0xe9    const char __user *path char __user *list       size_t size   fs/xattr.c:659
%define sys_flistxattr  0xea     ; sys_flistxattr       0xea    int fd  char __user *list       size_t size     -       -     fs/xattr.c:665
%define sys_removexattr 0xeb     ; sys_removexattr      0xeb    const char __user *path const char __user *name -       -     fs/xattr.c:718
%define sys_lremovexattr        0xec     ; sys_lremovexattr     0xec    const char __user *path const char __user *name -     fs/xattr.c:724
%define sys_fremovexattr        0xed     ; sys_fremovexattr     0xed    int fd  const char __user *name -       -       -     fs/xattr.c:730
%define sys_tkill       0xee     ; sys_tkill    0xee    pid_t pid       int sig -       -       -       kernel/signal.c:3035
%define sys_sendfile64  0xef     ; sys_sendfile64       0xef    int out_fd      int in_fd       loff_t __user *offset   size_t count   -       fs/read_write.c:1481
%define sys_futex       0xf0     ; sys_futex    0xf0    -       -       -       -       -       kernel/futex.c:3519
%define sys_sched_setaffinity   0xf1     ; sys_sched_setaffinity        0xf1    pid_t pid       unsigned int len        unsigned long __user *user_mask_ptr    -       -       kernel/sched/core.c:4725
%define sys_sched_getaffinity   0xf2     ; sys_sched_getaffinity        0xf2    pid_t pid       unsigned int len        unsigned long __user *user_mask_ptr    -       -       kernel/sched/core.c:4777
%define sys_set_thread_area     0xf3     ; sys_set_thread_area  0xf3    struct user_desc __user *       -       -       -     arch/mips/kernel/syscall.c:82
%define sys_get_thread_area     0xf4     ; sys_get_thread_area  0xf4    struct user_desc __user *       -       -       -     arch/x86/kernel/tls.c:245
%define sys_io_setup    0xf5     ; sys_io_setup 0xf5    unsigned nr_reqs        aio_context_t __user *ctx       -       -     fs/aio.c:1354
%define sys_io_destroy  0xf6     ; sys_io_destroy       0xf6    aio_context_t ctx       -       -       -       -       fs/aio.c:1423
%define sys_io_getevents        0xf7     ; sys_io_getevents     0xf7    aio_context_t ctx_id    long min_nr     long nr struct io_event __user *events struct timespec __user *timeout fs/aio.c:1841
%define sys_io_submit   0xf8     ; sys_io_submit        0xf8    aio_context_t   long    struct iocb __user * __user *   -     fs/aio.c:1714
%define sys_io_cancel   0xf9     ; sys_io_cancel        0xf9    aio_context_t ctx_id    struct iocb __user *iocb        struct io_event __user *result -       -       fs/aio.c:1789
%define sys_fadvise64   0xfa     ; sys_fadvise64        0xfa    int fd  loff_t offset   size_t len      int advice      -     mm/fadvise.c:182
%define not implemented 0xfb     ; not implemented      0xfb    -       -       -       -       -       :
%define sys_exit_group  0xfc     ; sys_exit_group       0xfc    int error_code  -       -       -       -       kernel/exit.c:977
%define sys_lookup_dcookie      0xfd     ; sys_lookup_dcookie   0xfd    u64 cookie64    char __user *buf        size_t len    fs/dcookies.c:149
%define sys_epoll_create        0xfe     ; sys_epoll_create     0xfe    int size        -       -       -       -       fs/eventpoll.c:1999
%define sys_epoll_ctl   0xff     ; sys_epoll_ctl        0xff    int epfd        int op  int fd  struct epoll_event __user *event       -       fs/eventpoll.c:2012
%define sys_epoll_wait  0x100    ; sys_epoll_wait       0x100   int epfd        struct epoll_event __user *events       int maxevents  int timeout     -       fs/eventpoll.c:2168
%define sys_remap_file_pages    0x101    ; sys_remap_file_pages 0x101   unsigned long start     unsigned long size      unsigned long prot     unsigned long pgoff     unsigned long flags     mm/mmap.c:2745
%define sys_set_tid_address     0x102    ; sys_set_tid_address  0x102   int __user *tidptr      -       -       -       -     kernel/fork.c:1476
%define sys_timer_create        0x103    ; sys_timer_create     0x103   clockid_t which_clock   struct sigevent __user *timer_event_spec       timer_t __user * created_timer_id       -       -       kernel/time/posix
%define sys_timer_settime       0x104    ; sys_timer_settime    0x104   timer_t timer_id        int flags       const struct itimerspec __user *new_setting    struct itimerspec __user *old_setting   -       kernel/time/posix-timers.c:902
%define sys_timer_gettime       0x105    ; sys_timer_gettime    0x105   timer_t timer_id        struct itimerspec __user *setting      -       -       -       kernel/time/posix-timers.c:739
%define sys_timer_getoverrun    0x106    ; sys_timer_getoverrun 0x106   timer_t timer_id        -       -       -       -     kernel/time/posix-timers.c:776
%define sys_timer_delete        0x107    ; sys_timer_delete     0x107   timer_t timer_id        -       -       -       -     kernel/time/posix-timers.c:968
%define sys_clock_settime       0x108    ; sys_clock_settime    0x108   clockid_t which_clock   const struct timespec __user *tp       -       -       -       kernel/time/posix-stubs.c:51
%define sys_clock_gettime       0x109    ; sys_clock_gettime    0x109   clockid_t which_clock   struct timespec __user *tp    kernel/time/posix-stubs.c:82
%define sys_clock_getres        0x10a    ; sys_clock_getres     0x10a   clockid_t which_clock   struct timespec __user *tp    kernel/time/posix-stubs.c:97
%define sys_clock_nanosleep     0x10b    ; sys_clock_nanosleep  0x10b   clockid_t which_clock   int flags       const struct timespec __user *rqtp     struct timespec __user *rmtp    -       kernel/time/posix-stubs.c:116
%define sys_statfs64    0x10c    ; sys_statfs64 0x10c   const char __user *path size_t sz       struct statfs64 __user *buf   fs/statfs.c:185
%define sys_fstatfs64   0x10d    ; sys_fstatfs64        0x10d   unsigned int fd size_t sz       struct statfs64 __user *buf   fs/statfs.c:206
%define sys_tgkill      0x10e    ; sys_tgkill   0x10e   pid_t tgid      pid_t pid       int sig -       -       kernel/signal.c:3019
%define sys_utimes      0x10f    ; sys_utimes   0x10f   char __user *filename   struct timeval __user *utimes   -       -     fs/utimes.c:215
%define sys_fadvise64_64        0x110    ; sys_fadvise64_64     0x110   int fd  loff_t offset   loff_t len      int advice    mm/fadvise.c:29
%define not implemented 0x111    ; not implemented      0x111   -       -       -       -       -       :
%define sys_mbind       0x112    ; sys_mbind    0x112   -       -       -       -       -       mm/mempolicy.c:1323
%define sys_get_mempolicy       0x113    ; sys_get_mempolicy    0x113   int __user *policy      unsigned long __user *nmask   unsigned long maxnode    unsigned long addr      unsigned long flags     mm/mempolicy.c:1460
%define sys_set_mempolicy       0x114    ; sys_set_mempolicy    0x114   int mode        const unsigned long __user *nmask     unsigned long maxnode    -       -       mm/mempolicy.c:1345
%define sys_mq_open     0x115    ; sys_mq_open  0x115   const char __user *name int oflag       umode_t mode    struct mq_attr __user *attr    -       ipc/mqueue.c:847
%define sys_mq_unlink   0x116    ; sys_mq_unlink        0x116   const char __user *name -       -       -       -       ipc/mqueue.c:857
%define sys_mq_timedsend        0x117    ; sys_mq_timedsend     0x117   mqd_t mqdes     const char __user *msg_ptr      size_t msg_len unsigned int msg_prio   const struct timespec __user *abs_timeout       ipc/mqueue.c:1183
%define sys_mq_timedreceive     0x118    ; sys_mq_timedreceive  0x118   mqd_t mqdes     char __user *msg_ptr    size_t msg_lenunsigned int __user *msg_prio    const struct timespec __user *abs_timeout       ipc/mqueue.c:1197
%define sys_mq_notify   0x119    ; sys_mq_notify        0x119   mqd_t mqdes     const struct sigevent __user *notification    ipc/mqueue.c:1342
%define sys_mq_getsetattr       0x11a    ; sys_mq_getsetattr    0x11a   mqd_t mqdes     const struct mq_attr __user *mqstat   struct mq_attr __user *omqstat   -       -       ipc/mqueue.c:1398
%define sys_kexec_load  0x11b    ; sys_kexec_load       0x11b   unsigned long entry     unsigned long nr_segments       struct kexec_segment __user *segments  unsigned long flags     -       kernel/kexec.c:195
%define sys_waitid      0x11c    ; sys_waitid   0x11c   int which       pid_t pid       struct siginfo __user *infop    int options    struct rusage __user *ru        kernel/exit.c:1596
%define not implemented 0x11d    ; not implemented      0x11d   -       -       -       -       -       :
%define sys_add_key     0x11e    ; sys_add_key  0x11e   const char __user *_type        const char __user *_description const void __user *_payload    size_t plen     key_serial_t destringid security/keys/keyctl.c:62
%define sys_request_key 0x11f    ; sys_request_key      0x11f   const char __user *_type        const char __user *_descriptioconst char __user *_callout_info key_serial_t destringid -       security/keys/keyctl.c:158
%define sys_keyctl      0x120    ; sys_keyctl   0x120   int cmd unsigned long arg2      unsigned long arg3      unsigned long arg4     unsigned long arg5      security/keys/keyctl.c:1641
%define sys_ioprio_set  0x121    ; sys_ioprio_set       0x121   int which       int who int ioprio      -       -       block/ioprio.c:64
%define sys_ioprio_get  0x122    ; sys_ioprio_get       0x122   int which       int who -       -       -       block/ioprio.c:175
%define sys_inotify_init        0x123    ; sys_inotify_init     0x123   -       -       -       -       -       fs/notify/inotify/inotify_user.c:663
%define sys_inotify_add_watch   0x124    ; sys_inotify_add_watch        0x124   int fd  const char __user *path u32 mask      fs/notify/inotify/inotify_user.c:668
%define sys_inotify_rm_watch    0x125    ; sys_inotify_rm_watch 0x125   int fd  __s32 wd        -       -       -       fs/notify/inotify/inotify_user.c:725
%define sys_migrate_pages       0x126    ; sys_migrate_pages    0x126   pid_t pid       unsigned long maxnode   const unsigned long __user *from       const unsigned long __user *to  -       mm/mempolicy.c:1364
%define sys_openat      0x127    ; sys_openat   0x127   int dfd const char __user *filename     int flags       umode_t mode  fs/open.c:1080
%define sys_mkdirat     0x128    ; sys_mkdirat  0x128   int dfd const char __user * pathname    umode_t mode    -       -     fs/namei.c:3816
%define sys_mknodat     0x129    ; sys_mknodat  0x129   int dfd const char __user * filename    umode_t mode    unsigned dev  fs/namei.c:3741
%define sys_fchownat    0x12a    ; sys_fchownat 0x12a   int dfd const char __user *filename     uid_t user      gid_t group   int flag fs/open.c:622
%define sys_futimesat   0x12b    ; sys_futimesat        0x12b   int dfd const char __user *filename     struct timeval __user *utimes  -       -       fs/utimes.c:187
%define sys_fstatat64   0x12c    ; sys_fstatat64        0x12c   int dfd const char __user *filename     struct stat64 __user *statbuf  int flag        -       fs/stat.c:502
%define sys_unlinkat    0x12d    ; sys_unlinkat 0x12d   int dfd const char __user * pathname    int flag        -       -     fs/namei.c:4086
%define sys_renameat    0x12e    ; sys_renameat 0x12e   int olddfd      const char __user * oldname     int newdfd      const char __user * newname    -       fs/namei.c:4636
%define sys_linkat      0x12f    ; sys_linkat   0x12f   int olddfd      const char __user *oldname      int newdfd      const char __user *newname     int flags       fs/namei.c:4248
%define sys_symlinkat   0x130    ; sys_symlinkat        0x130   const char __user * oldname     int newdfd      const char __user * newname    -       -       fs/namei.c:4123
%define sys_readlinkat  0x131    ; sys_readlinkat       0x131   int dfd const char __user *path char __user *buf        int bufsiz     -       fs/stat.c:382
%define sys_fchmodat    0x132    ; sys_fchmodat 0x132   int dfd const char __user * filename    umode_t mode    -       -     fs/open.c:557
%define sys_faccessat   0x133    ; sys_faccessat        0x133   int dfd const char __user *filename     int mode        -     fs/open.c:353
%define sys_pselect6    0x134    ; sys_pselect6 0x134   -       -       -       -       -       fs/select.c:759
%define sys_ppoll       0x135    ; sys_ppoll    0x135   struct pollfd __user *ufds      unsigned int nfds       struct timespec __user *tsp    const sigset_t __user *sigmask  size_t sigsetsize       fs/select.c:1050
%define sys_unshare     0x136    ; sys_unshare  0x136   unsigned long unshare_flags     -       -       -       -       kernel/fork.c:2320
%define sys_set_robust_list     0x137    ; sys_set_robust_list  0x137   struct robust_list_head __user *head    size_t len    kernel/futex.c:3262
%define sys_get_robust_list     0x138    ; sys_get_robust_list  0x138   int pid struct robust_list_head __user * __user *head_ptr      size_t __user *len_ptr  -       -       kernel/futex.c:3284
%define sys_splice      0x139    ; sys_splice   0x139   -       -       -       -       -       fs/splice.c:1382
%define sys_sync_file_range     0x13a    ; sys_sync_file_range  0x13a   int fd  loff_t offset   loff_t nbytes   unsigned int flags     -       fs/sync.c:283
%define sys_tee 0x13b    ; sys_tee      0x13b   int fdin        int fdout       size_t len      unsigned int flags      -     fs/splice.c:1718
%define sys_vmsplice    0x13c    ; sys_vmsplice 0x13c   int fd  const struct iovec __user *iov  unsigned long nr_segs   unsigned int flags     -       fs/splice.c:1334
%define sys_move_pages  0x13d    ; sys_move_pages       0x13d   -       -       -       -       -       mm/migrate.c:1749
%define sys_getcpu      0x13e    ; sys_getcpu   0x13e   unsigned __user *cpu    unsigned __user *node   struct getcpu_cache __user *cache      -       -       kernel/sys.c:2396
%define sys_epoll_pwait 0x13f    ; sys_epoll_pwait      0x13f   -       -       -       -       -       fs/eventpoll.c:2214
%define sys_utimensat   0x140    ; sys_utimensat        0x140   int dfd const char __user *filename     struct timespec __user *utimes int flags       -       fs/utimes.c:168
%define sys_signalfd    0x141    ; sys_signalfd 0x141   int ufd sigset_t __user *user_mask      size_t sizemask -       -     fs/signalfd.c:304
%define sys_timerfd_create      0x142    ; sys_timerfd_create   0x142   int clockid     int flags       -       -       -     fs/timerfd.c:387
%define sys_eventfd     0x143    ; sys_eventfd  0x143   unsigned int count      -       -       -       -       fs/eventfd.c:483
%define sys_fallocate   0x144    ; sys_fallocate        0x144   int fd  int mode        loff_t offset   loff_t len      -     fs/open.c:336
%define sys_timerfd_settime     0x145    ; sys_timerfd_settime  0x145   int ufd int flags       const struct itimerspec __user *utmr   struct itimerspec __user *otmr  -       fs/timerfd.c:535
%define sys_timerfd_gettime     0x146    ; sys_timerfd_gettime  0x146   int ufd struct itimerspec __user *otmr  -       -     fs/timerfd.c:553
%define sys_signalfd4   0x147    ; sys_signalfd4        0x147   int ufd sigset_t __user *user_mask      size_t sizemask int flags      -       fs/signalfd.c:250
%define sys_eventfd2    0x148    ; sys_eventfd2 0x148   unsigned int count      int flags       -       -       -       fs/eventfd.c:458
%define sys_epoll_create1       0x149    ; sys_epoll_create1    0x149   int flags       -       -       -       -       fs/eventpoll.c:1956
%define sys_dup3        0x14a    ; sys_dup3     0x14a   unsigned int oldfd      unsigned int newfd      int flags       -     fs/file.c:876
%define sys_pipe2       0x14b    ; sys_pipe2    0x14b   int __user *fildes      int flags       -       -       -       fs/pipe.c:839
%define sys_inotify_init1       0x14c    ; sys_inotify_init1    0x14c   int flags       -       -       -       -       fs/notify/inotify/inotify_user.c:638
%define sys_preadv      0x14d    ; sys_preadv   0x14d   unsigned long fd        const struct iovec __user *vec  unsigned long vlen     unsigned long pos_l     unsigned long pos_h     fs/read_write.c:1109
%define sys_pwritev     0x14e    ; sys_pwritev  0x14e   unsigned long fd        const struct iovec __user *vec  unsigned long vlen     unsigned long pos_l     unsigned long pos_h     fs/read_write.c:1129
%define sys_rt_tgsigqueueinfo   0x14f    ; sys_rt_tgsigqueueinfo        0x14f   pid_t tgid      pid_t pid       int sig siginfo_t __user *uinfo        -       kernel/signal.c:3106
%define sys_perf_event_open     0x150    ; sys_perf_event_open  0x150   struct perf_event_attr __user *attr_uptr        pid_t pid      int cpu int group_fd    unsigned long flags     kernel/events/core.c:9910
%define sys_recvmmsg    0x151    ; sys_recvmmsg 0x151   int fd  struct mmsghdr __user *msg      unsigned int vlen       unsigned flags struct timespec __user *timeout net/socket.c:2381
%define sys_fanotify_init       0x152    ; sys_fanotify_init    0x152   unsigned int flags      unsigned int event_f_flags    fs/notify/fanotify/fanotify_user.c:712
%define sys_fanotify_mark       0x153    ; sys_fanotify_mark    0x153   int fanotify_fd unsigned int flags      u64 mask      int fd   const char __user *pathname     fs/notify/fanotify/fanotify_user.c:820
%define sys_prlimit64   0x154    ; sys_prlimit64        0x154   pid_t pid       unsigned int resource   const struct rlimit64 __user *new_rlim struct rlimit64 __user *old_rlim        -       kernel/sys.c:1555
%define sys_name_to_handle_at   0x155    ; sys_name_to_handle_at        0x155   int dfd const char __user *name struct file_handle __user *handle      int __user *mnt_id      int flag        fs/fhandle.c:94
%define sys_open_by_handle_at   0x156    ; sys_open_by_handle_at        0x156   int mountdirfd  struct file_handle __user *handle      int flags       -       -       fs/fhandle.c:257
%define sys_clock_adjtime       0x157    ; sys_clock_adjtime    0x157   clockid_t which_clock   struct timex __user *tx -     kernel/time/posix-timers.c:1069
%define sys_syncfs      0x158    ; sys_syncfs   0x158   int fd  -       -       -       -       fs/sync.c:155
%define sys_sendmmsg    0x159    ; sys_sendmmsg 0x159   int fd  struct mmsghdr __user *msg      unsigned int vlen       unsigned flags -       net/socket.c:2165
%define sys_setns       0x15a    ; sys_setns    0x15a   int fd  int nstype      -       -       -       kernel/nsproxy.c:237
%define sys_process_vm_readv    0x15b    ; sys_process_vm_readv 0x15b   -       -       -       -       -       mm/process_vm_access.c:300
%define sys_process_vm_writev   0x15c    ; sys_process_vm_writev        0x15c   -       -       -       -       -       mm/process_vm_access.c:307
%define sys_kcmp        0x15d    ; sys_kcmp     0x15d   pid_t pid1      pid_t pid2      int type        unsigned long idx1    unsigned long idx2       kernel/kcmp.c:152
%define sys_finit_module        0x15e    ; sys_finit_module     0x15e   int fd  const char __user *uargs        int flags     kernel/module.c:3836
%define sys_sched_setattr       0x15f    ; sys_sched_setattr    0x15f   pid_t pid       struct sched_attr __user *attr  unsigned int flags     -       -       kernel/sched/core.c:4433
%define sys_sched_getattr       0x160    ; sys_sched_getattr    0x160   pid_t pid       struct sched_attr __user *attr  unsigned int size      unsigned int flags      -       kernel/sched/core.c:4574
%define sys_renameat2   0x161    ; sys_renameat2        0x161   int olddfd      const char __user *oldname      int newdfd    const char __user *newname       unsigned int flags      fs/namei.c:4493
%define sys_seccomp     0x162    ; sys_seccomp  0x162   unsigned int op unsigned int flags      const char __user *uargs      kernel/seccomp.c:940
%define sys_getrandom   0x163    ; sys_getrandom        0x163   char __user *buf        size_t count    unsigned int flags    drivers/char/random.c:1908
%define sys_memfd_create        0x164    ; sys_memfd_create     0x164   const char __user *uname_ptr    unsigned int flags    mm/shmem.c:3658
%define sys_bpf 0x165    ; sys_bpf      0x165   int cmd union bpf_attr *attr    unsigned int size       -       -       kernel/bpf/syscall.c:1453
%define sys_execveat    0x166    ; sys_execveat 0x166   int dfd const char __user *filename     const char __user *const __user *argv  const char __user *const __user *envp   int flags       fs/exec.c:1927
%define sys_socket      0x167    ; sys_socket   0x167   int     int     int     -       -       net/socket.c:1312
%define sys_socketpair  0x168    ; sys_socketpair       0x168   int     int     int     int __user *    -       net/socket.c:1353
%define sys_bind        0x169    ; sys_bind     0x169   int     struct sockaddr __user *        int     -       -       net/socket.c:1462
%define sys_connect     0x16a    ; sys_connect  0x16a   int     struct sockaddr __user *        int     -       -       net/socket.c:1623
%define sys_listen      0x16b    ; sys_listen   0x16b   int     int     -       -       -       net/socket.c:1491
%define sys_accept4     0x16c    ; sys_accept4  0x16c   int     struct sockaddr __user *        int __user *    int     -     net/socket.c:1524
%define sys_getsockopt  0x16d    ; sys_getsockopt       0x16d   int fd  int level       int optname     char __user *optval   int __user *optlen       net/socket.c:1865
%define sys_setsockopt  0x16e    ; sys_setsockopt       0x16e   int fd  int level       int optname     char __user *optval   int optlen       net/socket.c:1831
%define sys_getsockname 0x16f    ; sys_getsockname      0x16f   int     struct sockaddr __user *        int __user *    -     net/socket.c:1655
%define sys_getpeername 0x170    ; sys_getpeername      0x170   int     struct sockaddr __user *        int __user *    -     net/socket.c:1686
%define sys_sendto      0x171    ; sys_sendto   0x171   -       -       -       -       -       net/socket.c:1718
%define sys_sendmsg     0x172    ; sys_sendmsg  0x172   int fd  struct user_msghdr __user *msg  unsigned flags  -       -     net/socket.c:2090
%define sys_recvfrom    0x173    ; sys_recvfrom 0x173   -       -       -       -       -       net/socket.c:1774
%define sys_recvmsg     0x174    ; sys_recvmsg  0x174   int fd  struct user_msghdr __user *msg  unsigned flags  -       -     net/socket.c:2260
%define sys_shutdown    0x175    ; sys_shutdown 0x175   int     int     -       -       -       net/socket.c:1895
%define sys_userfaultfd 0x176    ; sys_userfaultfd      0x176   int flags       -       -       -       -       fs/userfaultfd.c:1924
%define sys_membarrier  0x177    ; sys_membarrier       0x177   int cmd int flags       -       -       -       kernel/sched/membarrier.c:150
%define sys_mlock2      0x178    ; sys_mlock2   0x178   unsigned long start     size_t len      int flags       -       -     mm/mlock.c:716
%define sys_copy_file_range     0x179    ; sys_copy_file_range  0x179   -       -       -       -       -       fs/read_write.c:1621
%define sys_preadv2     0x17a    ; sys_preadv2  0x17a   -       -       -       -       -       fs/read_write.c:1117
%define sys_pwritev2    0x17b    ; sys_pwritev2 0x17b   -       -       -       -       -       fs/read_write.c:1137
%define sys_pkey_mprotect       0x17c    ; sys_pkey_mprotect    0x17c   unsigned long start     size_t len      unsigned long prot     int pkey        -       mm/mprotect.c:520
%define sys_pkey_alloc  0x17d    ; sys_pkey_alloc       0x17d   unsigned long flags     unsigned long init_val  -       -     mm/mprotect.c:526
%define sys_pkey_free   0x17e    ; sys_pkey_free        0x17e   int pkey        -       -       -       -       mm/mprotect.c:556
%define sys_statx       0x17f    ; sys_statx    0x17f   int dfd const char __user *path unsigned flags  unsigned mask   struct statx __user *buffer    fs/stat.c:560
%define sys_arch_prctl  0x180    ; sys_arch_prctl       0x180   int     unsigned long   -       -       -       arch/x86/kernel/process_32.c:310
