/**
 * @file transport_spi.c
 * @author João Matheus Nascimento Dias (joao.dias@edge.ufal.br)
 * @brief Define os drivers de comunicação SPI para o display.
 * @version 0.1
 * @date 02-06-2026
 *
 * @copyright Copyright (c) 2026, Centro de Inovação EDGE.
 *
 */

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>

#include "transport.h"

/**
 * @brief Configuração do SPI do display.
 */
#define SPI_FLAGS (SPI_OP_MODE_MASTER | SPI_WORD_SET(8) | SPI_LINES_SINGLE)

/**
 * @brief Estrutura que representa o pino D/C do display.
 */
static const struct gpio_dt_spec data_command =
    GPIO_DT_SPEC_GET(DT_NODELABEL(data_command), gpios);

/**
 * @brief Estrutura que representa o SPI do display.
 */
static const struct spi_dt_spec display_spi =
    SPI_DT_SPEC_GET(DT_NODELABEL(display_spi), SPI_FLAGS, 0);

void transport_init(void) {
  gpio_pin_configure_dt(&data_command, GPIO_OUTPUT_INACTIVE);

  while (!spi_is_ready_dt(&display_spi)) {
    /* Espera a comunicação SPI estar pronta. */
  }
}

void transport_set_mode(enum transport_mode mode) {
  gpio_pin_set_dt(&data_command, mode == TRANSPORT_MODE_DATA);
}

int transport_write(const uint8_t *data, size_t length) {
  struct spi_buf buf = {.buf = (void *)data, .len = length};
  struct spi_buf_set tx_data = {.buffers = &buf, .count = 1};

  return spi_write_dt(&display_spi, &tx_data);
}