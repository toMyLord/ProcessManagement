# 基于 __Linux__ 的 __进程快照__ 
### 使用 ___C++___ 实现系统中全部进程的快照。
## 支持的 __快照__ 功能
- 进程号
- 进程所属用户的用户名
- 进程的CPU使用率
- 进程的内存使用率
- 进程的VSZ
- 进程的RSS
- 进程名
- 执行进程的完整命令（cmdline）
- 整个系统的CPU、内存使用率
- 整个系统的上传、下载速度（KB/s)
## 限制
- cpu使用率在0.1秒的时间内采集，导致cpu的使用率波动较大。
- 进程的内存使用率通过 ___RSS/total_mem___ 进行计算，会导致计算结果偏大。
- 上传、下载速度在0.1秒的时间内采集，导致波动较大。
## 支持的系统
- Linux distributions
## 安装方法
```
cd ~
git clone https://github.com/toMyLord/ProcessManagement.git
cd ProcessManagement
make
make clean
./ps
```

## ___CProcInfo___ 类
### 私有成员
- ```vector<proc_node> proc_info;    //所有进程的信息都存在vector容器proc_info中```

- ```int proc_number;                //系统中所有进程的数量```

- ```int processor_number;           //本机中cpu的核心数```

- ```double sys_cpu_rate;            //系统的CPU使用率```

- ```double sys_mem_rate;            //系统的内存使用率```

- ```unsigned long long total_mem;   //系统总共内存数量```

- ```unsigned long long free_mem;    //系统使用的内存数量```

- ```double sys_up_speed;            //系统上传网速(kb/s)```

- ```double sys_down_speed;          //系统下载网速(kb/s)```
### 公有成员
```
    CProcInfo();
    
    /*
     * 判断文件名是不是纯数字
     * @parameter:文件名
     * @return：是进程文件返回true，不是进程文件返回false
     */
    bool isNumber(char * file_name); 

    /*
     * 获取本系统中cpu的核心数
     * @return：核心数
     */
    int searchProcessor();

    /*
     * 获得当前的proc_node 并且通过temp返回
     * @parameter：用作返回值
     */
    void getCurProcNode(char * pid_path, proc_node * temp);

    /*
     * 获得当前的cpu总时间和idle，通过参数返回
     * @parameter：cpu总时间，idle时间
     */
    void getCurCpuTime(unsigned long long * cpu_time, unsigned long long * idle);

    /*
     * 获得系统的内存总量和当前使用量
     * @parameter：内存总量，当前空闲量，通过参数返回
     * @return：返回内存占用率
     */
    double getCurMemSize(unsigned long long * total_mem, unsigned long long * free_mem);

    /*
     * 获得当前收到的千字节和发送的字节
     * parameter：下载，上传
     */
    void getCurInterBytes(unsigned long long * receive_bytes,unsigned long long * transmit_bytes);

    /*
     * 搜寻dir_name目录下的所有进程，并将所有进程信息存在proc_number中
     * @return：搜寻成功返回ture，失败返回false
     */                
    bool searchProc();

    /*
     * 搜寻dir_name目录下的所有进程的占用信息
     * @return：搜寻成功返回ture，失败返回false
     */     
    bool searchSys();

    /*
     * 刷新所有进程的信息以及系统占用情况
     * @return：搜寻成功返回true，失败返回fase
     */
    bool flash();

    void show();
```
## ___proc_node___ 结构体
```
typedef struct proc_node{
    int pid;                    //进程号pid
    char cmd[16];               //进程命令
    char cmdline[256];          //进程详细命令，包含运行命令的参数等
    unsigned long long cpu_time;//此进程运行的总cpu时间，单看此参数无意义
    int uid;                    //进程所属用户的uid
    char username[64];          //进程所属用户的用户名
    int vsz;                    //虚拟消耗内存（KB）
    int rss;                    //实际使用物理内存（KB）
    char user[256];             //进程所属用户的用户名
    double proc_cpu_rate;        //CPU使用率
    double proc_mem_rate;        //内存使用率
}proc_node; 
```