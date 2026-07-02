# Copyright (c) 2023, Centro de Inovação Edge.
# SPDX-License-Identifier: BSD-3-Clause

zephyr_library()
zephyr_include_directories(includes)
zephyr_library_sources(src/display.c)

zephyr_library_sources_ifdef(CONFIG_OLED_DISPLAY_SPI src/transport_spi.c)   
zephyr_library_sources_ifdef(CONFIG_OLED_DISPLAY_I2C src/transport_i2c.c)