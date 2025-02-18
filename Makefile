# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Werror -pedantic -std=c++2a -I./deps/include -O3
LDFLAGS := -L./deps/lib/linux -lraylib -limgui -lGL -lpthread -ldl

# Directories
SRCDIR := ./src
BUILDDIR := ./build/linux
OBJDIR := $(BUILDDIR)/obj
TARGET := $(BUILDDIR)/gefest

# Source files and object files
SRCFILES := $(wildcard $(SRCDIR)/*.cpp)
OBJFILES := $(SRCFILES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJFILES)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Build object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create build directories if they don't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up build files
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
