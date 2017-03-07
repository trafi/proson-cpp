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

#include <maybe/result.hpp>
#include <string>

namespace proson {

    enum class MergeJsonErrorType {
        Undefined,
        JsonParse,
        JsonFieldNotObject,
        JsonFieldInvalidType,
        JsonFieldInvalidEnumType,
        TypeConversionNotImplemented,
    };

    class MergeJsonError {
    public:
        MergeJsonErrorType kind = MergeJsonErrorType::Undefined;
        std::string message;
    };

    using result = maybe::result<void, proson::MergeJsonError>;

    template <typename T>
    using result_value = maybe::result<T, proson::MergeJsonError>;
}