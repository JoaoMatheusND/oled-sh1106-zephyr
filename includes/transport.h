/**
 * @file transport.h
 * @author João Matheus Nascimento Dias (joao.dias@edge.ufal.br)
 * @brief Interface de abstração dos protocolos usados no display.
 * @version 0.1
 * @date 02-06-2026
 *
 * @copyright Copyright (c) 2026, Centro de Inovação EDGE.
 *
 */

#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Modos de transmissão do barramento.
 */
enum transport_mode {
	TRANSPORT_MODE_CMD = 0, /**< Bytes seguintes são comandos. */
	TRANSPORT_MODE_DATA,    /**< Bytes seguintes são dados para a RAM. */
};

/**
 * @brief Inicializa o barramento de transporte do display.
 */
void transport_init(void);

/**
 * @brief Seleciona o modo de transmissão do barramento, usado para diferenciar comandos de
 * dados (via pino D/C na SPI ou byte de controle no I2C).
 *
 * @param mode Modo desejado.
 */
void transport_set_mode(enum transport_mode mode);

/**
 * @brief Escreve dados no barramento de transporte do display.
 *
 * @param data Ponteiro para os dados a serem enviados.
 * @param length Tamanho dos dados a serem enviados.
 * @return int 0 se a operação foi bem sucedida, -1 caso contrário.
 */
int transport_write(const uint8_t *data, size_t length);

#endif /* TRANSPORT_H */
