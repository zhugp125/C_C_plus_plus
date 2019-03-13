#
# string_reverse
#

PROGRAM = Stack
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

BULID_OUT_DIR = .

%.o: %.cpp
	$(CXX) -c $(INCLUDES) -o $@ $?

$(PROGRAM): $(OBJS)
	$(CXX) -o $(BULID_OUT_DIR)/$@ $^ $(LIBS)

clean:
	rm -f $(OBJS) $(BULID_OUT_DIR)/$(PROGRAM)
