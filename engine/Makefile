#### PROJECT SETTINGS ####
# The name of the executable to be created
BIN_NAME := engine
# Compiler used
CXX ?= g++
# Source paths
SRC_PATH = src
GENERIC_SRC_PATH = ../src
# Space-separated pkg-config libraries used by this project
LIBS = -lIL -ltinyxml2 -lm -lGL -lGLEW -lGLU -lglut
# General compiler flags
COMPILE_FLAGS = -std=c++11 -Wall -Wextra
# Additional release-specific flags
RCOMPILE_FLAGS = -D NDEBUG -O3
# Additional debug-specific flags
DCOMPILE_FLAGS = -D DEBUG -g
#### END PROJECT SETTINGS ####

# Function used to check variables. Use on the command line: make print-VARNAME
print-%: ; @echo $*=$($*)

# Verbose option, to output compile and link commands
export V := false
export CMD_PREFIX := @
ifeq ($(V),true)
	CMD_PREFIX :=
endif

# Combine compiler and linker flags
release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS) $(RCOMPILE_FLAGS)
debug: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS) $(DCOMPILE_FLAGS)

# Build and output paths
release: export BUILD_PATH := build/release/obj
release: export BIN_PATH := build/release
debug: export BUILD_PATH := build/debug/obj
debug: export BIN_PATH := build/debug

SOURCES := $(wildcard $(SRC_PATH)/*.cpp)
GENERIC_SOURCES := $(wildcard $(GENERIC_SRC_PATH)/*.cpp)

# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:$(SRC_PATH)/%.cpp=$(BUILD_PATH)/%.o)
OBJECTS += $(GENERIC_SOURCES:$(GENERIC_SRC_PATH)/%.cpp=$(BUILD_PATH)/%.o)

TIME_FILE = $(dir $@).$(notdir $@)_time
START_TIME = date '+%s' > $(TIME_FILE)
END_TIME = read st < $(TIME_FILE) ; \
	$(RM) $(TIME_FILE) ; \
	st=$$((`date '+%s'` - $$st - 86400)) ; \
	echo `date -u -d @$$st '+%H:%M:%S'`

# Standard, non-optimized release build
.PHONY: release
release: dirs
	@echo "Beginning release build"
	@$(START_TIME)
	@$(MAKE) all --no-print-directory
	@echo -n "Total build time: "
	@$(END_TIME)

# Debug build for gdb debugging
.PHONY: debug
debug: dirs
	@echo "Beginning debug build"
	@$(START_TIME)
	@$(MAKE) all --no-print-directory
	@echo -n "Total build time: "
	@$(END_TIME)

# Create the directories used in the build
.PHONY: dirs
dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)

# Removes all build files
.PHONY: clean
clean:
	@echo "Deleting $(BIN_NAME) symlink"
	@$(RM) $(BIN_NAME)
	@echo "Deleting directories"
	@$(RM) -r build

# Main rule, checks the executable and symlinks to the output
all: $(BIN_PATH)/$(BIN_NAME)
	@echo "Making symlink: $(BIN_NAME) -> $<"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

# Link the executable
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $@"
	$(CMD_PREFIX)$(CXX) $(OBJECTS) $(LIBS) -o $@

# Source file rules
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp
	@echo "Compiling: $< -> $@"
	$(CMD_PREFIX)$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_PATH)/%.o: $(GENERIC_SRC_PATH)/%.cpp
	@echo "Compiling: $< -> $@"
	$(CMD_PREFIX)$(CXX) $(CXXFLAGS) -c $< -o $@
