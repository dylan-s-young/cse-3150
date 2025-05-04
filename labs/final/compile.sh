#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}Compiling TimedSharedPtr Project...${NC}"

# Download doctest.h if it doesn't exist
if [ ! -f "doctest.h" ]; then
    echo -e "${YELLOW}Downloading doctest.h...${NC}"
    curl -s -o doctest.h https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Successfully downloaded doctest.h${NC}"
    else
        echo -e "${RED}Failed to download doctest.h${NC}"
        exit 1
    fi
fi

# Compile test file
echo -e "${YELLOW}Compiling unit tests...${NC}"
g++ -std=c++17 -Wall -Wextra -o test_timed_shared_ptr test_timed_shared_ptr.cpp

if [ $? -eq 0 ]; then
    echo -e "${GREEN}Successfully compiled unit tests${NC}"
else
    echo -e "${RED}Failed to compile unit tests${NC}"
    exit 1
fi

# Compile main program
echo -e "${YELLOW}Compiling main program...${NC}"
g++ -std=c++17 -Wall -Wextra -o main_timed_shared_ptr main.cpp

if [ $? -eq 0 ]; then
    echo -e "${GREEN}Successfully compiled main program${NC}"
else
    echo -e "${RED}Failed to compile main program${NC}"
    exit 1
fi

echo -e "${GREEN}Compilation complete!${NC}"
echo ""
echo -e "${YELLOW}Run unit tests:${NC} ./test_timed_shared_ptr"
echo -e "${YELLOW}Run demo program:${NC} ./main_timed_shared_ptr"
