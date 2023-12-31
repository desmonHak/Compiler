 ;	Licencia Apache, Versión 2.0 con Modificación
 ;	
 ;	Copyright 2023 Desmon (David)
 ;	
 ;	Se concede permiso, de forma gratuita, a cualquier persona que obtenga una copia de 
 ;	este software y archivos de documentación asociados (el "Software"), para tratar el 
 ;	Software sin restricciones, incluidos, entre otros, los derechos de uso, copia, 
 ;	modificación, fusión, publicación, distribución, sublicencia y/o venta de copias del 
 ;	Software, y para permitir a las personas a quienes se les proporcione el Software 
 ;	hacer lo mismo, sujeto a las siguientes condiciones:
 ;	
 ;	El anterior aviso de copyright y este aviso de permiso se incluirán en todas las 
 ;	copias o partes sustanciales del Software.
 ;	
 ;	EL SOFTWARE SE PROPORCIONA "TAL CUAL", SIN GARANTÍA DE NINGÚN TIPO, EXPRESA O 
 ;	IMPLÍCITA, INCLUYENDO PERO NO LIMITADO A LAS GARANTÍAS DE COMERCIABILIDAD, IDONEIDAD 
 ;	PARA UN PROPÓSITO PARTICULAR Y NO INFRACCIÓN. EN NINGÚN CASO LOS TITULARES DEL 
 ;	COPYRIGHT O LOS TITULARES DE LOS DERECHOS DE AUTOR SERÁN RESPONSABLES DE NINGÚN 
 ;	RECLAMO, DAÑO U OTRA RESPONSABILIDAD, YA SEA EN UNA ACCIÓN DE CONTRATO, AGRAVIO O DE 
 ;	OTRA MANERA, QUE SURJA DE, FUERA DE O EN CONEXIÓN CON EL SOFTWARE O EL USO U OTRO TIPO
 ;	DE ACCIONES EN EL SOFTWARE.
 ;	
 ;	Además, cualquier modificación realizada por terceros se considerará propiedad del 
 ;	titular original de los derechos de autor. Los titulares de derechos de autor 
 ;	originales no se responsabilizan de las modificaciones realizadas por terceros.
 ;	
 ;	Queda explícitamente establecido que no es obligatorio especificar ni notificar los 
 ;	cambios realizados entre versiones, ni revelar porciones específicas de código 
 ;	modificado.
 ;

