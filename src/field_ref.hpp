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

#include <memory>
#include <string>

namespace proson {
    namespace internal {
        class FieldRef {
        private:
            std::string _name;
            int _array_index = -1;

        public:
            const std::shared_ptr<FieldRef> parent = nullptr;

            explicit FieldRef(std::string name);
            explicit FieldRef(int array_index);
            FieldRef(std::string name, std::shared_ptr<FieldRef> parent);
            FieldRef(int array_index, std::shared_ptr<FieldRef> parent);
            std::string full_name() const;
            std::string name() const;
            int array_index() const;
        };
    }
}