#pragma once

#include <ostream>

#include <mim/driver.h>
#include <mim/world.h>

namespace mim::plug::sexpr {

/// Implemented in `libmim_sexpr`; the wrappers below look it up via `GET_FUN_PTR`.
extern "C" MIM_EXPORT void mim_sexpr_emit(World&, std::ostream&, bool typed, bool slotted);

namespace detail {
inline void emit(World& world, std::ostream& ostream, bool typed, bool slotted) {
    auto& driver = world.driver();
    if (!driver.is_loaded("sexpr")) driver.load("sexpr");
    driver.GET_FUN_PTR("sexpr", mim_sexpr_emit)(world, ostream, typed, slotted);
}
} // namespace detail

/// @name Emit a World as Symbolic Expression
/// The `slotted` variants follow the format required by slotted-egraphs.
///@{
inline void emit_plain(World& world, std::ostream& ostream) { detail::emit(world, ostream, false, false); }
inline void emit_typed(World& world, std::ostream& ostream) { detail::emit(world, ostream, true, false); }
inline void emit_slotted(World& world, std::ostream& ostream) { detail::emit(world, ostream, false, true); }
inline void emit_slotted_typed(World& world, std::ostream& ostream) { detail::emit(world, ostream, true, true); }
///@}

} // namespace mim::plug::sexpr
