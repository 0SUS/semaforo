#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pico/bootrom.h"

// Arquivo .pio
#include "matriz_led.pio.h"

// Número de LEDs
#define NUM_PIXELS 25

// Pino de saída matriz
#define OUT_PIN 7

//intensidade final dos leds

#define GAMMA 0.1

// Pinos
#define LED_R 13
#define LED_G 11
#define LED_B 12
#define BUTTON_A 5
#define BUTTON_B 6

#define LED_RGB_BLINK_HZ 5  // Frequência do LED RGB

// Variáveis globais
volatile int8_t current_number = 0; // Número atual a ser exibido
volatile bool button_a_pressed = false;
volatile bool button_b_pressed = false;


// Estrutura para armazenar dados do numero
typedef struct {
    double frames[10][NUM_PIXELS];
    int num_frames;
    double r, g, b;
    int fps; 
} Animacao;

// Função para criar cor RGB
uint32_t matrix_rgb(double b, double r, double g) {
    unsigned char R = r * 255;
    unsigned char G = g * 255;
    unsigned char B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// Inicializa o PIO para a matriz de LEDs
void init_matriz_led(PIO pio, uint *offset, uint *sm) {
    *offset = pio_add_program(pio, &matriz_led_program);
    if (*offset < 0) {
        printf(" Erro ao carregar programa.\n");
        return;
    }

    *sm = pio_claim_unused_sm(pio, true);
    if (*sm < 0) {
        printf("Erro no estado de maquina.\n");
        return;
    }

    matriz_led_program_init(pio, *sm, *offset, OUT_PIN);
}
// looping que exibe o numero na matriz de led
void executar_animacao(PIO pio, uint sm, Animacao *anim) {
    
    for (int frame = 0; frame < anim->num_frames; frame++) {
        for (int i = 0; i < NUM_PIXELS; i++) {
            double intensidade = anim->frames[frame][i];
            uint32_t valor_led = matrix_rgb(anim->b * intensidade * GAMMA, anim->r * intensidade, anim->g * intensidade * GAMMA);
            pio_sm_put_blocking(pio, sm, valor_led);
        }

        
    }
}

// Configuração de animações
Animacao animacao_0 = {
    .frames = {
        {
        1.0, 1.0, 1.0, 1.0, 1.0, 
        1.0, 0.0, 0.0, 0.0, 1.0, 
        1.0, 0.0, 0.0, 0.0, 1.0, 
        1.0, 0.0, 0.0, 0.0, 1.0, 
        1.0, 1.0, 1.0, 1.0, 1.0
        }
        
    },
    .num_frames = 1,
    .r = 1.0,
    .g = 0.0,
    .b = 0.0,
    .fps = 1
};

Animacao animacao_1 = {
    .frames = {
        {
        1.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 1.0, 
        1.0, 0.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 0.0, 1.0, 
        1.0, 0.0, 0.0, 0.0, 0.0
        }
        
    },
    .num_frames = 1,
    .r = 1.0,
    .g = 0.005,
    .b = 0.05,
    .fps = 1
};

Animacao animacao_2 = {
    .frames = {
        {
        0.0, 1.0, 1.0, 1.0, 0.0, 
        0.0, 1.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 1.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 1.0, 0.0, 
        0.0, 1.0, 1.0, 1.0, 0.0
        }
        
    },
    .num_frames = 1,
    .r = 1.0,
    .g = 0.01,
    .b = 0.1,
    .fps = 1
};

Animacao animacao_3 = {
    .frames = {
        {
        0.0, 1.0, 1.0, 1.0, 0.0, 
        0.0, 0.0, 0.0, 1.0, 0.0, 
        0.0, 1.0, 1.0, 1.0, 0.0, 
        0.0, 0.0, 0.0, 1.0, 0.0, 
        0.0, 1.0, 1.0, 1.0, 0.0
        }
        
    },
    .num_frames = 1,
    .r = 1.0,
    .g = 0.02,
    .b = 0.15,
    .fps = 1
};

Animacao animacao_4 = {
    .frames = {
        {
        0.0, 1.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 1.0, 0.0, 
        0.0, 1.0, 1.0, 1.0, 0.0, 
        0.0, 1.0, 0.0, 1.0, 0.0, 
        0.0, 1.0, 0.0, 1.0, 0.0
        }
        
    },
    .num_frames = 1,
    .r = 1.0,
    .g = 0.05,
    .b = 0.2,
    .fps = 1
};

Animacao animacao_5 = {
    .frames = {
        {
        0.0, 1.0, 1.0, 1.0, 0.0, 
        0.0, 0.0, 0.0, 1.0, 0.0, 
        0.0, 1.0, 1.0, 1.0, 0.0, 
        0.0, 1.0, 0.0, 0.0, 0.0, 
        0.0, 1.0, 1.0, 1.0, 0.0
        }
        
    },
    .num_frames = 1,
    .r = 1.0,
    .g = 0.09,
    .b = 0.25,
    .fps = 1
};

Animacao animacao_6 = {
    .frames = {
        {
        0.0, 1.0, 1.0, 1.0, 0.0, 
        0.0, 1.0, 0.0, 1.0, 0.0, 
        0.0, 1.0, 1.0, 1.0, 0.0, 
        0.0, 1.0, 0.0, 0.0, 0.0, 
        0.0, 1.0, 1.0, 1.0, 0.0
        }
        
    },
    .num_frames = 1,
    .r = 1.0,
    .g = 0.1,
    .b = 0.3,
    .fps = 1
};

Animacao animacao_7 = {
    .frames = {
        {
        0.0, 1.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 1.0, 0.0, 
        0.0, 1.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 1.0, 0.0, 
        0.0, 1.0, 1.0, 1.0, 0.0
        }
        
    },
    .num_frames = 1,
    .r = 1.0,
    .g = 0.14,
    .b = 0.35,
    .fps = 1
};

Animacao animacao_8 = {
    .frames = {
        {
        0.0, 1.0, 1.0, 1.0, 0.0, 
        0.0, 1.0, 0.0, 1.0, 0.0, 
        0.0, 1.0, 1.0, 1.0, 0.0, 
        0.0, 1.0, 0.0, 1.0, 0.0, 
        0.0, 1.0, 1.0, 1.0, 0.0, 
        }
        
    },
    .num_frames = 1,
    .r = 1.0,
    .g = 0.16,
    .b = 0.4,
    .fps = 1
};

Animacao animacao_9 = {
    .frames = {
        {
        0.0, 1.0, 0.0, 0.0, 0.0, 
        0.0, 0.0, 0.0, 1.0, 0.0, 
        0.0, 1.0, 1.0, 1.0, 0.0, 
        0.0, 1.0, 0.0, 1.0, 0.0, 
        0.0, 1.0, 1.0, 1.0, 0.0, 
        }
        
    },
    .num_frames = 1,
    .r = 1.0,
    .g = 0.2,
    .b = 0.5,
    .fps = 1
};

// Pisca o LED RGB na cor vermelha
void blink_led_rgb() {
    static absolute_time_t last_blink_time = 0;
    static bool led_on = false;

    absolute_time_t now = get_absolute_time();
    if (absolute_time_diff_us(last_blink_time, now) >= (1000000 / LED_RGB_BLINK_HZ)) {
        last_blink_time = now;
        led_on = !led_on;
        gpio_put(LED_R, led_on);
    }
}

// Rotina executada na interrupção
void debounce_handler(uint gpio, uint32_t events) {
    static absolute_time_t last_time_a = 0;
    static absolute_time_t last_time_b = 0;

    if (gpio == BUTTON_A) {
        absolute_time_t now = get_absolute_time();
        if (absolute_time_diff_us(last_time_a, now) > 200000) { 
            last_time_a = now;
            button_a_pressed = true;
        }
    } else if (gpio == BUTTON_B) {
        absolute_time_t now = get_absolute_time();
        if (absolute_time_diff_us(last_time_b, now) > 200000) {
            last_time_b = now;
            button_b_pressed = true;
        }
    }
}

// Configuração dos GPIOs e interrupções
void configure_gpio() {
    // Configuração do LED RGB
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);

    // Configuração dos botões com resistores de pull-up
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &debounce_handler);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &debounce_handler);
}

