add_library(darr darr.c darr.h)

set_target_properties(darr PROPERTIES C_STANDARD 11)

# Error messages: the more the better.
target_compile_options(darr PRIVATE -Wall -Wextra)

# Turn certain warning messages into error messages.
target_compile_options(darr PRIVATE -Werror=incompatible-pointer-types)

# Suppress less desirable warning messages.
target_compile_options(darr PRIVATE -Wno-unused-variable)
