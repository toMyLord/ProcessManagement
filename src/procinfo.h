/*
 * 本程序供学习使用，未经作者许可，可以用于其它任何用途
 * 
 * 
 * 
$$ZZOO8DNMMMMMNNMMMNMMMMMMNMNDDD8ODDNNNDDDNNMNNND8DNNNMMNNNM
NDZ7$ZZZZOO8DDNNNNNNNNN8OZZZOOO8D888O8NNNNMNND88NMMNNNMMNNNM
MMMNNDO$$$ZZZOOOO888OZZZZ$ZOOOO8O$8DD88DDDD88NMMMMMNNNMMNNNM
NMMMMMMMNNNDD88OOOZ$DD8OO8OZ$ZOZZOOO88DDDODNMMMMNMMNNNMMNNNM
DOODNMMMMMMMMMMMNOO8DDDDNDOOZOO88O888D88DD$DNMMMNNNNNNMMNNNM
MMNND888DNMMMMNOZZ78OZOOO8O88O888D8DDDD8DO8OONMMNNNNNNMNNNNM
88DNMMMMNNNNDDZZ$ZOOZOZZZZOO8D888888D8O8D8D8OONNNNNNNNMMNNNM
DDDDDD8888888ZZZOOOOOZ$$$ZZO8O88OOZOO$ZOZO8O888MNNNNNNMNNNNM
DDDDDDDDDNMN8ZOO88$OZZZ??Z7I$$$ZOZ7IZ$?Z$I$OO8ONNNNNNNMNNNNM
DDDDDDDDDMND8Z8DDZ+II=?+=7+???+=I?==?=$IZ=+78ONDNNNNNNMNNNNM
DDDDDD88DMMD8O8D8I==~~~~~~~~=~~~~=:::~~~+:~=7D8DNNNNNNNNNNNM
DDD8DD88DMNDOO8DZ+~:::~:::::::::::::::::::::788NNNNNNNNMNNNM
DDD8D88DDNN8DD88Z+~~~:::,,:,,::::::::::::::~7O8NNNNNNNNMNNNM
DDD8888DNMNDNDDD?=~~:=+==~::::::,:::::::::::IO8NNNNNNNNNNNNM
DDDDDD8DNNNDNND$===+++?7$7Z?==~~~+IZ$$$I?::~~OODNNNNNNNMNNNM
DDDDDDDDNNN~=D8$=~?I7I+??+?7?+==+???+=====~~:8ODNNNNNNNMNNNN
DDDDDD8DNM$I??$$$D?+?$O88$7$8N8ONO$$77I+=ID=~Z?+NNNNNNNNNDNM
DDDDDDDDNN7+==$$7D+===~=+?7I7N8N7I$?8$?I7?7MZ=??DNNNNNNNNNNM
DDDDDDDDNNN==?$++?==~==+??+=$=:~D=?????+++=N+==?DNDDNNNNNNNN
DDDDDDDDNNN8~++=~~Z?:~~~~~=I+:,,+=====~~~~O~++=NNNNDNNNNNNNN
DDDDDDDDNNND+===~~~::::::~=~~:,,:~?$ZZ$$7=::+=7NNNDDNNNNNNNN
DDDDDDDDNNND8:~~==~~:::~+=~:~:,,::~?=~::::::+=NNNNDDNNNNNNNN
DDDDDDDDNNNDD++==++====+~=+==~~~~~~====~~~~~~NNNNNDDNNNNNNNN
DDDDDDDNNNNDNDD===++++=~~~~?I$7I?+==~==+=~=~$NNNNNNDNNNNNNNN
DDNDDDDNNNNDNDD+=====+?+=~~~~~===~=~==++==~~NNNNNNNDNNNNNNNN
DDDDNDDNNNNDNDD$?+=+==+INZZZZ$$$ZZZO$+====~7NNNNNNNDDNNNNNNN
DDDNDDDNNNNDNDDNI?+++==~=+?I?~~:=++=~======NNNNNNNNNNNNNNNNN
NNDDNDNNNNNDNDDD+II??+===+I?====+?=~==++++DNNNNNNDDDNNNNNNNN
DDNDDNNNNNNDNDD:+?7II?===~=+III?+=====++?NNNNNNNNNNDNNNNNNNN
DNNNDDNNNNNNND~.=+II7I?=~~~~~~~~~~~~=+?8NNNNNNNNNNDDNNNNDNNN
NNNDNNNNNNDDDD,.=+?II7II+==~~~==~~=+?+:DNNNNNNNNNNDDNNNNDNNN
NNNNNNNNNDND$:..~++??I7II7IIII??II7?+=,~NNNNNNNNNNNDNNNNDNNN
NNNNNNNNND$I,....~+++?II777777777I?+=~,:$NNNNNNNNNNDDNNNDDNN
NNNNNNO$7+++:......=++??III777I???+=~..:$INNNNNNNNNDDNNDDDNN
ND$7++++++??~.......,++?????????+++:...,777$NNNNNNDDDNND8DDD
++++?????+???.........:++??I??++=:.....:777777NNNDDDDDND88DD
++????????II+............++++=:,.......:$$77$777$8888DD888DD
++???????II+=...........,:::,,........,~$$7777777777ZZOO88OO
 *                  威哥保佑，玄学除bug
 * 
 * 
 * 
 * 参考网站：https://github.com/toMyLord/ProcessManagement
 * Copyright(C) toMyLord 2017-12-12
 */


#ifndef __PROC_INFO__
#define __PROC_INFO__

#include "findway.h"
#include "procnode.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <pwd.h>


using namespace std;


class CProcInfo{
private:
    vector<proc_node> proc_info;    //所有进程的信息都存在vector容器proc_info中
    int proc_number;                //系统中所有进程的数量
    int processor_number;           //本机中cpu的核心数
    double sys_cpu_rate;            //系统的CPU使用率
    double sys_mem_rate;            //系统的内存使用率
    unsigned long long total_mem;   //系统总共内存数量
    unsigned long long free_mem;    //系统使用的内存数量
    double sys_up_speed;            //系统上传网速(kb/s)
    double sys_down_speed;          //系统下载网速(kb/s)

public:
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
};


#endif