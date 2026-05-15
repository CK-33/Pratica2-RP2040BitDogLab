#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

// ==========================
// DEFINIÇÕES
// ==========================

#define WS2812_PIN 7
#define NUM_LEDS 25

#define BUTTON_A 5
#define BUTTON_B 6

#define IS_RGBW false

PIO pio = pio0;
int sm = 0;

// ==========================
// MATRIZ
// ==========================

uint32_t leds[NUM_LEDS];

// ==========================
// FUNÇÕES WS2812
// ==========================

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
        ((uint32_t)(r) << 8) |
        ((uint32_t)(g) << 16) |
        (uint32_t)(b);
}

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio, sm, pixel_grb << 8u);
}

void show_matrix() {
    for (int i = 0; i < NUM_LEDS; i++) {
        put_pixel(leds[i]);
    }
}

void clear_matrix() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = urgb_u32(0,0,0);
    }
}

// ==========================
// DESENHO
// ==========================

void set_led(int index, uint8_t r, uint8_t g, uint8_t b) {
    leds[index] = urgb_u32(r,g,b);
}

// ==========================
// ANIMAÇÃO 1
// Vermelho andando
// ==========================

void animation_red() {

    for(int frame = 0; frame < 5; frame++) {

        clear_matrix();

        for(int i = 0; i < 5; i++) {
            int pos = frame + (i * 5);

            if(pos < NUM_LEDS) {
                set_led(pos, 80, 0, 0);
            }
        }

        show_matrix();
        sleep_ms(200);
    }

    clear_matrix();
    show_matrix();
}

// ==========================
// ANIMAÇÃO 2
// Expansão azul
// ==========================

void animation_blue() {

    int frames[5][25] = {

        // Frame 1
        {
            0,0,0,0,0,
            0,0,0,0,0,
            0,0,1,0,0,
            0,0,0,0,0,
            0,0,0,0,0
        },

        // Frame 2
        {
            0,0,0,0,0,
            0,1,1,1,0,
            0,1,1,1,0,
            0,1,1,1,0,
            0,0,0,0,0
        },

        // Frame 3
        {
            0,1,1,1,0,
            1,1,1,1,1,
            1,1,1,1,1,
            1,1,1,1,1,
            0,1,1,1,0
        },

        // Frame 4
        {
            1,1,1,1,1,
            1,0,0,0,1,
            1,0,0,0,1,
            1,0,0,0,1,
            1,1,1,1,1
        },

        // Frame 5
        {
            1,1,1,1,1,
            1,1,1,1,1,
            1,1,1,1,1,
            1,1,1,1,1,
            1,1,1,1,1
        }
    };

    for(int f = 0; f < 5; f++) {

        clear_matrix();

        for(int i = 0; i < 25; i++) {

            if(frames[f][i]) {
                set_led(i, 0, 0, 80);
            }
        }

        show_matrix();
        sleep_ms(180);
    }

    clear_matrix();
    show_matrix();
}

// ==========================
// MAIN
// ==========================

int main() {

    stdio_init_all();

    // Botões
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    // WS2812
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(
        pio,
        sm,
        offset,
        WS2812_PIN,
        800000,
        IS_RGBW
    );

    absolute_time_t last_press_a = 0;
    absolute_time_t last_press_b = 0;

    while (true) {

        // ==========================
        // BOTÃO A
        // ==========================

        if(!gpio_get(BUTTON_A)) {

            absolute_time_t now = get_absolute_time();

            // Debounce 250 ms
            if(
                absolute_time_diff_us(last_press_a, now)
                > 250000
            ) {

                animation_red();

                last_press_a = now;
            }
        }

        // ==========================
        // BOTÃO B
        // ==========================

        if(!gpio_get(BUTTON_B)) {

            absolute_time_t now = get_absolute_time();

            // Debounce 250 ms
            if(
                absolute_time_diff_us(last_press_b, now)
                > 250000
            ) {

                animation_blue();

                last_press_b = now;
            }
        }

        sleep_ms(10);
    }
}
