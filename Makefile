
BINDIR	 = bin/
OBJDIR	 = obj/
BIN      = W3DUnit

SRCS     = application.cpp context.cpp contextstrings.cpp defaultparams.cpp enumstrings.cpp exception.cpp implementation_checks_basic.cpp implementation_checks_v3_primitives.cpp implementation_checks_v4_vertex.cpp implementation_checks_v4_primitives.cpp implementation_checks_v4_points.cpp implementation_checks_v4_lines.cpp implementation_checks_v4_tris.cpp logger.cpp main.cpp test.cpp texture.cpp timer.cpp vertex.cpp

CXXFLAGS = -O3 -Wall -W -Wno-unused-parameter -fomit-frame-pointer -D__USE_BASETYPE__
LDFLAGS  =
OBJS     = $(foreach SRC, $(SRCS), $(OBJDIR)$(SRC:.cpp=.o))

$(BIN): $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) ${LDFLAGS} $(OBJS) -o $(BINDIR)$(BIN)

$(OBJDIR)%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	$(RM) $(TARGET) $(OBJDIR)*.o

