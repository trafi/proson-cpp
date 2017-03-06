cmake_minimum_required(VERSION 3.0)
project(proson)

SET(EXPERIMENTAL_OPTIONAL_INCLUDE "" CACHE PATH "Path to experimental optional include directory.")
SET(MAYBE_RESULT_INCLUDE "" CACHE PATH "Path to trafi/maybe-result-cpp include directory.")
SET(NLOHMANN_JSON_INCLUDE "" CACHE PATH "Path to nlohmann/json include directory.")
SET(PROTOBUF_INCLUDE "" CACHE PATH "Path to protobuf include directory.")
SET(PROTOBUF_LINK_DIRECTORY "" CACHE PATH "Path to protobuf library directory.")

if (NOT EXISTS "${EXPERIMENTAL_OPTIONAL_INCLUDE}")
    message(FATAL_ERROR "Set EXPERIMENTAL_OPTIONAL_INCLUDE path and reload cache.")
endif ()

if (NOT EXISTS "${MAYBE_RESULT_INCLUDE}")
    message(FATAL_ERROR "Set MAYBE_RESULT_INCLUDE path and reload cache.")
endif ()

if (NOT EXISTS "${NLOHMANN_JSON_INCLUDE}")
    message(FATAL_ERROR "Set NLOHMANN_JSON_INCLUDE path and reload cache.")
endif ()

if (NOT EXISTS "${PROTOBUF_INCLUDE}")
    message(FATAL_ERROR "Set PROTOBUF_INCLUDE path and reload cache.")
endif ()

if (NOT EXISTS "${PROTOBUF_LINK_DIRECTORY}")
    message(FATAL_ERROR "Set PROTOBUF_LINK_DIRECTORY path and reload cache.")
endif ()

include_directories(
    PUBLIC src
    PUBLIC ${EXPERIMENTAL_OPTIONAL_INCLUDE}
    PUBLIC ${MAYBE_RESULT_INCLUDE}
    PRIVATE ${NLOHMANN_JSON_INCLUDE}
    PRIVATE ${PROTOBUF_INCLUDE}
)

LINK_DIRECTORIES(${PROTOBUF_LINK_DIRECTORY})

add_subdirectory(src)
add_subdirectory(tests)