#! /usr/bin/python3

Import("env")

env.AddPostAction(
    "$BUILD_DIR/${PROGNAME}.elf",
    env.VerboseAction(" ".join([
        "~/.espressif/tools/xtensa-esp-elf/esp-13.2.0_20230928/xtensa-esp-elf/xtensa-esp-elf/bin/objdump", "-d", "-S",
        "$BUILD_DIR/${PROGNAME}.elf", ">", "$BUILD_DIR/${PROGNAME}.lst"
    ]), "Building $BUILD_DIR/${PROGNAME}.lst")
    )
