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
 * 参考网站：https://github.com/toMyLord
 * Copyright(C) toMyLord 2017-12-12
 */


#ifndef __PROC_NODE__
#define __PROC_NODE__

//保存单个进程的详细信息
typedef struct proc_node{
    int pid;                    //进程号pid
    char cmd[16];               //进程命令
    char cmdline[256];          //进程详细命令，包含运行命令的参数等
    unsigned long long cpu_time;//此进程运行的总cpu时间，单看次参数无意义
    int uid;                    //进程所属用户的uid
    char username[64];          //进程所属用户的用户名
    int vsz;                    //虚拟消耗内存（KB）
    int rss;                    //实际使用物理内存（KB）
    char user[256];             //进程所属用户的用户名
    double proc_cpu_rate;        //CPU使用率
    double proc_mem_rate;        //内存使用率
}proc_node; 


#endif