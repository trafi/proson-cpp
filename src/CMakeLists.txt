set(TARGET "proson")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_library(${TARGET} STATIC
        create_error.cpp
        create_error.hpp
        error.hpp
        field_ref.cpp
        field_ref.hpp
        json_to_scalars.cpp
        json_to_scalars.hpp
        proson.cpp
        proson.hpp
        )

target_link_libraries(${TARGET}
        PUBLIC protobuf
        )

target_include_directories(${TARGET}
        PUBLIC src
        )

set_target_properties(${TARGET} PROPERTIES
        COMPILE_FLAGS "${COMPILE_FLAGS}"
        )