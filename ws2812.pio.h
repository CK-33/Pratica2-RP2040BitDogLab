#pragma once

// ============================================================
// ws2812.pio.h
// Header gerado para controle de LEDs endereçáveis WS2812
// Protocolo GRB, 800 kHz — compatível com RP2040 / Pico SDK
// ============================================================

#if !PICO_NO_HARDWARE
#include "hardware/pio.h"
#endif

// ------------------------------------------------------------
// Instruções do programa PIO (geradas a partir do ws2812.pio)
// ------------------------------------------------------------

#define ws2812_wrap_target 0
#define ws2812_wrap        3

static const uint16_t ws2812_program_instructions[] = {
    //     .wrap_target
    0x6221, //  0: out    x, 1            side 0 [2]
    0x1123, //  1: jmp    !x, 3           side 1 [1]
    0x1400, //  2: jmp    0               side 1 [4]
    0xa442, //  3: nop                    side 0 [4]
    //     .wrap
};

static const struct pio_program ws2812_program = {
    .instructions = ws2812_program_instructions,
    .length       = 4,
    .origin       = -1,
};

static inline pio_sm_config ws2812_program_get_default_config(uint offset) {
    pio_sm_config c = pio_get_default_sm_config();
    sm_config_set_wrap(&c, offset + ws2812_wrap_target, offset + ws2812_wrap);
    sm_config_set_sideset(&c, 1, false, false);
    return c;
}

// ------------------------------------------------------------
// Função de inicialização
// ------------------------------------------------------------

#include "hardware/clocks.h"

static inline void ws2812_program_init(
    PIO   pio,
    uint  sm,
    uint  offset,
    uint  pin,
    float freq,
    bool  rgbw
) {
    pio_gpio_init(pio, pin);
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);

    pio_sm_config c = ws2812_program_get_default_config(offset);

    sm_config_set_sideset_pins(&c, pin);
    sm_config_set_out_shift(&c, false, true, rgbw ? 32 : 24);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);

    // Calcula o divisor de clock para atingir a frequência desejada (800 kHz)
    // Cada bit ocupa 10 ciclos de clock do PIO (T1 + T2 + T3 = 2 + 5 + 3)
    float div = clock_get_hz(clk_sys) / (freq * 10);
    sm_config_set_clkdiv(&c, div);

    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_enabled(pio, sm, true);
}
