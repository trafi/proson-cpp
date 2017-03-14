#include "catch.hpp"

#include "dto.pb.h"
#include <proson/proson.hpp>

using namespace proson;

TEST_CASE("proson_value_parse_test")
{
    dto::Values values;

    SECTION("check default values")
    {
        auto res = proson::merge(values, "{}");

        REQUIRE(res);
        REQUIRE(values.valdouble() == 0.0);
        REQUIRE(values.valfloat() == 0.0);
        REQUIRE(values.valint32() == 42); // test different default value
        REQUIRE(values.valint64() == 0);
        REQUIRE(values.valuint32() == 0);
        REQUIRE(values.valuint64() == 0);
        REQUIRE(values.valsint32() == 0);
        REQUIRE(values.valsint64() == 0);
        REQUIRE(values.valfixed32() == 0);
        REQUIRE(values.valfixed64() == 0);
        REQUIRE(values.valsfixed32() == 0);
        REQUIRE(values.valsfixed64() == 0);
        REQUIRE(!values.valbool());
        REQUIRE(values.valstring() == "");
        REQUIRE(values.valbytes().size() == 0);
        REQUIRE(values.valenum() == dto::EnumValue::None);
    }

    SECTION("check double")
    {
        SECTION("from float")
        {
            auto res = proson::merge(values, "{ \"ValDouble\": 22.3, \"ValFloat\": 22.3 }");
            REQUIRE(res);
            REQUIRE(values.valdouble() == 22.3);
            REQUIRE(values.valfloat() == 22.3f);
        }

        SECTION("from int")
        {
            auto res = proson::merge(values, "{ \"ValDouble\": 22, \"ValFloat\": 22 }");
            REQUIRE(res);
            REQUIRE(values.valdouble() == 22.0);
            REQUIRE(values.valfloat() == 22.0f);
        }

        SECTION("from bool")
        {
            auto res_d = proson::merge(values, "{ \"ValDouble\": false }");
            REQUIRE(!res_d);
            REQUIRE(res_d.err_value().message
                    == "expected type double, but found value false at ValDouble");

            auto res_f = proson::merge(values, "{ \"ValFloat\": false }");
            REQUIRE(!res_f);
            REQUIRE(res_f.err_value().message
                    == "expected type float, but found value false at ValFloat");
        }

        SECTION("from string")
        {
            auto res_d = proson::merge(values, "{ \"ValDouble\": \"22\" }");
            REQUIRE(!res_d);
            REQUIRE(res_d.err_value().message
                    == "expected type double, but found value \"22\" at ValDouble");

            auto res_f = proson::merge(values, "{ \"ValFloat\": \"22\" }");
            REQUIRE(!res_f);
            REQUIRE(res_f.err_value().message
                    == "expected type float, but found value \"22\" at ValFloat");
        }

        SECTION("from array")
        {
            auto res_d = proson::merge(values, "{ \"ValDouble\": [] }");
            REQUIRE(!res_d);
            REQUIRE(res_d.err_value().message
                    == "expected type double, but found value [] at ValDouble");

            auto res_f = proson::merge(values, "{ \"ValFloat\": [] }");
            REQUIRE(!res_f);
            REQUIRE(res_f.err_value().message
                    == "expected type float, but found value [] at ValFloat");
        }

        SECTION("from object")
        {
            auto res_d = proson::merge(values, "{ \"ValDouble\": {} }");
            REQUIRE(!res_d);
            REQUIRE(res_d.err_value().message
                    == "expected type double, but found value {} at ValDouble");

            auto res_f = proson::merge(values, "{ \"ValFloat\": {} }");
            REQUIRE(!res_f);
            REQUIRE(res_f.err_value().message
                    == "expected type float, but found value {} at ValFloat");
        }

        SECTION("from null")
        {
            auto res_d = proson::merge(values, "{ \"ValDouble\": null }");
            REQUIRE(!res_d);
            REQUIRE(res_d.err_value().message
                    == "expected type double, but found value null at ValDouble");

            auto res_f = proson::merge(values, "{ \"ValFloat\": null }");
            REQUIRE(!res_f);
            REQUIRE(res_f.err_value().message
                    == "expected type float, but found value null at ValFloat");
        }
    }

    SECTION("check int32")
    {
        SECTION("ValInt32")
        {
            SECTION("from int32")
            {
                auto res = proson::merge(values, "{ \"ValInt32\": 22 }");
                REQUIRE(res);
                REQUIRE(values.valint32() == 22);
            }

            SECTION("from int32 negative")
            {
                auto res = proson::merge(values, "{ \"ValInt32\": -22 }");
                REQUIRE(res);
                REQUIRE(values.valint32() == -22);
            }

            SECTION("from uint32")
            {
                auto res = proson::merge(values, "{ \"ValInt32\": 4000000000 }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int32, but found value 4000000000 at ValInt32");
            }

            SECTION("from int64")
            {
                auto res = proson::merge(values, "{ \"ValInt32\": 700000000000 }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int32, but found value 700000000000 at ValInt32");
            }

            SECTION("from uint64")
            {
                auto res = proson::merge(values, "{ \"ValInt32\": 10000000000000000000 }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int32, but found value 10000000000000000000 at ValInt32");
            }

            SECTION("from float")
            {
                auto res = proson::merge(values, "{ \"ValInt32\": 3.14 }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int32, but found value 3.14 at ValInt32");
            }

            SECTION("from bool")
            {
                auto res = proson::merge(values, "{ \"ValInt32\": false }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int32, but found value false at ValInt32");
            }

            SECTION("from string")
            {
                auto res = proson::merge(values, "{ \"ValInt32\": \"false\" }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int32, but found value \"false\" at ValInt32");
            }

            SECTION("from array")
            {
                auto res = proson::merge(values, "{ \"ValInt32\": [] }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int32, but found value [] at ValInt32");
            }

            SECTION("from object")
            {
                auto res = proson::merge(values, "{ \"ValInt32\": {} }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int32, but found value {} at ValInt32");
            }

            SECTION("from null")
            {
                auto res = proson::merge(values, "{ \"ValInt32\": null }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int32, but found value null at ValInt32");
            }
        }

        SECTION("ValSInt32")
        {
            SECTION("from int32")
            {
                auto res = proson::merge(values, "{ \"ValSInt32\": 22 }");
                REQUIRE(res);
                REQUIRE(values.valsint32() == 22);
            }
        }

        SECTION("ValSFixed32")
        {
            SECTION("from int32")
            {
                auto res = proson::merge(values, "{ \"ValSFixed32\": 22 }");
                REQUIRE(res);
                REQUIRE(values.valsfixed32() == 22);
            }
        }
    }

    SECTION("check uint32")
    {
        SECTION("ValUInt32")
        {
            SECTION("from uint32")
            {
                auto res = proson::merge(values, "{ \"ValUInt32\": 22 }");
                REQUIRE(res);
                REQUIRE(values.valuint32() == 22);
            }

            SECTION("from int32 negative")
            {
                auto res = proson::merge(values, "{ \"ValUInt32\": -22 }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint32, but found value -22 at ValUInt32");
            }

            SECTION("from int64")
            {
                auto res = proson::merge(values, "{ \"ValUInt32\": 700000000000 }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint32, but found value 700000000000 at ValUInt32");
            }

            SECTION("from uint64")
            {
                auto res = proson::merge(values, "{ \"ValUInt32\": 10000000000000000000 }");
                REQUIRE(!res);
                REQUIRE(
                    res.err_value().message
                    == "expected type uint32, but found value 10000000000000000000 at ValUInt32");
            }

            SECTION("from float")
            {
                auto res = proson::merge(values, "{ \"ValUInt32\": 3.14 }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint32, but found value 3.14 at ValUInt32");
            }

            SECTION("from bool")
            {
                auto res = proson::merge(values, "{ \"ValUInt32\": false }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint32, but found value false at ValUInt32");
            }

            SECTION("from string")
            {
                auto res = proson::merge(values, "{ \"ValUInt32\": \"false\" }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint32, but found value \"false\" at ValUInt32");
            }

            SECTION("from array")
            {
                auto res = proson::merge(values, "{ \"ValUInt32\": [] }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint32, but found value [] at ValUInt32");
            }

            SECTION("from object")
            {
                auto res = proson::merge(values, "{ \"ValUInt32\": {} }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint32, but found value {} at ValUInt32");
            }

            SECTION("from null")
            {
                auto res = proson::merge(values, "{ \"ValUInt32\": null }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint32, but found value null at ValUInt32");
            }
        }

        SECTION("ValFixed32")
        {
            SECTION("from int32")
            {
                auto res = proson::merge(values, "{ \"ValFixed32\": 22 }");
                REQUIRE(res);
                REQUIRE(values.valfixed32() == 22);
            }
        }
    }

    SECTION("check int64")
    {
        SECTION("ValInt64")
        {
            SECTION("from int64")
            {
                auto res = proson::merge(values, "{ \"ValInt64\": 5140000000 }");
                REQUIRE(res);
                REQUIRE(values.valint64() == 5140000000);
            }

            SECTION("from int64 negative")
            {
                auto res = proson::merge(values, "{ \"ValInt64\": -5140000000 }");
                REQUIRE(res);
                REQUIRE(values.valint64() == -5140000000);
            }

            SECTION("from uint64")
            {
                auto res = proson::merge(values, "{ \"ValInt64\": 18446744073709551600 }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int64, but found value 18446744073709551600 at ValInt64");
            }

            SECTION("from float")
            {
                auto res = proson::merge(values, "{ \"ValInt64\": 3.14 }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int64, but found value 3.14 at ValInt64");
            }

            SECTION("from bool")
            {
                auto res = proson::merge(values, "{ \"ValInt64\": false }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int64, but found value false at ValInt64");
            }

            SECTION("from string")
            {
                auto res = proson::merge(values, "{ \"ValInt64\": \"false\" }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int64, but found value \"false\" at ValInt64");
            }

            SECTION("from array")
            {
                auto res = proson::merge(values, "{ \"ValInt64\": [] }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int64, but found value [] at ValInt64");
            }

            SECTION("from object")
            {
                auto res = proson::merge(values, "{ \"ValInt64\": {} }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int64, but found value {} at ValInt64");
            }

            SECTION("from null")
            {
                auto res = proson::merge(values, "{ \"ValInt64\": null }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type int64, but found value null at ValInt64");
            }
        }

        SECTION("ValSInt64")
        {
            SECTION("from int64")
            {
                auto res = proson::merge(values, "{ \"ValSInt64\": 22 }");
                REQUIRE(res);
                REQUIRE(values.valsint64() == 22);
            }
        }

        SECTION("ValSFixed64")
        {
            SECTION("from int64")
            {
                auto res = proson::merge(values, "{ \"ValSFixed64\": 22 }");
                REQUIRE(res);
                REQUIRE(values.valsfixed64() == 22);
            }
        }
    }

    SECTION("check uint64")
    {
        SECTION("ValUInt64")
        {
            SECTION("from uint64")
            {
                auto res = proson::merge(values, "{ \"ValUInt64\": 22 }");
                REQUIRE(res);
                REQUIRE(values.valuint64() == 22);
            }

            SECTION("from int32 negative")
            {
                auto res = proson::merge(values, "{ \"ValUInt64\": -22 }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint64, but found value -22 at ValUInt64");
            }

            SECTION("from int64 negative")
            {
                auto res = proson::merge(values, "{ \"ValUInt64\": -700000000000 }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint64, but found value -700000000000 at ValUInt64");
            }

            SECTION("from float")
            {
                auto res = proson::merge(values, "{ \"ValUInt64\": 3.14 }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint64, but found value 3.14 at ValUInt64");
            }

            SECTION("from bool")
            {
                auto res = proson::merge(values, "{ \"ValUInt64\": false }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint64, but found value false at ValUInt64");
            }

            SECTION("from string")
            {
                auto res = proson::merge(values, "{ \"ValUInt64\": \"false\" }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint64, but found value \"false\" at ValUInt64");
            }

            SECTION("from array")
            {
                auto res = proson::merge(values, "{ \"ValUInt64\": [] }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint64, but found value [] at ValUInt64");
            }

            SECTION("from object")
            {
                auto res = proson::merge(values, "{ \"ValUInt64\": {} }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint64, but found value {} at ValUInt64");
            }

            SECTION("from null")
            {
                auto res = proson::merge(values, "{ \"ValUInt64\": null }");
                REQUIRE(!res);
                REQUIRE(res.err_value().message
                        == "expected type uint64, but found value null at ValUInt64");
            }
        }

        SECTION("ValFixed64")
        {
            SECTION("from int32")
            {
                auto res = proson::merge(values, "{ \"ValFixed64\": 22 }");
                REQUIRE(res);
                REQUIRE(values.valfixed64() == 22);
            }
        }
    }

    SECTION("check bool")
    {
        SECTION("from bool")
        {
            auto res = proson::merge(values, "{ \"ValBool\": true }");
            REQUIRE(res);
            REQUIRE(values.valbool());
        }

        SECTION("from int")
        {
            auto res = proson::merge(values, "{ \"ValBool\": 22 }");
            REQUIRE(!res);
            REQUIRE(res.err_value().message == "expected type bool, but found value 22 at ValBool");
        }

        SECTION("from float")
        {
            auto res = proson::merge(values, "{ \"ValBool\": 22.0 }");
            REQUIRE(!res);
            REQUIRE(res.err_value().message
                    == "expected type bool, but found value 22.0 at ValBool");
        }

        SECTION("from string")
        {
            auto res = proson::merge(values, "{ \"ValBool\": \"22\" }");
            REQUIRE(!res);
            REQUIRE(res.err_value().message
                    == "expected type bool, but found value \"22\" at ValBool");
        }

        SECTION("from array")
        {
            auto res = proson::merge(values, "{ \"ValBool\": [] }");
            REQUIRE(!res);
            REQUIRE(res.err_value().message == "expected type bool, but found value [] at ValBool");
        }

        SECTION("from object")
        {
            auto res = proson::merge(values, "{ \"ValBool\": {} }");
            REQUIRE(!res);
            REQUIRE(res.err_value().message == "expected type bool, but found value {} at ValBool");
        }

        SECTION("from null")
        {
            auto res = proson::merge(values, "{ \"ValBool\": null }");
            REQUIRE(!res);
            REQUIRE(res.err_value().message
                    == "expected type bool, but found value null at ValBool");
        }
    }

    SECTION("check string")
    {
        SECTION("from string")
        {
            auto res = proson::merge(values, "{ \"ValString\": \"Hello World\" }");
            REQUIRE(res);
            REQUIRE(values.valstring() == "Hello World");
        }

        SECTION("from bool")
        {
            auto res = proson::merge(values, "{ \"ValString\": true }");
            REQUIRE(!res);
            REQUIRE(res.err_value().message
                    == "expected type string, but found value true at ValString");
        }

        SECTION("from int")
        {
            auto res = proson::merge(values, "{ \"ValString\": 22 }");
            REQUIRE(!res);
            REQUIRE(res.err_value().message
                    == "expected type string, but found value 22 at ValString");
        }

        SECTION("from float")
        {
            auto res = proson::merge(values, "{ \"ValString\": 22.0 }");
            REQUIRE(!res);
            REQUIRE(res.err_value().message
                    == "expected type string, but found value 22.0 at ValString");
        }

        SECTION("from array")
        {
            auto res = proson::merge(values, "{ \"ValString\": [] }");
            REQUIRE(!res);
            REQUIRE(res.err_value().message
                    == "expected type string, but found value [] at ValString");
        }

        SECTION("from object")
        {
            auto res = proson::merge(values, "{ \"ValString\": {} }");
            REQUIRE(!res);
            REQUIRE(res.err_value().message
                    == "expected type string, but found value {} at ValString");
        }

        SECTION("from null")
        {
            auto res = proson::merge(values, "{ \"ValString\": null }");
            REQUIRE(!res);
            REQUIRE(res.err_value().message
                    == "expected type string, but found value null at ValString");
        }
    }

    SECTION("check bytes")
    {
        SECTION("from bytes")
        {
            auto res = proson::merge(values, "{ \"ValBytes\": \"\" }");
            REQUIRE(!res);
            REQUIRE(
                res.err_value().message
                == "type conversion from bytes is not implemented, but pull requests are welcome"
                   " at ValBytes");
        }
    }

    SECTION("check enum value")
    {
        SECTION("from enum value")
        {
            auto res = proson::merge(values, "{ \"ValEnum\": 1 }");
            REQUIRE(res);
            REQUIRE(values.valenum() == dto::EnumValue::Some);
        }

        SECTION("from invalid enum value")
        {
            auto res = proson::merge(values, "{ \"ValEnum\": 2 }");
            REQUIRE(!res);
            REQUIRE(
                res.err_value().message
                == "expected one of None = 0, Some = 1, Other = 3, but found value 2 at ValEnum");
        }

        SECTION("from null")
        {
            auto res = proson::merge(values, "{ \"ValEnum\": null }");
            REQUIRE(!res);
            REQUIRE(res.err_value().message
                    == "expected type enum, but found value null at ValEnum");
        }
    }
}