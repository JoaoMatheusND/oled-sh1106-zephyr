/**
 * @file display.h
 * @author Paulo Santos (pauloroberto.santos@edge.ufal.br)
 * @brief Interface de abstração dos drivers do display.
 * @version 0.1
 * @date 29-05-2023
 *
 * @copyright Copyright (c) 2023, Centro de Inovação EDGE.
 *
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "fonts.h"

#include <stdbool.h>

#include <zephyr/kernel.h>

/**
 * @defgroup display Display.
 * @{
 */

/**
 * @brief Largura, em pixels, do display.
 */
#define SCR_W ((uint8_t)128)

/**
 * @brief Altura, em pixels, do display.
 */
#define SCR_H ((uint8_t)64)

/**
 * @brief Enumera os comandos do display.
 */
enum display_commands {
	DISPLAY_CMD_COL_LOW = 0x02,        /**< Configura o endereço da coluna inferior. */
	DISPLAY_CMD_COL_HIGH = 0x10,       /**< Configura o endereço da coluna superior. */
	DISPLAY_DC_DC_VOLTAGE = 0x32,      /**< Configura o DC-Dc para 8v. */
	DISPLAY_CMD_START_LINE = 0x40,     /**< Configura a linha do inicio do display para
					    * 0. */
	DISPLAY_CMD_CONTRAST = 0x81,       /**< Controle de Contraste. */
	DISPLAY_CMD_SET_MUX = 0xA8,        /**< Configura a razão do multiplexador. */
	DISPLAY_CMD_SEG_NORM = 0xA0,       /**< Configura a coluna 0 como SEG0. (Coordenada x
					    * crescente.) */
	DISPLAY_CMD_SEG_INV = 0xA1,        /**< Configura a coluna 127 como SEG0. (Coordenada x
					    * decrescente.) */
	DISPLAY_CMD_DISPLAY_BY_RAM = 0xA4, /**< Configura o display para mostrar o
					    * conteúdo da RAM. */
	DISPLAY_CMD_INV_OFF = 0xA6,        /**< Configura o display para não inverter os dados
					    * da RAM. */
	DISPLAY_CMD_INV_ON = 0xA7,         /**< Configura o display para inverter a RAM. */
	DISPLAY_CMD_DC_DC_SET = 0xAD,      /**<  Configura o pump DC-DC do display. */
	DISPLAY_CMD_DISP_OFF = 0xAE,       /**< Configura o display para desligado. */
	DISPLAY_CMD_DISP_ON = 0xAF,        /**< Configura o display para ligado. */
	DISPLAY_CMD_PAGE_ADDR = 0xB0,      /**< Configura o endereço da página para 0. */
	DISPLAY_CMD_COM_NORM = 0xC0,       /**< Configura o escaneamento interno de COM0 para
					    * COM[n-1]. (Coordenada y crescente.) */
	DISPLAY_CMD_COM_INV = 0xC8,        /**< Configura o escaneamento interno de COM[n-1]
					    * para COM0.  (Coordenada y decrescente.) */
	DISPLAY_CMD_SET_OFFSET = 0xD3,     /**< Configura o offset do display. */
	DISPLAY_CMD_CLOCKDIV = 0xD5,       /**< Configura o pre-scaler do clock do display. */
	DISPLAY_CMD_SET_CHARGE = 0xD9,     /**< Configura o tempo de descarga/pré-carga do
					    * display. */
	DISPLAY_CMD_COM_HW = 0xDA,         /**< Configura o modo dos pinos COM internos. */
	DISPLAY_CMD_VCOM_DSEL = 0xDB,      /**< Configura a tensão nos pads comuns no nível de
					    * de-seleção. */
	DISPLAY_CMD_RMW_START = 0xE0,      /**< Inicia uma comunicação de dados. */
	DISPLAY_CMD_RMW_END = 0xEE, /**< Finaliza uma comunicação de dados e retorna o endereço
					    de coluna para 0. */
};

/**
 * @brief Enumera os modos de desenho.
 */
enum display_draw_mode {
	DISPLAY_PIXEL_WHITE = 0, /**< Pixel ligado sobrescreve a RAM. */
	DISPLAY_PIXEL_BLACK,     /**< Pixel ligado apaga a RAM. */
	DISPLAY_PIXEL_INVERT,    /**< Pixel ligado inverte a RAM. */
};

/**
 * @brief Inicializa o display com as configurações padrões.
 *
 * @param is_dcdc_dependent Se verdadeiro, o display ativará o DC-DC interno.
 */
void display_init(bool is_dcdc_dependent);

/**
 * @brief Desabilita o display.
 */
void display_disable(void);

/**
 * @brief Habilita o display.
 */
void display_enable(void);

/**
 * @brief Limpa o buffer VRAM do display.
 */
void display_clear(void);

/**
 * @brief Envia a vRAM para o display.
 */
void display_flush(void);

/**
 * @brief Desenha uma linha.
 *
 * @param origin_x x do ponto de origem.
 * @param origin_y y do ponto de origem.
 * @param end_x x do ponto de destino.
 * @param end_y y do ponto de destino.
 */
void display_draw_line(uint8_t origin_x, uint8_t origin_y, uint8_t end_x, uint8_t end_y);

/**
 * @brief Desenha um retângulo.
 *
 * @param top y da aresta superior.
 * @param left x da aresta esquerda.
 * @param height Altura do retângulo.
 * @param width Largura do retângulo.
 * @param filled Se verdadeiro, o retângulo será preenchido.
 */
void display_draw_rect(uint8_t top, uint8_t left, uint8_t height, uint8_t width, bool filled);

/**
 * @brief Desenha um círculo.
 *
 * @param center_x x no centro do círculo
 * @param center_y y no centro do círculo
 * @param radius Raio do círculo.
 */
void display_draw_circle(uint8_t center_x, uint8_t center_y, uint8_t radius);

/**
 * @brief Desenha um bitmap.
 *
 * @param[in] bmp Referência para o bitmap.
 * @param top x esquerdo do bitmap.
 * @param left y superior do bitmap.
 * @param width Tamanho horizontal do bitmap.
 * @param height Tamanho vertical do bitmap.
 * @param scale Fator de escala para o bitmap.
 */
void display_draw_bitmap(const uint8_t *bmp, uint8_t top, uint8_t left, uint8_t width,
			 uint8_t height, uint8_t scale);

/**
 * @brief Imprime uma string.
 *
 * @param[in] str Referência para a string.
 * @param top y superior da string.
 * @param left x esquerdo da string.
 * @param font Fonte a ser usada.
 * @param scale Fator de escala para o texto.
 * @return Posição do canto direito da string, em pixeis.
 */
uint16_t display_print(const uint8_t *str, uint8_t top, uint8_t left, enum font_sizes font,
		       uint8_t scale);

/**
 * @brief Configura o modo de desenho do display.
 *
 * @param mode Modo desejado.
 */
void display_set_draw_mode(enum display_draw_mode mode);

#if CONFIG_DISPLAY_VIRTUAL != 1
/**
 * @brief Configura o contraste da tela.
 *
 * @param amount Contraste desejado.
 */
void display_set_contrast(uint8_t amount);

/**
 * @}
 */
#endif

#endif /* DISPLAY_H */
