/**
 * @file transport_i2c.c
 * @author João Matheus Nascimento Dias (joao.dias@edge.ufal.br)
 * @brief Define os drivers de comunicação I2C para o display.
 * @version 0.1
 * @date 02-06-2026
 *
 * @copyright Copyright (c) 2026, Centro de Inovação EDGE.
 *
 */

#include <zephyr/drivers/i2c.h>

#include "transport.h"

/**
 * @brief Estrutura que representa o I2C do display.
 */
static const struct i2c_dt_spec display_i2c =
    I2C_DT_SPEC_GET(DT_NODELABEL(display_i2c));

/**
 * @brief Byte de controle usado na próxima escrita, definido por
 * transport_set_mode.
 */
static uint8_t control_byte = CONFIG_DISPLAY_I2C_CTRL_CMD;

void transport_init(void) {
  while (!i2c_is_ready_dt(&display_i2c)) {
    /* Espera a comunicação I2C estar pronta. */
  }
}

void transport_set_mode(enum transport_mode mode) {
  control_byte = (mode == TRANSPORT_MODE_DATA) ? CONFIG_DISPLAY_I2C_CTRL_DATA
                                               : CONFIG_DISPLAY_I2C_CTRL_CMD;
}

int transport_write(const uint8_t *data, size_t length) {
  static uint8_t buf[1 + CONFIG_DISPLAY_I2C_MAX_PAYLOAD];

  if (length > CONFIG_DISPLAY_I2C_MAX_PAYLOAD) {
    return -1;
  }

  buf[0] = control_byte;
  memcpy(buf + 1, data, length);

  return i2c_write_dt(&display_i2c, buf, length + 1);
}