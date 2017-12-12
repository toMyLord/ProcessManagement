#
#	完成编译过程，生成的中间文件可以用make clean清除
#		最终生成目标可执行文件ps
#


objects		:= ./src/findway.o ./src/procinfo.o main.o

ps : $(objects) 
	g++	-o ps $(objects)

./src/findway.o : ./src/procnode.h
./src/procinfo.o : ./src/findway.h ./src/procnode.h
main.o : ./src/procnode.h

.PHONY : clean
clean :
	-rm $(objects)