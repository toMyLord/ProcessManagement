#include "procinfo.h"

CProcInfo::CProcInfo()
{
    this->proc_number = 0;
    this->processor_number = searchProcessor();
    if(!searchProc())
    {
        printf("[fail]:search proc fail!\n");
    }
    if(!searchSys())
    {
        printf("[fail]:search sys fail!\n");
    }
}


bool CProcInfo::isNumber(char * file_name)
{
    int lenth = strlen(file_name);

    for(int i = 0; i < lenth; i++)
        if(!(file_name[i] <= '9' && file_name[i] >= '0'))
            return false;

    return true;
}


int CProcInfo::searchProcessor()
{
    int processor = 0;
    char pro[] = "processor";
    char path[] = "/proc/cpuinfo";
    char line[1000];
    FILE * fd = fopen(path, "r");

    while(!feof(fd))  
    {  
        fgets(line,1000,fd);  
        if(strstr(line,pro) != NULL)
            processor++ ;
    }
    
    fclose(fd);

    return processor;
}


void CProcInfo::getCurProcNode(char * pid_path, proc_node * temp)
{
    int uid;
    char path[256];
    FILE * fd;

    strcpy(path, "/proc/");
    strcat(path, pid_path);
    strcat(path, "/stat");
    fd = fopen(path, "r");
    fscanf(fd, "%d", &temp->pid);    //获取进程的pid
            
    fseek(fd, 2, SEEK_CUR);
    fscanf(fd,"%s", temp->cmd);
    temp->cmd[strlen(temp->cmd) - 1] = '\0';  //获取进程的cmd

    char stat[4];
    long long  trash,cpu_time = 0;
    fscanf(fd,"%s ",stat);
    for(int i = 0; i < 10; i++)
    {
        fscanf(fd,"%d ", &trash);
    }
    for(int i = 0; i < 4; i++)
    {
        fscanf(fd,"%ld ", &trash);
        cpu_time += trash;
    }
    temp->cpu_time = cpu_time;      //获取进程的cputime

    fclose(fd);

    strcpy(path, "/proc/");
    strcat(path, pid_path);
    strcat(path, "/cmdline");
    fd = fopen(path,"r");
    fgets(temp->cmdline, 256, fd); //获取进程的cmdline
    temp->cmdline[255] = '\0';

    fclose(fd);

    char line[1000];
    struct passwd * pw;
    strcpy(path, "/proc/");
    strcat(path, pid_path);
    strcat(path, "/status");
    fd = fopen(path, "r");
    while(!feof(fd))  
    {  
        fgets(line,1000,fd);  
        if(strstr(line,"Uid") != NULL)
        {
            sscanf(line, "%s%d", path, &temp->uid);
            pw = getpwuid(temp->uid);
            strcpy(temp->username, pw->pw_name);
        }
    }
    
    fclose(fd);

    strcpy(path, "/proc/");
    strcat(path, pid_path);
    strcat(path, "/statm");
    fd = fopen(path,"r");
    fscanf(fd, "%d%d", &temp->vsz, &temp->rss);
    temp->vsz *= 4;             //获取进程的vsz
    temp->rss *= 4;             //获取进程的rss

    temp->proc_mem_rate = (temp->rss * 1.0) / this->total_mem * 100.0;  //获取进程的内存使用率

    fclose(fd);



}


void CProcInfo::getCurCpuTime(unsigned long long * cpu_time, unsigned long long * idle)
{
    unsigned long long temp;
    char buf[1000];

    *cpu_time = 0;

    FILE * fd = fopen("/proc/stat","r");

    fscanf(fd,"%s  ",buf);
    for(int i = 0; i < 9; i++)
    {
        fscanf(fd, "%llu ", &temp);
        *cpu_time += temp;
        if(i == 3)
        {
            *idle = temp;
        }

    }
    fclose(fd);
}


double CProcInfo::getCurMemSize(unsigned long long * total_mem, unsigned long long * free_mem)
{
    char dirty[10];
    double mem_rate;
    FILE * fd = fopen("/proc/meminfo","r");
    
    fscanf(fd,"%s%llu%s%s%llu",dirty,total_mem,dirty,dirty,free_mem);

    return (100.0 - (*free_mem) * 1.0 / (*total_mem) *100.0) * 0.589;

}


void CProcInfo::getCurInterBytes(unsigned long long * receive_bytes,unsigned long long * transmit_bytes)
{
    FILE * fd;
    char line[1000], dirty[16];
    int line_num = 0, trash;
    unsigned long long rec_temp = 0, tra_temp = 0;
    
    *receive_bytes = 0;
    *transmit_bytes = 0;

    fd = fopen("/proc/net/dev", "r");
    while(!feof(fd))  
    {  
        line_num++;
        fgets(line,1000,fd);  
        
        if(line_num >= 3)
        {
            sscanf(line,"%s%llu%d%d%d%d%d%d%d%llu",dirty, &rec_temp, &trash, &trash,
             &trash, &trash, &trash, &trash, &trash, &tra_temp);
            
            *receive_bytes += rec_temp;
            *transmit_bytes += tra_temp;
        }
    }
    
    fclose(fd);
}


