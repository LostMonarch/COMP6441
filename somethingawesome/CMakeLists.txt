# CMakeLists file for building fraud detector Something Awesome project

# CMake declarations
cmake_minimum_required (VERSION 3.6)
project (Awesome)

# Pull in sources and headers
set(SOURCES 
    main.cpp
    Bank.cpp
)

set(HEADERS
     CustomerProfile.h 
     card.h
     transaction.h
     vendorType.h
     TransactionHistory.h
     Customer.h
     Bank.h
     FraudDetector.h
)

# Include headers
include_directories(${HEADERS})

# Add target executable
add_executable(main ${SOURCES})