%define sys_read        0        ; read fs/read_write.c
%define sys_write       1        ; write        fs/read_write.c
%define sys_open        2        ; open fs/open.c
%define sys_close       3        ; close        fs/open.c
%define sys_newstat     4        ; stat fs/stat.c
%define sys_newfstat    5        ; fstat        fs/stat.c
%define sys_newlstat    6        ; lstat        fs/stat.c
%define sys_poll        7        ; poll fs/select.c
%define sys_lseek       8        ; lseek        fs/read_write.c
%define sys_mmap        9        ; mmap arch/x86/kernel/sys_x86_64.c
%define sys_mprotect    10       ; mprotect     mm/mprotect.c
%define sys_munmap      11       ; munmap       mm/mmap.c
%define sys_brk         12       ; brk  mm/mmap.c
%define sys_rt_sigaction        13       ; rt_sigaction kernel/signal.c
%define sys_rt_sigprocmask      14       ; rt_sigprocmask       kernel/signal.c
%define stub_rt_sigreturn       15       ; rt_sigreturn arch/x86/kernel/signal.c
%define sys_ioctl       16       ; ioctl        fs/ioctl.c
%define sys_pread64     17       ; pread64      fs/read_write.c
%define sys_pwrite64    18       ; pwrite64     fs/read_write.c
%define sys_readv       19       ; readv        fs/read_write.c
%define sys_writev      20       ; writev       fs/read_write.c
%define sys_access      21       ; access       fs/open.c
%define sys_pipe        22       ; pipe fs/pipe.c
%define sys_select      23       ; select       fs/select.c
%define sys_sched_yield 24       ; sched_yield  kernel/sched/core.c
%define sys_mremap      25       ; mremap       mm/mmap.c
%define sys_msync       26       ; msync        mm/msync.c
%define sys_mincore     27       ; mincore      mm/mincore.c
%define sys_madvise     28       ; madvise      mm/madvise.c
%define sys_shmget      29       ; shmget       ipc/shm.c
%define sys_shmat       30       ; shmat        ipc/shm.c
%define sys_shmctl      31       ; shmctl       ipc/shm.c
%define sys_dup         32       ; dup  fs/file.c
%define sys_dup2        33       ; dup2 fs/file.c
%define sys_pause       34       ; pause        kernel/signal.c
%define sys_nanosleep   35       ; nanosleep    kernel/hrtimer.c
%define sys_getitimer   36       ; getitimer    kernel/itimer.c
%define sys_alarm       37       ; alarm        kernel/timer.c
%define sys_setitimer   38       ; setitimer    kernel/itimer.c
%define sys_getpid      39       ; getpid       kernel/sys.c
%define sys_sendfile64  40       ; sendfile     fs/read_write.c
%define sys_socket      41       ; socket       net/socket.c
%define sys_connect     42       ; connect      net/socket.c
%define sys_accept      43       ; accept       net/socket.c
%define sys_sendto      44       ; sendto       net/socket.c
%define sys_recvfrom    45       ; recvfrom     net/socket.c
%define sys_sendmsg     46       ; sendmsg      net/socket.c
%define sys_recvmsg     47       ; recvmsg      net/socket.c
%define sys_shutdown    48       ; shutdown     net/socket.c
%define sys_bind        49       ; bind net/socket.c
%define sys_listen      50       ; listen       net/socket.c
%define sys_getsockname 51       ; getsockname  net/socket.c
%define sys_getpeername 52       ; getpeername  net/socket.c
%define sys_socketpair  53       ; socketpair   net/socket.c
%define sys_setsockopt  54       ; setsockopt   net/socket.c
%define sys_getsockopt  55       ; getsockopt   net/socket.c
%define stub_clone      56       ; clone        kernel/fork.c
%define stub_fork       57       ; fork kernel/fork.c
%define stub_vfork      58       ; vfork        kernel/fork.c
%define stub_execve     59       ; execve       fs/exec.c
%define sys_exit        60       ; exit kernel/exit.c
%define sys_wait4       61       ; wait4        kernel/exit.c
%define sys_kill        62       ; kill kernel/signal.c
%define sys_newuname    63       ; uname        kernel/sys.c
%define sys_semget      64       ; semget       ipc/sem.c
%define sys_semop       65       ; semop        ipc/sem.c
%define sys_semctl      66       ; semctl       ipc/sem.c
%define sys_shmdt       67       ; shmdt        ipc/shm.c
%define sys_msgget      68       ; msgget       ipc/msg.c
%define sys_msgsnd      69       ; msgsnd       ipc/msg.c
%define sys_msgrcv      70       ; msgrcv       ipc/msg.c
%define sys_msgctl      71       ; msgctl       ipc/msg.c
%define sys_fcntl       72       ; fcntl        fs/fcntl.c
%define sys_flock       73       ; flock        fs/locks.c
%define sys_fsync       74       ; fsync        fs/sync.c
%define sys_fdatasync   75       ; fdatasync    fs/sync.c
%define sys_truncate    76       ; truncate     fs/open.c
%define sys_ftruncate   77       ; ftruncate    fs/open.c
%define sys_getdents    78       ; getdents     fs/readdir.c
%define sys_getcwd      79       ; getcwd       fs/dcache.c
%define sys_chdir       80       ; chdir        fs/open.c
%define sys_fchdir      81       ; fchdir       fs/open.c
%define sys_rename      82       ; rename       fs/namei.c
%define sys_mkdir       83       ; mkdir        fs/namei.c
%define sys_rmdir       84       ; rmdir        fs/namei.c
%define sys_creat       85       ; creat        fs/open.c
%define sys_link        86       ; link fs/namei.c
%define sys_unlink      87       ; unlink       fs/namei.c
%define sys_symlink     88       ; symlink      fs/namei.c
%define sys_readlink    89       ; readlink     fs/stat.c
%define sys_chmod       90       ; chmod        fs/open.c
%define sys_fchmod      91       ; fchmod       fs/open.c
%define sys_chown       92       ; chown        fs/open.c
%define sys_fchown      93       ; fchown       fs/open.c
%define sys_lchown      94       ; lchown       fs/open.c
%define sys_umask       95       ; umask        kernel/sys.c
%define sys_gettimeofday        96       ; gettimeofday kernel/time.c
%define sys_getrlimit   97       ; getrlimit    kernel/sys.c
%define sys_getrusage   98       ; getrusage    kernel/sys.c
%define sys_sysinfo     99       ; sysinfo      kernel/sys.c
%define sys_times       100      ; times        kernel/sys.c
%define sys_ptrace      101      ; ptrace       kernel/ptrace.c
%define sys_getuid      102      ; getuid       kernel/sys.c
%define sys_syslog      103      ; syslog       kernel/printk/printk.c
%define sys_getgid      104      ; getgid       kernel/sys.c
%define sys_setuid      105      ; setuid       kernel/sys.c
%define sys_setgid      106      ; setgid       kernel/sys.c
%define sys_geteuid     107      ; geteuid      kernel/sys.c
%define sys_getegid     108      ; getegid      kernel/sys.c
%define sys_setpgid     109      ; setpgid      kernel/sys.c
%define sys_getppid     110      ; getppid      kernel/sys.c
%define sys_getpgrp     111      ; getpgrp      kernel/sys.c
%define sys_setsid      112      ; setsid       kernel/sys.c
%define sys_setreuid    113      ; setreuid     kernel/sys.c
%define sys_setregid    114      ; setregid     kernel/sys.c
%define sys_getgroups   115      ; getgroups    kernel/groups.c
%define sys_setgroups   116      ; setgroups    kernel/groups.c
%define sys_setresuid   117      ; setresuid    kernel/sys.c
%define sys_getresuid   118      ; getresuid    kernel/sys.c
%define sys_setresgid   119      ; setresgid    kernel/sys.c
%define sys_getresgid   120      ; getresgid    kernel/sys.c
%define sys_getpgid     121      ; getpgid      kernel/sys.c
%define sys_setfsuid    122      ; setfsuid     kernel/sys.c
%define sys_setfsgid    123      ; setfsgid     kernel/sys.c
%define sys_getsid      124      ; getsid       kernel/sys.c
%define sys_capget      125      ; capget       kernel/capability.c
%define sys_capset      126      ; capset       kernel/capability.c
%define sys_rt_sigpending       127      ; rt_sigpending        kernel/signal.c
%define sys_rt_sigtimedwait     128      ; rt_sigtimedwait      kernel/signal.c
%define sys_rt_sigqueueinfo     129      ; rt_sigqueueinfo      kernel/signal.c
%define sys_rt_sigsuspend       130      ; rt_sigsuspend        kernel/signal.c
%define sys_sigaltstack 131      ; sigaltstack  kernel/signal.c
%define sys_utime       132      ; utime        fs/utimes.c
%define sys_mknod       133      ; mknod        fs/namei.c
%define	uselib          134      ; uselib       fs/exec.c
%define sys_personality 135      ; personality  kernel/exec_domain.c
%define sys_ustat       136      ; ustat        fs/statfs.c
%define sys_statfs      137      ; statfs       fs/statfs.c
%define sys_fstatfs     138      ; fstatfs      fs/statfs.c
%define sys_sysfs       139      ; sysfs        fs/filesystems.c
%define sys_getpriority 140      ; getpriority  kernel/sys.c
%define sys_setpriority 141      ; setpriority  kernel/sys.c
%define sys_sched_setparam      142      ; sched_setparam       kernel/sched/core.c
%define sys_sched_getparam      143      ; sched_getparam       kernel/sched/core.c
%define sys_sched_setscheduler  144      ; sched_setscheduler   kernel/sched/core.c
%define sys_sched_getscheduler  145      ; sched_getscheduler   kernel/sched/core.c
%define sys_sched_get_priority_max      146      ; sched_get_priority_max       kernel/sched/core.c
%define sys_sched_get_priority_min      147      ; sched_get_priority_min       kernel/sched/core.c
%define sys_sched_rr_get_interval       148      ; sched_rr_get_interval        kernel/sched/core.c
%define sys_mlock       149      ; mlock        mm/mlock.c
%define sys_munlock     150      ; munlock      mm/mlock.c
%define sys_mlockall    151      ; mlockall     mm/mlock.c
%define sys_munlockall  152      ; munlockall   mm/mlock.c
%define sys_vhangup     153      ; vhangup      fs/open.c
%define sys_modify_ldt  154      ; modify_ldt   arch/x86/um/ldt.c
%define sys_pivot_root  155      ; pivot_root   fs/namespace.c
%define sys_sysctl      156      ; _sysctl      kernel/sysctl_binary.c
%define sys_prctl       157      ; prctl        kernel/sys.c
%define sys_arch_prctl  158      ; arch_prctl   arch/x86/um/syscalls_64.c
%define sys_adjtimex    159      ; adjtimex     kernel/time.c
%define sys_setrlimit   160      ; setrlimit    kernel/sys.c
%define sys_chroot      161      ; chroot       fs/open.c
%define sys_sync        162      ; sync fs/sync.c
%define sys_acct        163      ; acct kernel/acct.c
%define sys_settimeofday        164      ; settimeofday kernel/time.c
%define sys_mount       165      ; mount        fs/namespace.c
%define sys_umount      166      ; umount2      fs/namespace.c
%define sys_swapon      167      ; swapon       mm/swapfile.c
%define sys_swapoff     168      ; swapoff      mm/swapfile.c
%define sys_reboot      169      ; reboot       kernel/reboot.c
%define sys_sethostname 170      ; sethostname  kernel/sys.c
%define sys_setdomainname       171      ; setdomainname        kernel/sys.c
%define stub_iopl       172      ; iopl arch/x86/kernel/ioport.c
%define sys_ioperm      173      ; ioperm       arch/x86/kernel/ioport.c
%define create_module   174      ; create_module        NOT IMPLEMENTED
%define sys_init_module 175      ; init_module  kernel/module.c
%define sys_delete_module  176      ; delete_module        kernel/module.c
%define get_kernel_syms    177      ; get_kernel_syms      NOT IMPLEMENTED
%define query_module       178      ; query_module NOT IMPLEMENTED
%define sys_quotactl    179      ; quotactl     fs/quota/quota.c
%define nfsservctl      180      ; nfsservctl   NOT IMPLEMENTED
%define getpmsg         181      ; getpmsg      NOT IMPLEMENTED
%define putpmsg         182      ; putpmsg      NOT IMPLEMENTED
%define afs_syscall     183      ; afs_syscall  NOT IMPLEMENTED
%define tuxcall         184      ; tuxcall      NOT IMPLEMENTED
%define security        185      ; security     NOT IMPLEMENTED
%define sys_gettid      186      ; gettid       kernel/sys.c
%define sys_readahead   187      ; readahead    mm/readahead.c
%define sys_setxattr    188      ; setxattr     fs/xattr.c
%define sys_lsetxattr   189      ; lsetxattr    fs/xattr.c
%define sys_fsetxattr   190      ; fsetxattr    fs/xattr.c
%define sys_getxattr    191      ; getxattr     fs/xattr.c
%define sys_lgetxattr   192      ; lgetxattr    fs/xattr.c
%define sys_fgetxattr   193      ; fgetxattr    fs/xattr.c
%define sys_listxattr   194      ; listxattr    fs/xattr.c
%define sys_llistxattr  195      ; llistxattr   fs/xattr.c
%define sys_flistxattr  196      ; flistxattr   fs/xattr.c
%define sys_removexattr 197      ; removexattr  fs/xattr.c
%define sys_lremovexattr        198      ; lremovexattr fs/xattr.c
%define sys_fremovexattr        199      ; fremovexattr fs/xattr.c
%define sys_tkill               200      ; tkill        kernel/signal.c
%define sys_time                201      ; time kernel/time.c
%define sys_futex               202      ; futex        kernel/futex.c
%define sys_sched_setaffinity   203      ; sched_setaffinity    kernel/sched/core.c
%define sys_sched_getaffinity   204      ; sched_getaffinity    kernel/sched/core.c
%define set_thread_area         205      ; set_thread_area      arch/x86/kernel/tls.c
%define sys_io_setup            206      ; io_setup     fs/aio.c
%define sys_io_destroy          207      ; io_destroy   fs/aio.c
%define sys_io_getevents        208      ; io_getevents fs/aio.c
%define sys_io_submit           209      ; io_submit    fs/aio.c
%define sys_io_cancel           210      ; io_cancel    fs/aio.c
%define get_thread_area         211      ; get_thread_area      arch/x86/kernel/tls.c
%define sys_lookup_dcookie      212      ; lookup_dcookie       fs/dcookies.c
%define sys_epoll_create        213      ; epoll_create fs/eventpoll.c
%define epoll_ctl_old           214      ; epoll_ctl_old        NOT IMPLEMENTED
%define epoll_wait_old          215      ; epoll_wait_old       NOT IMPLEMENTED
%define sys_remap_file_pages    216      ; remap_file_pages     mm/fremap.c
%define sys_getdents64          217      ; getdents64   fs/readdir.c
%define sys_set_tid_address     218      ; set_tid_address      kernel/fork.c
%define sys_restart_syscall     219      ; restart_syscall      kernel/signal.c
%define sys_semtimedop          220      ; semtimedop   ipc/sem.c
%define sys_fadvise64           221      ; fadvise64    mm/fadvise.c
%define sys_timer_create        222      ; timer_create kernel/posix-timers.c
%define sys_timer_settime       223      ; timer_settime        kernel/posix-timers.c
%define sys_timer_gettime       224      ; timer_gettime        kernel/posix-timers.c
%define sys_timer_getoverrun    225      ; timer_getoverrun     kernel/posix-timers.c
%define sys_timer_delete        226      ; timer_delete kernel/posix-timers.c
%define sys_clock_settime       227      ; clock_settime        kernel/posix-timers.c
%define sys_clock_gettime       228      ; clock_gettime        kernel/posix-timers.c
%define sys_clock_getres        229      ; clock_getres kernel/posix-timers.c
%define sys_clock_nanosleep     230      ; clock_nanosleep      kernel/posix-timers.c
%define sys_exit_group  231      ; exit_group   kernel/exit.c
%define sys_epoll_wait  232      ; epoll_wait   fs/eventpoll.c
%define sys_epoll_ctl   233      ; epoll_ctl    fs/eventpoll.c
%define sys_tgkill      234      ; tgkill       kernel/signal.c
%define sys_utimes      235      ; utimes       fs/utimes.c
%define vserver         236      ; vserver      NOT IMPLEMENTED
%define sys_mbind       237      ; mbind        mm/mempolicy.c
%define sys_set_mempolicy       238      ; set_mempolicy        mm/mempolicy.c
%define sys_get_mempolicy       239      ; get_mempolicy        mm/mempolicy.c
%define sys_mq_open             240      ; mq_open      ipc/mqueue.c
%define sys_mq_unlink           241      ; mq_unlink    ipc/mqueue.c
%define sys_mq_timedsend        242      ; mq_timedsend ipc/mqueue.c
%define sys_mq_timedreceive     243      ; mq_timedreceive      ipc/mqueue.c
%define sys_mq_notify           244      ; mq_notify    ipc/mqueue.c
%define sys_mq_getsetattr       245      ; mq_getsetattr        ipc/mqueue.c
%define sys_kexec_load          246      ; kexec_load   kernel/kexec.c
%define sys_waitid              247      ; waitid       kernel/exit.c
%define sys_add_key             248      ; add_key      security/keys/keyctl.c
%define sys_request_key         249      ; request_key  security/keys/keyctl.c
%define sys_keyctl              250      ; keyctl       security/keys/keyctl.c
%define sys_ioprio_set          251      ; ioprio_set   fs/ioprio.c
%define sys_ioprio_get          252      ; ioprio_get   fs/ioprio.c
%define sys_inotify_init        253      ; inotify_init fs/notify/inotify/inotify_user.c
%define sys_inotify_add_watch   254      ; inotify_add_watch    fs/notify/inotify/inotify_user.c
%define sys_inotify_rm_watch    255      ; inotify_rm_watch     fs/notify/inotify/inotify_user.c
%define sys_migrate_pages       256      ; migrate_pages        mm/mempolicy.c
%define sys_openat              257      ; openat       fs/open.c
%define sys_mkdirat             258      ; mkdirat      fs/namei.c
%define sys_mknodat             259      ; mknodat      fs/namei.c
%define sys_fchownat            260      ; fchownat     fs/open.c
%define sys_futimesat           261      ; futimesat    fs/utimes.c
%define sys_newfstatat          262      ; newfstatat   fs/stat.c
%define sys_unlinkat            263      ; unlinkat     fs/namei.c
%define sys_renameat            264      ; renameat     fs/namei.c
%define sys_linkat              265      ; linkat       fs/namei.c
%define sys_symlinkat           266      ; symlinkat    fs/namei.c
%define sys_readlinkat          267      ; readlinkat   fs/stat.c
%define sys_fchmodat            268      ; fchmodat     fs/open.c
%define sys_faccessat           269      ; faccessat    fs/open.c
%define sys_pselect6            270      ; pselect6     fs/select.c
%define sys_ppoll               271      ; ppoll        fs/select.c
%define sys_unshare             272      ; unshare      kernel/fork.c
%define sys_set_robust_list     273      ; set_robust_list      kernel/futex.c
%define sys_get_robust_list     274      ; get_robust_list      kernel/futex.c
%define sys_splice              275      ; splice       fs/splice.c
%define sys_tee                 276      ; tee  fs/splice.c
%define sys_sync_file_range     277      ; sync_file_range      fs/sync.c
%define sys_vmsplice            278      ; vmsplice     fs/splice.c
%define sys_move_pages          279      ; move_pages   mm/migrate.c
%define sys_utimensat           280      ; utimensat    fs/utimes.c
%define sys_epoll_pwait         281      ; epoll_pwait  fs/eventpoll.c
%define sys_signalfd            282      ; signalfd     fs/signalfd.c
%define sys_timerfd_create      283      ; timerfd_create       fs/timerfd.c
%define sys_eventfd             284      ; eventfd      fs/eventfd.c
%define sys_fallocate           285      ; fallocate    fs/open.c
%define sys_timerfd_settime     286      ; timerfd_settime      fs/timerfd.c
%define sys_timerfd_gettime     287      ; timerfd_gettime      fs/timerfd.c
%define sys_accept4             288      ; accept4      net/socket.c
%define sys_signalfd4           289      ; signalfd4    fs/signalfd.c
%define sys_eventfd2            290      ; eventfd2     fs/eventfd.c
%define sys_epoll_create1       291      ; epoll_create1        fs/eventpoll.c
%define sys_dup3                292      ; dup3 fs/file.c
%define sys_pipe2               293      ; pipe2        fs/pipe.c
%define sys_inotify_init1       294      ; inotify_init1        fs/notify/inotify/inotify_user.c
%define sys_preadv              295      ; preadv       fs/read_write.c
%define sys_pwritev             296      ; pwritev      fs/read_write.c
%define sys_rt_tgsigqueueinfo   297      ; rt_tgsigqueueinfo    kernel/signal.c
%define sys_perf_event_open     298      ; perf_event_open      kernel/events/core.c
%define sys_recvmmsg            299      ; recvmmsg     net/socket.c
%define sys_fanotify_init       300      ; fanotify_init        fs/notify/fanotify/fanotify_user.c
%define sys_fanotify_mark       301      ; fanotify_mark        fs/notify/fanotify/fanotify_user.c
%define sys_prlimit64           302      ; prlimit64    kernel/sys.c
%define sys_name_to_handle_at   303      ; name_to_handle_at    fs/fhandle.c
%define sys_open_by_handle_at   304      ; open_by_handle_at    fs/fhandle.c
%define sys_clock_adjtime       305      ; clock_adjtime        kernel/posix-timers.c
%define sys_syncfs              306      ; syncfs       fs/sync.c
%define sys_sendmmsg            307      ; sendmmsg     net/socket.c
%define sys_setns               308      ; setns        kernel/nsproxy.c
%define sys_getcpu              309      ; getcpu       kernel/sys.c
%define sys_process_vm_readv    310      ; process_vm_readv     mm/process_vm_access.c
%define sys_process_vm_writev   311      ; process_vm_writev    mm/process_vm_access.c
%define sys_kcmp                312      ; kcmp kernel/kcmp.c
%define sys_finit_module        313      ; finit_module kernel/module.c