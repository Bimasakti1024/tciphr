cmake_minimum_required(VERSION 3.10)
project(tciphr C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

add_executable(tciphr
    src/main.c

    src/util.c
    src/crack_param.c
    src/cipher/ciphers.c
    src/kasiski.c
    src/frequency.c

    # Monoalphabetic substitution cipher
    src/cipher/caesar.c
    src/cipher/atbash.c
    src/cipher/rot13.c

    # Polyalphabetic substitution cipher
    src/cipher/vigenere.c
    src/cipher/autokey.c
    src/cipher/beaufort.c

    # Transposition cipher
    src/cipher/railfence.c

    # Cracker
    src/cracker/autokey_cracker.c
    src/cracker/vigenere_cracker.c
    src/cracker/beaufort_cracker.c
    src/cracker/railfence_cracker.c
    src/cracker/caesar_cracker.c
)
target_include_directories(tciphr PRIVATE src)

target_compile_options(tciphr PRIVATE -Wall -Wextra)

target_compile_options(tciphr PRIVATE
    $<$<CONFIG:Debug>:-g -O0 -fsanitize=address>
    $<$<CONFIG:Release>:-O3>
)

target_link_libraries(tciphr PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address>
)

target_link_libraries(tciphr PRIVATE m)