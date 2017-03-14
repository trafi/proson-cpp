/*
 * Copyright 2017 TRAFI
 *
 * Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 * http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 * http://opensource.org/licenses/MIT>, at your option. This file may not be
 * copied, modified, or distributed except according to those terms.
 *
 */

#pragma once

#include <google/protobuf/message.h>
#include <proson/error.hpp>

namespace proson {
    result merge(google::protobuf::Message& m, const std::string& json_string);
    result_value<std::string> dump(const google::protobuf::Message& m,
                                   const int indent = -1,
                                   const bool skip_default_values = true);
}