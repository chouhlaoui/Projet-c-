CXX = g++
CXXFLAGS = -I include -Wall
LDFLAGS = -lopengl32 -lfreeglut -lglew32 -lglu32

SRCDIR = src
OBJDIR = obj
INCDIR = include

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

main: main.o $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/*.h | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cpp $(INCDIR)/*.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)/*.o main.o main
