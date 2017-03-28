# BEGIN CONFIG
TARGET=lib/libartemis.a

SRCDIR=src
OBJDIR=obj

# END CONFIG

CXXFLAGS:=-I./include

SOURCES=$(wildcard $(SRCDIR)/*.cpp)
HEADERS=$(wildcard include/*.h)
OBJS=$(subst $(SRCDIR),$(OBJDIR),$(subst .cpp,.o,$(SOURCES)))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJDIR) $(OBJS)
	ar rcs $(TARGET) $(OBJS)

$(OBJDIR):
	mkdir $(OBJDIR)

all: $(TARGET)

.PHONY: clean
clean:
	rm -r $(OBJDIR)
	rm $(TARGET)
