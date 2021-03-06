CC = c++
FLAGS = -Wall

#-----------------------------------------
#Optimization ----------------------------
OPT = -O2 -g

#-----------------------------------------
#-----------------------------------------

TARGETS = meshfair
OBJECTS = meshfair.o 

#-----------------------------------------
# 
INCS = -I/usr/include/eigen3 -I/usr/local/include/eigen-3.3.8/ 
LIBS =

CCOPTS = $(OPT) $(FLAGS) $(INCS)  
LDOPTS = $(OPT) $(LIBS)

#-----------------------------------------
#-----------------------------------------

default: $(TARGETS) 

clean:
	/bin/rm -fv *.o $(TARGETS) 

#-----------------------------------------
#-----------------------------------------

hide: $(OBJECTS)
	$(CC) $(LDOPTS) -o hide $(OBJECTS)


#-----------------------------------------

.cpp.o:
	$(CC) $(CCOPTS) -c $< -o $@

#-----------------------------------------
#-----------------------------------------
