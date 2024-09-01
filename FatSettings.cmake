add_library (FatSettings INTERFACE)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    target_compile_options (FatSettings INTERFACE
        ## Active warnings
        -Weverything
        -Wmicrosoft
        
        
        ## Inactive warnings
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
        
        -Wno-c++20-compat
        
        -Wno-missing-prototypes
        -Wno-unused-function
        -Wno-unused-private-field


        ## Errors
        -Werror


        ## Optimizations
        $<$<CONFIG:Debug>:-O0>
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
        /wd4820
        /wd5045
        /wd4514

        # for my library code
        /wd4061 /wd4668 /wd5039 /wd4365 /wd4265 /wd5220 /wd4625 /wd4626 /wd5204

        ## Errors
        /Wx # Treat warnings as errors

        ## Optimizations
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Release>:
            /O2
            /Qvec-report:2
            /Qpar-report:2

            /GF # String pooling
        >
    )
endif ()
