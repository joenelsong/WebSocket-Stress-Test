SOURCE_PATH=src
BUILD_PATH=build
INCLUDE_PATH=include
BIN_PATH=bin
LOG_PATH=log
APPLICATION_NAME=quicksocket
FILES=quicksocket.C HTTPrequest.C
SOURCES = $(FILES:%.cpp=$(SOURCE_PATH)/%.cpp)
OBJ=$(FILES:%.C=$(BUILD_PATH)/%.o)

all: folders $(OBJ)
	g++ -o $(BIN_PATH)/$(APPLICATION_NAME) -I./$(INCLUDE_PATH) -L/usr/lib -lssl -lcrypto $(OBJ)

$(BUILD_PATH)/%.o : $(SOURCE_PATH)/%.C
	g++ -o $@ -g -I./$(INCLUDE_PATH) -c $<

debug: folders $(OBJ)
	g++ -g -DDEBUG_MODE -o $(BIN_PATH)/$(APPLICATION_NAME) -I./$(INCLUDE_PATH) -L/usr/lib -lssl -lcrypto $(OBJ)

run: all
	$(BIN_PATH)/$(APPLICATION_NAME)
	
test: debug
	#TODO make automated test script to go here
	
prog: folders $(OBJ)
	g++ $(OBJ) -o $(BIN_PATH)/$(APPLICATION_NAME)

$(BUILD_PATH)/%.o : $(SOURCE_PATH)/%.C
	g++ -o $@ -g -I./$(INCLUDE_PATH) -c $<
	
folders:
	mkdir -p $(BIN_PATH) $(BUILD_PATH) $(LOG_PATH)
	
clean:
	rm -f $(BUILD_PATH)/*.o $(BIN_PATH)/$(APPLICATION_NAME) $(LOG_PATH)/*.log
	rm -rf $(BUILD_PATH)
	rm -rf $(BIN_PATH)
	rm -rf $(LOG_PATH)
