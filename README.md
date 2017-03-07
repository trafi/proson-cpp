# Proson

Merge JSON data into any Protobuf object at runtime. Requires C++14 (see requirements section bellow).

## Examples

Let's say we have this `example.proto` schema:

```proto
package example_dto;

enum Air {
    Hot = 5;
    Cold = 0;
}

message Position {
    required double x = 1;
    required double y = 2;
    required double z = 3;
}

message Target {
    required sint64 updated_at = 1;
    required Position pos = 2;
}

message Servo {
    repeated Target targets = 1;
    optional float rpm = 2;
    optional Air air = 3;
}
```

This library can build `Servo` value from JSON string:

```cpp
#include <proson.hpp>
#include "example_dto.pb.h"

TEST_CASE("example_test") // uses #include "catch.hpp" for testing
{
    Servo servo;
    
    auto merge_ok = proson::merge(&servo, R"json(
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
```

### Incomplete JSON data

It is possible to merge incomplete JSON data. In that case,
values that are defined in JSON are replaced:

```cpp
TEST_CASE("incomplete data")
{
    Servo servo;
    servo.set_air(Air::Cold); // set existing value

    auto merge_ok = proson::merge(&servo, R"json(
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

    CHECK(servo.has_air()); // value was not modified
    CHECK(servo.air() == Air::Cold);

    REQUIRE(servo.targets_size() == 1);
    CHECK(servo.targets(0).pos().x() == 3);
    CHECK(servo.targets(0).pos().y() == 0);
}
```

### Comprehensive errors

Library was designed for use in tests, so having good errors was one of the
main goals:

```cpp
TEST_CASE("nice_errors")
{
    Servo servo;

    auto merge_ok = proson::merge(&servo, R"json(
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
```

## Requirements

### C++14

A C++ compiler supporting C++14 is required. 
You can use -std=c++14 flag for sufficiently recent versions 
of GCC (4.9) or CLANG (3.7). Library was tested on CLANG for use 
on iOS and Android.

### Required header-only libraries

* [`maybe::result`][maybe-result] library is used to for error handling.
* [`experimental::optional`][optional] library is required by `maybe::result` for optional type (this will remain until `maybe::result` can use `std::variant` on Android).
* [`nlohmann::json`][json] (2.1) library is used for json parsing.

[maybe-result]: https://github.com/trafi/maybe-result-cpp
[optional]: https://github.com/akrzemi1/Optional
[json]: https://github.com/nlohmann/json

### Required compiled libraries

* [`google::protobuf`][protobuf] (3.2) library is required for protobuf 
reflection (other versions were not tested, but may work). 

[protobuf]: https://github.com/google/protobuf

### Usage

See top-level `CMakeLists.txt` to see the list of required settings.
See `src/CMakeLists.txt` to see the list of cpp files.

## License

Licensed under either of

 * Apache License, Version 2.0, ([LICENSE-APACHE](LICENSE-APACHE) or http://www.apache.org/licenses/LICENSE-2.0)
 * MIT license ([LICENSE-MIT](LICENSE-MIT) or http://opensource.org/licenses/MIT)

at your option.

### Contribution

Unless you explicitly state otherwise, any contribution intentionally
submitted for inclusion in the work by you, as defined in the Apache-2.0
license, shall be dual licensed as above, without any additional terms or
conditions.