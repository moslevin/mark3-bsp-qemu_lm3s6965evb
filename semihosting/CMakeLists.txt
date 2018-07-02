project(semihosting)

set(BIN_SOURCES
        semihosting.cpp
)

set(LIB_HEADERS
    public/semihosting.h
)

 
mark3_add_library(semihosting ${BIN_SOURCES})

target_include_directories(semihosting
    PUBLIC
        public
    )

