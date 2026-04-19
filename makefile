# Windows Makefile (MinGW/MSYS2)
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -static-libgcc -static-libstdc++
TARGET = webserver.exe
SRC = src/webserver.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lws2_32

debug:
	$(CXX) $(CXXFLAGS) -g -O0 -DDEBUG -o $(TARGET) $(SRC) -lws2_32

run: $(TARGET)
	@mkdir -p public 2>nul
	@copy style.css public\ 2>nul || echo "CSS not found, using embedded"
	@copy script.js public\ 2>nul || echo "JS not found, using embedded"
	.\$(TARGET)

clean:
	del /Q $(TARGET) 2>nul || true

.PHONY: all debug run clean