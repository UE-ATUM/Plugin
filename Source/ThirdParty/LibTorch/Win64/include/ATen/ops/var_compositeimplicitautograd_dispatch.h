#pragma once
// @generated by torchgen/gen.py from DispatchKeyFunction.h

// NB: The implementing C++ file is RegisterDispatchKey.cpp

// The only #includes we need are for custom classes that have defaults in the C++ API
#include <c10/core/MemoryFormat.h>
#include <c10/core/Scalar.h>
#include <ATen/core/Reduction.h>

// Forward declarations of any types needed in the operator signatures.
// We can't directly include these classes because it will cause circular include dependencies.
// This file is included by TensorBody.h, which defines the Tensor class.
#include <ATen/core/ATen_fwd.h>

namespace at {

namespace compositeimplicitautograd {

TORCH_API at::Tensor var(const at::Tensor & self, bool unbiased);
TORCH_API at::Tensor var(const at::Tensor & self, at::OptionalIntArrayRef dim, bool unbiased, bool keepdim=false);
TORCH_API at::Tensor & var_out(at::Tensor & out, const at::Tensor & self, at::OptionalIntArrayRef dim, bool unbiased, bool keepdim=false);
TORCH_API at::Tensor & var_outf(const at::Tensor & self, at::OptionalIntArrayRef dim, bool unbiased, bool keepdim, at::Tensor & out);
TORCH_API at::Tensor var(const at::Tensor & self, at::DimnameList dim, bool unbiased, bool keepdim=false);
TORCH_API at::Tensor & var_out(at::Tensor & out, const at::Tensor & self, at::DimnameList dim, bool unbiased, bool keepdim=false);
TORCH_API at::Tensor & var_outf(const at::Tensor & self, at::DimnameList dim, bool unbiased, bool keepdim, at::Tensor & out);
TORCH_API at::Tensor var(const at::Tensor & self, at::DimnameList dim, c10::optional<int64_t> correction=c10::nullopt, bool keepdim=false);
TORCH_API at::Tensor & var_out(at::Tensor & out, const at::Tensor & self, at::DimnameList dim, c10::optional<int64_t> correction=c10::nullopt, bool keepdim=false);
TORCH_API at::Tensor & var_outf(const at::Tensor & self, at::DimnameList dim, c10::optional<int64_t> correction, bool keepdim, at::Tensor & out);

} // namespace compositeimplicitautograd
} // namespace at