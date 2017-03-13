#include "catch.hpp"

#include <proson/proson.hpp>
#include "example_dto.pb.h"

using namespace proson;
using namespace example_dto;

TEST_CASE("example_test")
{
    SECTION("happy case")
    {
        Servo servo;

        auto merge_ok = proson::merge(servo, R"json(
            {
                "targets": [
                    {
                        "updated_at": 1434555532,
                        "pos": {
                            "x": 3,
                            "y": 5
                        }
                    },
                    {
                        "updated_at": 1437234456,
                        "pos": {
                            "x": 5,
                            "y": 9
                        }
                    }
                ],
                "rpm": 4535.6,
                "air": 5
            }
        )json");

        CHECK(merge_ok);
        if (!merge_ok) {
            CHECK(merge_ok.err_value().message == "");
        }

        CHECK(servo.has_air());
        CHECK(servo.air() == Air::Hot);

        REQUIRE(servo.targets_size() == 2);
        CHECK(servo.targets(0).updated_at() == 1434555532);
        CHECK(servo.targets(0).pos().x() == 3);
        CHECK(servo.targets(0).pos().y() == 5);
        CHECK(servo.targets(1).updated_at() == 1437234456);
        CHECK(servo.targets(1).pos().x() == 5);
        CHECK(servo.targets(1).pos().y() == 9);

        CHECK(servo.rpm() == Approx(4535.6));
    }

    SECTION("incomplete data")
    {
        Servo servo;
        servo.set_air(Air::Cold); // set existing value

        auto merge_ok = proson::merge(servo, R"json(
            {
                "targets": [
                    {
                        "pos": {
                            "x": 3
                        }
                    }
                ]
            }
        )json");

        CHECK(merge_ok);
        if (!merge_ok) {
            CHECK(merge_ok.err_value().message == "");
        }

        CHECK(servo.has_air()); // value was not modified
        CHECK(servo.air() == Air::Cold);

        REQUIRE(servo.targets_size() == 1);
        CHECK(servo.targets(0).pos().x() == 3);
        CHECK(servo.targets(0).pos().y() == 0);
    }

    SECTION("nice_errors")
    {
        Servo servo;

        auto merge_ok = proson::merge(servo, R"json(
            {
                "targets": [
                    {
                        "pos": "hello error"
                    }
                ]
            }
        )json");

        REQUIRE(!merge_ok);
        REQUIRE(merge_ok.err_value().message
                == "expected type object, but found value \"hello error\" at targets[0].pos");
    }
}