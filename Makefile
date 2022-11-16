SHELL = /bin/bash
CXX = g++ -std=c++17
#CXX = clang++ -std=c++17
CXXFLAGS = -Wall -pedantic -Wextra -Werror -g -O0 -I. -I$(HEADDIR)
LDFLAGS =

HEADDIR = include
SRCDIR = src
OBJDIR = obj
BINDIR = bin

TARGET = $(BINDIR)/clamshell
HEADS = $(wildcard $(HEADDIR)/*.h $(HEADDIR)/*.hpp)
SRCS = $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/*.cc)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(TARGET): $(OBJS) | $(BINDIR)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: $(BINDIR) $(OBJDIR) clean memtest echo run

run: $(TARGET)
	@./$(TARGET)

$(BINDIR) $(OBJDIR):
	@mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)

memtest: $(TARGET)
	valgrind --tool=memcheck -s --leak-check=full --show-leak-kinds=all $(TARGET)

echo:
	@echo $(foreach var, $(.VARIABLES), $(info $(var) = $($(var)))) # | grep "... ="

