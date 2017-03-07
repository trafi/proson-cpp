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

#include <proson/error.hpp>
#include <proson/field_ref.hpp>
#include <google/protobuf/message.h>
#include <string>

namespace proson {
    namespace internal {
        MergeJsonError error_json_parse(const std::string& message);

        MergeJsonError error_json_field_invalid_type(const std::shared_ptr<FieldRef>& field,
                                                     const std::string& expected_type,
                                                     std::string value);

        MergeJsonError error_json_field_invalid_enum_value_type(
            const std::shared_ptr<FieldRef>& field,
            int invalid_value,
            const google::protobuf::EnumDescriptor* enum_desc);

        MergeJsonError error_type_conversion_not_implemented(const std::shared_ptr<FieldRef>& field,
                                                             const std::string& expected_type);
    }
}