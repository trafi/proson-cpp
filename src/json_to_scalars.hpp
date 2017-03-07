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

#include <error.hpp>
#include <json.hpp>

#include "field_ref.hpp"

namespace proson {
    namespace internal {
        result_value<std::string> to_string(const std::shared_ptr<FieldRef>& field_ref,
                                            const nlohmann::json& value);
        result_value<double> to_double(const std::shared_ptr<FieldRef>& field_ref,
                                       const nlohmann::json& value);
        result_value<int32_t> to_int32(const std::shared_ptr<FieldRef>& field_ref,
                                       const nlohmann::json& value);
        result_value<uint32_t> to_uint32(const std::shared_ptr<FieldRef>& field_ref,
                                         const nlohmann::json& value);
        result_value<int> to_enum_int(const std::shared_ptr<FieldRef>& field_ref,
                                      const nlohmann::json& value);
        result_value<int64_t> to_int64(const std::shared_ptr<FieldRef>& field_ref,
                                       const nlohmann::json& value);
        result_value<uint64_t> to_uint64(const std::shared_ptr<FieldRef>& field_ref,
                                         const nlohmann::json& value);
        result_value<bool> to_bool(const std::shared_ptr<FieldRef>& field_ref,
                                   const nlohmann::json& value);
        result_value<bool> to_bytes(const std::shared_ptr<FieldRef>& field_ref,
                                    const nlohmann::json& value);
    }
}