set(TARGET "tests")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(${TARGET}
        dto.pb.h
        dto.pb.cc
        example_dto.pb.h
        example_dto.pb.cc
        main.cpp
        proson_value_parse_test.cpp
        proson_nested_parse_test.cpp
        example_test.cpp
        )

target_link_libraries(${TARGET}
        PUBLIC proson
        )

target_include_directories(${TARGET}
        PRIVATE ../src
        )