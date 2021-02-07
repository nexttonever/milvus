// Copyright (C) 2019-2020 Zilliz. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software distributed under the License
// is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
// or implied. See the License for the specific language governing permissions and limitations under the License

#pragma once
#include "knowhere/index/structured_index_simple/StructuredIndexSort.h"
#include "common/Span.h"
#include "common/FieldMeta.h"
#include <memory>

namespace milvus::query {

template <typename T>
inline std::unique_ptr<knowhere::scalar::StructuredIndex<T>>
generate_scalar_index(Span<T> data) {
    auto indexing = std::make_unique<knowhere::scalar::StructuredIndexSort<T>>();
    indexing->Build(data.row_count(), data.data());
    return indexing;
}

inline std::unique_ptr<knowhere::Index>
generate_scalar_index(SpanBase data, DataType data_type) {
    Assert(!datatype_is_vector(data_type));
    switch (data_type) {
        case DataType::BOOL:
            return generate_scalar_index(Span<bool>(data));
        case DataType::INT8:
            return generate_scalar_index(Span<int8_t>(data));
        case DataType::INT16:
            return generate_scalar_index(Span<int16_t>(data));
        case DataType::INT32:
            return generate_scalar_index(Span<int32_t>(data));
        case DataType::INT64:
            return generate_scalar_index(Span<int64_t>(data));
        case DataType::FLOAT:
            return generate_scalar_index(Span<float>(data));
        case DataType::DOUBLE:
            return generate_scalar_index(Span<double>(data));
        default:
            PanicInfo("unsupported type");
    }
}

}  // namespace milvus::query
