add_library (FatSettings INTERFACE)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(FatSettings INTERFACE
        ## Active warnings
        -Wall
        -Wextra
        -Wpedantic


        ## Configuration-specific
        $<$<CONFIG:Debug>:
            -O0

            -Werror
            -Wno-error=changes-meaning
        >
        $<$<CONFIG:Release>:
            -O3
        >
    )

elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options (FatSettings INTERFACE
        ## Active warnings
        -Weverything
        
        
        ## Inactive warnings
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
        
        -Wno-c++20-compat

        -Wno-padded
        
        -Wno-missing-prototypes
        -Wno-unused-function
        -Wno-unused-private-field


        ## Configuration-specific
        $<$<CONFIG:Debug>:-O0 -Werror>
        $<$<CONFIG:Release>:-O3>
    )

elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options (FatSettings INTERFACE
        # MSVC specific
        /std:c++latest
        /permissive- # Conform to ISO/IEC C++


        ## Active warnings
        /Wall


        ## Inactive warnings
        /wd4061 # Not all enum identifiers of an Enum (class) are handled by a switch statement (When there is a default case)
        /wd4062 # Not all enum identifiers of an Enum (class) are handled by a switch statement (When there is NOT a default case)
        /wd4324 # structure was padded due to alignment specifier
        /wd4514 # Unreferenced inline function has been removed
        /wd4820 # n bytes padding added after construct MyClass
        /wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified


        ## Configuration-specific
        $<$<CONFIG:Debug>:
            /Od

            /Wx # Treat warnings as errors
        >
        $<$<CONFIG:Release>:
            /O2
            /GL # Whole-program optimization

            /Qvec-report:2 # Auto vectorizer reporting (max)
            /Qpar-report:2 # Parallelizer reporting (max)

            /GF # String pooling
        >
    )
endif ()