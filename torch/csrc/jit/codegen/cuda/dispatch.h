#pragma once

#include <torch/csrc/WindowsTorchApiMacro.h>
#include <c10/util/Exception.h>

/*
 * dispatch.h prevents the need from adding manual dispatch in every class that
 * wants to define how to process a series of nodes. dispatch.h provides 4
 * classes that can be inherited providing a means to override functions on a
 * per-node basis. There are currently 4 provided dispatch mechanisms:
 *
 * OptOutDispatch:
 *
 * provides the functions:
 * virtual void handle(ValType* irnode){}
 *
 * This provides a mechanisms to override this handle for particular node
 * types. For example if we only wanted to actually run a function on
 * BinaryOps, we could inherit OptOutDispatch and simply override: void
 * handle(BinaryOp*) { doSomething; } Then we could run through all our
 * Statement* and call OptOutDispatch::handle(statement). When a BinaryOp is
 * encountered our override function will be called. For every other node,
 * nothing will be done.
 *
 * OptInDispatch:
 *
 * This class is similar to OptOutDispatch, however if we encounter a node
 * that we haven't specified an override for in the derived class, an error
 * will be thrown. This is useful if we create a class that is expected to
 * handle any type of node it encounters.
 *
 * OptOutMutator:
 *
 * This class is similar to OptOutDispatch except the functions provided are of
 * type: virtual Statement* mutate(Statement*) this is useful for when we want
 * to have an IR node result from our overloaded functions.
 *
 * OptInMutator:
 *
 * This class is similar to OptInDispatch except the functions provided are of
 * type: virtual Statement* mutate(Statement*) this is useful for when we want
 * to have an IR node result from our overloaded functions.
 */

namespace torch {
namespace jit {
namespace fuser {

struct Fusion;

// Hierarchal dispatch functions for handle
struct Statement;
struct Expr;
struct Val;

// Vals
struct IterDomain;
struct TensorDomain;
struct TensorView;
struct Float;
struct Int;

// Exprs
struct Split;
struct Merge;
struct Reorder;
struct UnaryOp;
struct BinaryOp;

/*
 * By default, all IR nodes are handled in this dispatch, and will call an empty
 * function on all nodes.
 */
struct TORCH_CUDA_API OptOutDispatch {
  virtual ~OptOutDispatch() = default;
  OptOutDispatch() = default;

  OptOutDispatch(const OptOutDispatch& other) = default;
  OptOutDispatch& operator=(const OptOutDispatch& other) = default;

  OptOutDispatch(OptOutDispatch&& other) = default;
  OptOutDispatch& operator=(OptOutDispatch&& other) = default;

  // Hierarchal dispatch functions for handle
  virtual void handle(Statement*);
  virtual void handle(Expr*);
  virtual void handle(Val*);

  // Vals
  virtual void handle(IterDomain*) {}
  virtual void handle(TensorDomain*) {}
  virtual void handle(TensorView*) {}
  virtual void handle(Float*) {}
  virtual void handle(Int*) {}

  // Exprs
  virtual void handle(Split*) {}
  virtual void handle(Merge*) {}
  virtual void handle(Reorder*) {}
  virtual void handle(UnaryOp*) {}
  virtual void handle(BinaryOp*) {}
};

struct TORCH_CUDA_API OptInConstDispatch {
  virtual ~OptInConstDispatch() = default;
  OptInConstDispatch() = default;

  OptInConstDispatch(const OptInConstDispatch& other) = default;
  OptInConstDispatch& operator=(const OptInConstDispatch& other) = default;

  OptInConstDispatch(OptInConstDispatch&& other) = default;
  OptInConstDispatch& operator=(OptInConstDispatch&& other) = default;

  // Hierarchal dispatch functions for handle
  virtual void handle(const Statement* const);
  virtual void handle(const Expr* const);
  virtual void handle(const Val* const);

  // Vals
  virtual void handle(const IterDomain* const) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for IterDomain.");
  }
  virtual void handle(const TensorDomain* const) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for TensorDomain.");
  }
  virtual void handle(const TensorView* const) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for TensorView.");
  }
  virtual void handle(const Float* const) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for Float.");
  }
  virtual void handle(const Int* const) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for Int.");
  }

  // Exprs
  virtual void handle(const Split* const) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for Split.");
  }
  virtual void handle(const Merge* const) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for Merge.");
  }
  virtual void handle(const Reorder* const) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for Reorder.");
  }
  virtual void handle(const UnaryOp* const) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for UnaryOp.");
  }
  virtual void handle(const BinaryOp* const) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for BinaryOp.");
  }
};

