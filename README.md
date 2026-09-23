# sexpr

A [MimIR](https://github.com/mimir/mimir) plugin that emits a program as symbolic expression, e.g. for equality saturation with [egg](https://egraphs-good.github.io/) or [slotted-egraphs](https://github.com/memoryleak47/slotted-egraphs).

Clone this repository into `extra/sexpr` of a MimIR checkout, and it is built automatically:

```sh
mim foo.mim -p sexpr -X sexpr:o=-                          # egg format to stdout
mim foo.mim -p sexpr -X sexpr:slotted -X sexpr:types -X sexpr:o=foo.sexpr
```

| Argument                  | Description                                                                 |
| ------------------------- | --------------------------------------------------------------------------- |
| `o=<file>, output=<file>` | Output file instead of `<world>.sexpr`/`a.sexpr`; `-` for stdout.          |
| `slotted`                 | Follows the format required by slotted-egraphs.                             |
| `types`                   | Wraps each term in a type annotation; types themselves stay unwrapped.      |

The emission phase `sexpr.emit` is part of `opt`'s `_default_compile`; a custom pipeline needs to list `compile.named "sexpr.emit"` itself.

Other plugins can emit a `World` directly via `mim::plug::sexpr::emit_{plain,typed,slotted,slotted_typed}` from `mim/plug/sexpr/sexpr.h`.
