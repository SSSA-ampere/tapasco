if(POLICY CMP0069)
  cmake_policy(SET CMP0069 NEW)
endif()

function(set_tapasco_defaults target_name)
    target_compile_options(${target_name} PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>
                                           $<$<CXX_COMPILER_ID:GNU>:-Werror>)
    target_compile_options(${target_name} PRIVATE $<$<C_COMPILER_ID:GNU>:-Wall>
                                       $<$<C_COMPILER_ID:GNU>:-Werror>)
    set_target_properties(${target_name} PROPERTIES DEBUG_POSTFIX d)
    set_target_properties(${target_name} PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
    set_target_properties(${target_name} PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED ON)

    if(${CMAKE_VERSION} VERSION_LESS "3.9.0")
        message("-- Using IPO through fallback! Use CMake version >= 3.9.0 if possible")
        set_target_properties(${target_name} PROPERTIES CMAKE_AR "gcc-ar")
        set_target_properties(${target_name} PROPERTIES CMAKE_RANLIB  "gcc-ranlib")
        target_compile_options(${target_name} PUBLIC $<$<CXX_COMPILER_ID:GNU>:-flto>
                                           $<$<CXX_COMPILER_ID:GNU>:-fno-fat-lto-objects>
                                           $<$<CXX_COMPILER_ID:GNU>:-Werror>)
    else()
        include(CheckIPOSupported)
        check_ipo_supported(RESULT ipo_supported)
        if(ipo_supported)
            set_target_properties(${target_name} PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
        else()
            message(WARNING "IPO is not supported!")
        endif()
    endif()
endfunction(set_tapasco_defaults)