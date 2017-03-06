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