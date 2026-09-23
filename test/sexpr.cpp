#include <sstream>

#include <doctest/doctest.h>

#include <mim/driver.h>

#include <mim/ast/ast.h>
#include <mim/ast/parser.h>

#include <mim/plug/sexpr/sexpr.h>

using namespace mim;

namespace {
std::string emit(void (*f)(World&, std::ostream&)) {
    auto driver = Driver();
    auto ast    = ast::AST(driver.world());
    auto parser = ast::Parser(ast);
    auto is     = std::istringstream("extern fun f (x: Nat): Nat = return x;");
    parser.import(is, "sexpr_test.mim")->compile(ast);

    auto os = std::ostringstream();
    f(driver.world(), os);
    return os.str();
}
} // namespace

TEST_CASE("sexpr: emit via GET_FUN_PTR") {
    CHECK(emit(plug::sexpr::emit_plain).starts_with("(root extern f\n    (fun"));
    CHECK(emit(plug::sexpr::emit_typed).starts_with("(root extern f\n    (@ "));
    CHECK(emit(plug::sexpr::emit_slotted).contains("(var $"));
    CHECK(emit(plug::sexpr::emit_slotted_typed).contains("(@ "));
}
