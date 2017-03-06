set(TARGET "tests")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(${TARGET}
        dto.pb.h
        dto.pb.cc
        main.cpp
        proson_value_parse.cpp
        proson_nested_parse.cpp
        )

SET_SOURCE_FILES_PROPERTIES(dto.pb.cc PROPERTIES LANGUAGE CXX)

target_link_libraries(${TARGET}
        PUBLIC proson
        )

target_include_directories(${TARGET}
        PRIVATE ../src
        )