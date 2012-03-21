   
MAKE_MODEL=make_model
LOAD_MODEL=load_model

LUA_BASE=/project/projectdirs/snfactry/rthomas/local/$(NERSC_HOST)
LUA_INCLUDE=-I$(LUA_BASE)/include
LUA_LDFLAGS=-L$(LUA_BASE)/lib
LUA_LIBS=-llua

CXX=CC -O3
CXXFLAGS=$(LUA_INCLUDE)
LDFLAGS=$(LUA_LDFLAGS)
CXXLIBS=$(LUA_LIBS)

OBJ=Node.o Index.o Zone.o

all: $(MAKE_MODEL) $(LOAD_MODEL)

$(MAKE_MODEL) : $(OBJ) $(MAKE_MODEL).o
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(MAKE_MODEL).o $(CXXLIBS)

$(LOAD_MODEL) : $(OBJ) $(LOAD_MODEL).o
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LOAD_MODEL).o $(CXXLIBS)

.cc.o :
	$(CXX) $(CXXFLAGS) -c -o $@ $< 

clean :
	rm -rf *.o

realclean : clean
	rm -rf $(MAKE_MODEL) $(MAKE_MODEL).dSYM $(LOAD_MODEL) $(LOAD_MODEL).dSYM core
