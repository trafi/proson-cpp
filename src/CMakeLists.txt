set(TARGET "proson")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_library(${TARGET} STATIC
        proson/create_error.cpp
        proson/create_error.hpp
        proson/error.hpp
        proson/field_ref.cpp
        proson/field_ref.hpp
        proson/json_to_scalars.cpp
        proson/json_to_scalars.hpp
        proson/proson.cpp
        proson/proson.hpp
        )

target_link_libraries(${TARGET}
        PUBLIC protobuf
        )

target_include_directories(${TARGET}
        PUBLIC .
        )

set_target_properties(${TARGET} PROPERTIES
        COMPILE_FLAGS "${COMPILE_FLAGS}"
        )