struct TORCH_CUDA_API OptInDispatch {
  virtual ~OptInDispatch() = default;
  OptInDispatch() = default;

  OptInDispatch(const OptInDispatch& other) = default;
  OptInDispatch& operator=(const OptInDispatch& other) = default;

  OptInDispatch(OptInDispatch&& other) = default;
  OptInDispatch& operator=(OptInDispatch&& other) = default;

  // Hierarchal dispatch functions for handle
  virtual void handle(Statement* s);
  virtual void handle(Expr* e);
  virtual void handle(Val* v);

  // Vals
  virtual void handle(IterDomain*) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for IterDomain.");
  }
  virtual void handle(TensorDomain*) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for TensorDomain.");
  }
  virtual void handle(TensorView*) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for TensorView.");
  }
  virtual void handle(Float*) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for Float.");
  }
  virtual void handle(Int*) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for Int.");
  }

  // Exprs
  virtual void handle(Split*) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for Split.");
  }
  virtual void handle(Merge*) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for Merge.");
  }
  virtual void handle(Reorder*) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for Reorder.");
  }
  virtual void handle(UnaryOp*) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for UnaryOp.");
  }
  virtual void handle(BinaryOp*) {
    TORCH_INTERNAL_ASSERT(false, "Handle not overriden for BinaryOp.");
  }
};

struct TORCH_CUDA_API OptOutMutator {
  virtual ~OptOutMutator() = default;
  OptOutMutator() = default;

  OptOutMutator(const OptOutMutator& other) = default;
  OptOutMutator& operator=(const OptOutMutator& other) = default;

  OptOutMutator(OptOutMutator&& other) = default;
  OptOutMutator& operator=(OptOutMutator&& other) = default;

  virtual void mutate(Fusion* fusion);

  // Hierarchal dispatch functions for handle
  virtual Statement* mutate(Statement* s);
  virtual Statement* mutate(Expr* e);
  virtual Statement* mutate(Val* v);

  //****Functions below defined in mutator.cpp*****///
  // Vals
  virtual Statement* mutate(IterDomain*);
  virtual Statement* mutate(TensorDomain*);
  virtual Statement* mutate(TensorView*);
  virtual Statement* mutate(Float*);
  virtual Statement* mutate(Int*);

  // Exprs
  virtual Statement* mutate(Split*);
  virtual Statement* mutate(Merge*);
  virtual Statement* mutate(Reorder*);
  virtual Statement* mutate(UnaryOp*);
  virtual Statement* mutate(BinaryOp*);
};

struct TORCH_CUDA_API OptInMutator {
  virtual ~OptInMutator() = default;
  OptInMutator() = default;

  OptInMutator(const OptInMutator& other) = default;
  OptInMutator& operator=(const OptInMutator& other) = default;

  OptInMutator(OptInMutator&& other) = default;
  OptInMutator& operator=(OptInMutator&& other) = default;

  // Hierarchal dispatch functions for mutate
  virtual Statement* mutate(Statement*);
  virtual Statement* mutate(Expr*);
  virtual Statement* mutate(Val*);

  // Vals
  virtual Statement* mutate(IterDomain*) {
    TORCH_INTERNAL_ASSERT(false, "Mutate not overriden for IterDomain.");
  }
  virtual Statement* mutate(TensorDomain*) {
    TORCH_INTERNAL_ASSERT(false, "Mutate not overriden for TensorDomain.");
  }
  virtual Statement* mutate(TensorView*) {
    TORCH_INTERNAL_ASSERT(false, "Mutate not overriden for TensorView.");
  }
  virtual Statement* mutate(Float*) {
    TORCH_INTERNAL_ASSERT(false, "Mutate not overriden for Float.");
  }
  virtual Statement* mutate(Int*) {
    TORCH_INTERNAL_ASSERT(false, "Mutate not overriden for Int.");
  }

  // Exprs
  virtual Statement* mutate(Split*) {
    TORCH_INTERNAL_ASSERT(false, "Mutate not overriden for Split.");
  }
  virtual Statement* mutate(Merge*) {
    TORCH_INTERNAL_ASSERT(false, "Mutate not overriden for Merge.");
  }
  virtual Statement* mutate(Reorder*) {
    TORCH_INTERNAL_ASSERT(false, "Mutate not overriden for Reorder.");
  }
  virtual Statement* mutate(UnaryOp*) {
    TORCH_INTERNAL_ASSERT(false, "Mutate not overriden for UnaryOp.");
  }
  virtual Statement* mutate(BinaryOp*) {
    TORCH_INTERNAL_ASSERT(false, "Mutate not overriden for BinaryOp.");
  }
};

} // namespace fuser
} // namespace jit
} // namespace torch
