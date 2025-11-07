# Copyright (c) 2023, Centro de Inovação Edge.
# SPDX-License-Identifier: BSD-3-Clause

if (CONFIG_OLED_DISPLAY)
    zephyr_library()
    zephyr_library_sources(src/display.c)
    zephyr_include_directories(includes)
endif ()
