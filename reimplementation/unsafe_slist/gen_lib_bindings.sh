#!/bin/sh
LIB_NAME="libsingly_linked_list_rust.a"
HEADER_FILENAME="rust_lib.h"
rm target/debug/$LIB_NAME 2>/dev/null
cargo build --lib
cargo install cbindgen
cbindgen --config cbindgen.toml --crate singly_linked_list_rust --output ${HEADER_FILENAME}
echo "built: target/debug/${LIB_NAME}\nbindings: ${HEADER_FILENAME}"