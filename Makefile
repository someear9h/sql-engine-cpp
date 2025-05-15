# Use clang++ on macOS for compatibility with libc++
CXX=clang++
CXXFLAGS=-std=c++17 -Wall

# Target to build the main executable
all: sql_engine

# Rule to build the sql_engine binary
sql_engine: src/main.cpp src/lexer.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp src/lexer.cpp -o sql_engine

# Clean up build artifacts
clean:
	rm -f sql_engine
