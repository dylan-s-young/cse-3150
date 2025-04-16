# Check if OpenSSL is installed via Homebrew
OPENSSL_PREFIX := $(shell brew --prefix openssl 2>/dev/null)
ifeq ($(OPENSSL_PREFIX),)
    $(error OpenSSL not found. Install it with: brew install openssl)
endif

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I$(OPENSSL_PREFIX)/include
LDFLAGS = -L$(OPENSSL_PREFIX)/lib -lcrypto

# Source files
SOURCES = main.cpp NfToken.cpp ManageTokens.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = nft_app

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean