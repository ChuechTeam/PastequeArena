# Egregiously stolen from raylib
macro(enum_option var values description)
    set(${var}_VALUES ${values})
    list(GET ${var}_VALUES 0 default)
    set(${var} "${default}" CACHE STRING "${description}")
    set_property(CACHE ${var} PROPERTY STRINGS ${${var}_VALUES})
    if (NOT ";${${var}_VALUES};" MATCHES ";${${var}};")
        message(FATAL_ERROR "Unknown value ${${var}}. Only -D${var}=${${var}_VALUES} allowed.")
    endif()
endmacro()

option(PA_PACKAGED "Builds the game in packaged mode: pack and bundle assets for use with the game" OFF)