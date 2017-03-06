#pragma once

#include <error.hpp>
#include <google/protobuf/message.h>

namespace proson {
    result merge(google::protobuf::Message* m, const std::string& json_string);
}