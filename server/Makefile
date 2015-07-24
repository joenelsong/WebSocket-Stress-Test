SOURCE_PATH=src
BUILD_PATH=build
INCLUDE_PATH=include
BIN_PATH=bin
LOG_PATH=log
APPLICATION_NAME=quicksocket
FILES=quicksocket.C http_request.C http_response.C tcp_listener.C websocket_frame.C
SOURCES = $(FILES:%.cpp=$(SOURCE_PATH)/%.cpp)
OBJ=$(FILES:%.C=$(BUILD_PATH)/%.o)

all: folders $(OBJ)
	g++ -std=c++11 -o $(BIN_PATH)/$(APPLICATION_NAME) -I./$(INCLUDE_PATH) $(OBJ) -L/usr/lib -lssl -lcrypto -pthread

$(BUILD_PATH)/%.o : $(SOURCE_PATH)/%.C
	g++ -std=c++11 -o $@ -g -I./$(INCLUDE_PATH) -c $< -L/usr/lib -lssl -lcrypto -pthread

debug: folders $(OBJ)
	g++ -std=c++11 -g -DDEBUG_MODE -o $(BIN_PATH)/$(APPLICATION_NAME) -I./$(INCLUDE_PATH) $(OBJ) -L/usr/lib -lssl -lcrypto -pthread

run: all
	$(BIN_PATH)/$(APPLICATION_NAME)
	
test: debug
	#TODO make automated test script to go here
	
folders:
	mkdir -p $(BIN_PATH) $(BUILD_PATH) $(LOG_PATH)
	
clean:
	rm -f $(BUILD_PATH)/*.o $(BIN_PATH)/$(APPLICATION_NAME) $(LOG_PATH)/*.log
	rm -rf $(BUILD_PATH)
	rm -rf $(BIN_PATH)
	rm -rf $(LOG_PATH)