//relaciona o numero global a o qu e é exibido na matriz de leds
void display_number(int8_t num, PIO pio, uint sm){
    switch(num){
        case 0: executar_animacao(pio, sm, &animacao_0);break;
        case 1: executar_animacao(pio, sm, &animacao_1);break;
        case 2: executar_animacao(pio, sm, &animacao_2);break;
        case 3: executar_animacao(pio, sm, &animacao_3);break;
        case 4: executar_animacao(pio, sm, &animacao_4);break;
        case 5: executar_animacao(pio, sm, &animacao_5);break;
        case 6: executar_animacao(pio, sm, &animacao_6);break;
        case 7: executar_animacao(pio, sm, &animacao_7);break;
        case 8: executar_animacao(pio, sm, &animacao_8);break;
        case 9: executar_animacao(pio, sm, &animacao_9);break;
    }


}



int main() {
    PIO pio = pio0;
    uint offset, sm;

    // Configurações iniciais
    stdio_init_all();
    configure_gpio();
    init_matriz_led(pio, &offset, &sm);

    while (true) {

        blink_led_rgb();

        if (button_a_pressed) {
            button_a_pressed = false;
            current_number = (current_number + 1) % 10; // Incrementa o número (0-9)
            display_number(current_number,pio,sm);
        }

        if (button_b_pressed) {
            button_b_pressed = false;
            current_number = (current_number - 1 + 10) % 10; // Decrementa o número (0-9)
            display_number(current_number,pio,sm);
        }

        }
    

    return 0;
}