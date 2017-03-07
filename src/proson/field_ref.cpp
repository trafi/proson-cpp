/*
 * Copyright 2017 TRAFI
 *
 * Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 * http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 * http://opensource.org/licenses/MIT>, at your option. This file may not be
 * copied, modified, or distributed except according to those terms.
 *
 */

#include "field_ref.hpp"

#include <sstream>

using namespace std;
using namespace proson::internal;

FieldRef::FieldRef(string name) : _name(move(name))
{
}

FieldRef::FieldRef(int array_index) : _array_index(move(array_index))
{
}

FieldRef::FieldRef(string name, shared_ptr<FieldRef> parent)
    : _name(move(name)), parent(move(parent))
{
}

FieldRef::FieldRef(int array_index, shared_ptr<FieldRef> parent)
    : _array_index(move(array_index)), parent(move(parent))
{
}

namespace {
    void output_full_field_name(const FieldRef& field, ostringstream& ss)
    {
        if (nullptr != field.parent) {
            output_full_field_name(*field.parent, ss);
            if (field.array_index() == -1) {
                ss << ".";
            }
        }

        ss << field.name();
        if (field.array_index() != -1) {
            ss << "[" << field.array_index() << "]";
        }
    }
}

string FieldRef::full_name() const
{
    ostringstream ss;
    output_full_field_name(*this, ss);
    return ss.str();
}

std::string FieldRef::name() const
{
    return _name;
}

int FieldRef::array_index() const
{
    return _array_index;
}
