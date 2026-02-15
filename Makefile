CXX = g++
GCOV = gcov

CXXFLAGS = -std=c++11 -Wall -Wextra -g
CXXFLAGS += -I include -I /usr/local/include
COVERAGE += -fprofile-arcs -ftest-coverage


### NAMES ###
TARGET_NAME = chess
TEST_NAME = test_main


### COMMON ###
BUILD_PATH = build
OBJ_PATH = $(BUILD_PATH)/obj
BIN_PATH = $(BUILD_PATH)/bin
GCOV_PATH = $(BUILD_PATH)/gcov
MISC_PATH = $(BUILD_PATH)/misc


### TARGET ###
SRC_PATH = src
TARGET = $(BIN_PATH)/$(TARGET_NAME)


### TEST PATH ###
TEST_PATH = test
TEST = $(BIN_PATH)/$(TEST_NAME)
TEST_OBJ_PATH = $(BUILD_PATH)/obj


### DOCS ###
DOCS_PATH = docs
DOCS_HTML = $(DOCS_PATH)/html/index.html
DOXYFILE = $(DOCS_PATH)/Doxyfile


SRC = $(wildcard $(SRC_PATH)/*.cpp)
OBJ = $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.o, $(SRC))

TEST_SRC = $(wildcard $(TEST_PATH)/*.cpp)
TEST_OBJ = $(patsubst $(TEST_PATH)/%.cpp, $(TEST_OBJ_PATH)/%.o, $(TEST_SRC)) #Adds all the .o files in test/
TEST_OBJ += $(filter-out $(OBJ_PATH)/main.o, $(OBJ)) # Add all OBJ except main.o to avoid mult. main because of CATCH_CONFIG_MAIN


default: all


### TARGET ###
$(TARGET): $(OBJ) 
	@echo "Linking"
	@$(CXX) $(CXXFLAGS) $(COVERAGE) -o $@ $(OBJ)
	# Gets rid of files created by coverage
	mv $(OBJ_PATH)/*.gcda $(MISC_PATH) 
	mv $(OBJ_PATH)/*.gcno $(MISC_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp | dirs
	@echo "Compiling $<"
	@g++ $(CXXFLAGS) $(COVERAGE) -c -o $@ $<


### Test ###	
$(TEST): $(TEST_OBJ)
	@echo "Linking"
	@$(CXX) $(CXXFLAGS) $(COVERAGE) -o $@ $^

$(TEST_OBJ_PATH)/%.o: $(TEST_PATH)/%.cpp | dirs
	@echo "Compiling $<"
	@g++ $(CXXFLAGS) $(COVERAGE) -c -o $@ $<


.PHONY: all
all: dirs $(TARGET)

### RUNNERS ###
.PHONY: run
run: $(TARGET)
	@echo "Running $(TARGET_NAME)"
	@./$(TARGET)

.PHONY: run_test
run_test: $(TEST) #run all tests
	@echo "Running $(TEST_NAME)"
	@./$(TEST)


### TEST ###
.PHONY: test_bin
test_bin: $(TEST) # Create bin only
	@echo "Building $(BIN_PATH)/$(TEST_NAME)"
	@echo "Compile with ./$(BIN_PATH)/$(TEST_NAME) and Catch Arguments"

gcov: $(SRC) # Create coverage report
	- gcov -r $(SRC) -o $(OBJ_PATH)
	mv *.gcov $(GCOV_PATH)


### BUILDERS ###
.PHONY: dirs
dirs:
	@echo "Creating directories"
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(SRC_PATH)
	@mkdir -p $(GCOV_PATH)


### DOCS ###
.PHONY: opendocs
opendocs: docs
	@echo "Opening docs"
	@xdg-open $(DOCS_HTML)

.PHONY: docs
docs: 
	@echo "Generating docs"
	@doxygen $(DOXYFILE)


### CLEAN ###
.PHONY: clean
clean:
	@echo "Deleting directories"
	@rm -r $(BUILD_PATH)