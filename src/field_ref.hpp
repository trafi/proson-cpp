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