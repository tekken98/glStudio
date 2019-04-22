INCLUDE=-I/usr/include -I/usr/local/include/ -I/usr/local/include/freetype2/ -I/opt/libjpeg-turbo/include/
LIB=-L/usr/local/lib/ -L/opt/libjpeg-turbo/lib64/
LIBGLUT=-lglut -lGL -lGLU -lfreetype -lturbojpeg -l3ds 
objs=a.o button.o font.o object.o common.o loadfile.o GLProgram.o GLModel.o GLTexture.o
CFLAGS=-Wall 
OPTS= -lm -lstdc++ -fpch-preprocess
a:$(objs) 
	cc $(objs) -o a  $(CFLAGS) $(INCLUDE) $(LIB) $(LIBGLUT)   $(OPTS)
	./a
a.o:a.cpp 
	clear
	gcc -c a.cpp $(CFLAGS)  $(INCLUDE) $(OPTS)
button.o:button.cpp button.h
	gcc -c button.cpp  $(CFLAGS) $(INCLUDE) $(OPTS)
font.o:font.cpp font.h
	gcc -c font.cpp  $(CFLAGS) $(INCLUDE) $(OPTS)
object.o:object.cpp object.h
	gcc -c object.cpp  $(CFLAGS) $(INCLUDE) $(OPTS)
common.o:common.h common.cpp
	gcc -c common.cpp $(CFLAGS)  $(INCLUDE)  $(OPTS)
loadfile.o:loadfile.cpp  loadfile.h
	gcc -c loadfile.cpp  $(CFLAGS)  $(INCLUDE)  $(OPTS)
GLProgram.o:GLProgram.cpp GLProgram.h
	g++ -c GLProgram.cpp $(CFLAGS)  $(INCLUDE)  $(OPTS)
GLModel.o:GLModel.cpp GLModel.h
	gcc -c GLModel.cpp  $(CFLAGS)  $(INCLUDE)  $(OPTS)
GLTexture.o:GLTexture.cpp GLTexture.h
	gcc -c $<  $(CFLAGS)  $(INCLUDE)  $(OPTS)
tags:
	cpp $(INCLUDE) a.cpp >.my.cpp
	#ctags -R --extra=q --fields=+aiS --c++-kinds=cfp --language-force=c++ -h "..h" /usr/include/c++/7/* 
	ctags --extra=+q --fields=+aiS --c++-kinds=cfp .my.cpp
	ctags --extra=+q --fields=+aiS --c++-kinds=cfp -a *.cpp *.h
clean:
	rm *.o
