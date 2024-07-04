// Copyright 2023 StarkWare Industries Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License").
// You may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// https://www.starkware.co/open-source-license/
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions
// and limitations under the License.

#ifndef STARKWARE_UTILS_ALIGNED_UNIQUE_PTR_H_
#define STARKWARE_UTILS_ALIGNED_UNIQUE_PTR_H_

#include <memory>

#define CACHE_LINE_SIZE 64

namespace starkware {

template <auto Function>
using DeleterFromFunction = std::integral_constant<decltype(Function), Function>;

template <typename T>
using AlignedUniquePtr = std::unique_ptr<T, DeleterFromFunction<std::free>>;

template <class T>
AlignedUniquePtr<T> AllocateAlignedBuffer(size_t size, size_t align = CACHE_LINE_SIZE) {
  return AlignedUniquePtr<T>(static_cast<T*>(std::aligned_alloc(align, size * sizeof(T))));
}

}  // namespace starkware

#endif  // STARKWARE_UTILS_ALIGNED_UNIQUE_PTR_H_
