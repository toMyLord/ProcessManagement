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


#ifndef __FIND_WAY__
#define __FIND_WAY__

#include "procnode.h"
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

/* 
 * 同过pid查找迭代器，用于find_if函数
 */
class findByPid{
private:
    int pid;

public:
    findByPid(char * pid);
    bool operator()(vector<proc_node>::value_type &value);
};


#endif