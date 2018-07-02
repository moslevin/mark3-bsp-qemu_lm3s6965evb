project(startup)

set(BIN_SOURCES
	startup.c
)
 
mark3_add_library(startup ${BIN_SOURCES})

set_target_properties(
    startup
    PROPERTIES
        COMPILE_FLAGS "${mark3_cc_flags}"
        LINK_FLAGS "${mark3_ln_flags}"
    )

