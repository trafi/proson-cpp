#pragma once

#include <error.hpp>
#include <google/protobuf/message.h>
#include <string>

#include "field_ref.hpp"

namespace proson {
    namespace internal {
        MergeJsonError error_json_parse(const std::string& message);

        MergeJsonError error_json_field_is_not_an_object(const std::shared_ptr<FieldRef>& field);

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