bool CProcInfo::searchProc()
{
    unsigned long long temp;
    unsigned long long cpu_time, old_cpu_time, idle, old_idle;
    unsigned long long rec_kb, old_rec_kb, tra_kb, old_tra_kb;

    struct dirent *  dir_info;
    DIR * dir;
    dir = opendir("/proc");

    this->sys_mem_rate = getCurMemSize(&this->total_mem, &this->free_mem);

    getCurCpuTime(&old_cpu_time, &old_idle);

    if(dir == NULL)
    {
        printf("[fail]:cann't open /proc !\n");
        return false;
    }
    while((dir_info = readdir(dir)) != NULL)
    {
        //省略目录下的 . 和 .. 
        if(strcmp(dir_info->d_name, ".") == 0 ||
           strcmp(dir_info->d_name, "..") == 0)
           continue;
        else if(!isNumber(dir_info->d_name))
        {
            //非进程文件 
            continue;
        }
        else
        {
            proc_node temp;
            
            getCurProcNode(dir_info->d_name, &temp);

            this->proc_info.push_back(temp);
            this->proc_number++;
        }
    }
    closedir(dir);

    getCurInterBytes(&old_rec_kb, &old_tra_kb);

    usleep(100000); //等待足够短的时间

    getCurInterBytes(&rec_kb, &tra_kb);

    this->sys_down_speed = (rec_kb - old_rec_kb) / 102.4;
    this->sys_up_speed = (tra_kb - old_tra_kb) / 102.4;

    dir = opendir("/proc");
    if(dir == NULL)
    {
        printf("[fail]:cann't open /proc !\n");
        return false;
    }
    while((dir_info = readdir(dir)) != NULL)
    {
        //省略目录下的 . 和 .. 
        if(strcmp(dir_info->d_name, ".") == 0 ||
           strcmp(dir_info->d_name, "..") == 0)
           continue;
        else if(!isNumber(dir_info->d_name))
        {
            //非进程文件 
            continue;
        }
        else
        {
            vector<proc_node>::iterator it;
            it = find_if(this->proc_info.begin(), this->proc_info.end(), findByPid(dir_info->d_name));
            if(it != this->proc_info.end())
            {
                char path[256],tra[20];
                long long trash,cpu_tm = 0;

                strcpy(path,"/proc/");
                strcat(path,dir_info->d_name);
                strcat(path,"/stat");
                FILE * fd = fopen(path,"r");

                fscanf(fd,"%d %s %s ",&trash,tra,tra);
                for(int i = 0; i < 10; i++)
                {
                    fscanf(fd,"%d ", &trash);
                }
                for(int i = 0; i < 4; i++)
                {
                    fscanf(fd,"%ld ", &trash);
                    cpu_tm += trash;
                }

                getCurCpuTime(&cpu_time, &idle);

                (*it).proc_cpu_rate = (cpu_tm - (*it).cpu_time)/((cpu_time - old_cpu_time) 
                                      * 1.0) * 100.0 / this->processor_number;
                
                // printf("%s \t %ld \t % ld \t %ld \t %d \t %.2lf\%\n", dir_info->d_name, old_cpu_time,
                //                  cpu_time, (*it).cpu_time, cpu_tm, (*it).proc_cpu_rate
                //                 );
            }
            else 
                continue;
        }
    }
    closedir(dir);
    
    getCurCpuTime(&cpu_time, &idle);

    this->sys_cpu_rate = ((cpu_time - old_cpu_time) - (idle - old_idle))
                           / ((cpu_time - old_cpu_time)*1.0) * 100;     //获取cpu占用率



    return true;
}


bool CProcInfo::searchSys()
{
    // unsigned long long temp,cpu_time,old_cpu_time,idle,old_idle;
    
    // getCurCpuTime(&old_cpu_time, &old_idle);

    // usleep(100000); //等待足够短的时间

    // getCurCpuTime(&cpu_time, &idle);

    // this->sys_cpu_rate = ((cpu_time - old_cpu_time) - (idle - old_idle))
    //                      / ((cpu_time - old_cpu_time)*1.0) * 100;

    return true;
}


bool CProcInfo::flash()
{

    return true;
}


void CProcInfo::show()
{
    for(int i = 0; i < this->proc_number; i++)
    {
        printf("%d\t%s\t%.2lf\%\t%.2f\%\t%d\t%d\t%s\t%s\n",
              this->proc_info[i].pid, this->proc_info[i].username,
              this->proc_info[i].proc_cpu_rate, this->proc_info[i].proc_mem_rate,
              this->proc_info[i].vsz, this->proc_info[i].rss, 
              this->proc_info[i].cmd, this->proc_info[i].cmdline
              );
    }
    printf("CPU_RATE = %.2lf\%\nPRO_NUM = %d\nMEM_RATE = %.2lf\%\nUPLOAD = %.2lfKB/s\nDOWNLOAD = %.2lfKB/s\n",
          this->sys_cpu_rate, this->processor_number, this->sys_mem_rate, 
          this->sys_up_speed, this->sys_down_speed
          );
}


