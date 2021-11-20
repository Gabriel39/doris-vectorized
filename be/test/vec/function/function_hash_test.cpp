// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include <gtest/gtest.h>
#include <time.h>

#include "function_test_util.h"
#include "runtime/tuple_row.h"
#include "vec/functions/simple_function_factory.h"

namespace doris {

using vectorized::Null;
using vectorized::DataSet;

TEST(HashFunctionTest, murmur_hash_3_test) {
    std::string func_name = "murmur_hash3_32";

    {
        std::vector<std::any> input_types = {vectorized::TypeIndex::String};

        DataSet data_set = {{{Null()}, Null()},
                            {{std::string("hello")}, (int32_t) 1321743225}};

        vectorized::check_function<vectorized::DataTypeInt32, true>(func_name, input_types, data_set);
    };

    {
        std::vector<std::any> input_types = {vectorized::TypeIndex::String,
                                             vectorized::TypeIndex::String};

        DataSet data_set = {{{std::string("hello"), std::string("world")}, (int32_t) 984713481},
                            {{std::string("hello"), Null()}, Null()}};

        vectorized::check_function<vectorized::DataTypeInt32, true>(func_name, input_types, data_set);
    };

    {
        std::vector<std::any> input_types = {vectorized::TypeIndex::String,
                                             vectorized::TypeIndex::String,
                                             vectorized::TypeIndex::String};

        DataSet data_set = {{{std::string("hello"), std::string("world"), std::string("!")}, (int32_t) -666935433},
                            {{std::string("hello"), std::string("world"), Null()}, Null()}};

        vectorized::check_function<vectorized::DataTypeInt32, true>(func_name, input_types, data_set);
    };
}

TEST(HashFunctionTest, murmur_hash_2_test) {
    std::string func_name = "murmurHash2_64";

    {
        std::vector<std::any> input_types = {vectorized::TypeIndex::String};

        DataSet data_set = {{{Null()}, Null()},
                            {{std::string("hello")}, (uint64_t) 2191231550387646743}};

        vectorized::check_function<vectorized::DataTypeUInt64, true>(func_name, input_types, data_set);
    };

    {
        std::vector<std::any> input_types = {vectorized::TypeIndex::String,
                                             vectorized::TypeIndex::String};

        DataSet data_set = {{{std::string("hello"), std::string("world")}, (uint64_t) 11978658642541747642},
                            {{std::string("hello"), Null()}, Null()}};

        vectorized::check_function<vectorized::DataTypeUInt64, true>(func_name, input_types, data_set);
    };

    {
        std::vector<std::any> input_types = {vectorized::TypeIndex::String,
                                             vectorized::TypeIndex::String,
                                             vectorized::TypeIndex::String};

        DataSet data_set = {{{std::string("hello"), std::string("world"), std::string("!")}, (uint64_t) 1367324781703025231},
                            {{std::string("hello"), std::string("world"), Null()}, Null()}};

        vectorized::check_function<vectorized::DataTypeUInt64, true>(func_name, input_types, data_set);
    };
}

} // namespace doris

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
