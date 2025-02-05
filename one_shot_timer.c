#include <stdio.h>
#include "pico/stdlib.h" // Biblioteca padrão Raspberry Pi Pico W
#include "hardware/gpio.h"
#include "hardware/timer.h"
// Definição
#define LED_RED 13 // GPIO para os LED RGB
#define LED_BLUE 12
#define LED_GREEN 11
#define PIN_BUTTON 5 // GPIO para o botão A
// Variables
bool interruption = false; //Variável para controlar o estado do alarme
struct repeating_timer timer; // Variável para armazenar o timer repetitivo
volatile int leds_para_desligar = 0; // Variável determinar qual LED será apagado


// chamada de funções
void turn_on_leds(); // Liga os LEDs
void inicialization_pins(); // inicializa os pinos em uso
// Protótipo da função de callback para o temporizador repetitivo
bool turn_led_off_callback(struct repeating_timer *t);
// Protótipo da função de callback para o alarme inicial
int64_t turn_led_on_callback(alarm_id_t id, void *user_data);

int main()
{
    // incialização
    stdio_init_all();
    inicialization_pins();

    while (true) {
        // verificação se o botão foi pressionado
        if (gpio_get(PIN_BUTTON) == 0 && !interruption) {
            sleep_ms(50); // leve delay para debounce;
            //realiza nova verificação após debounde
            if(gpio_get(PIN_BUTTON) == 0) {
                printf("ligou os leds, alterou o interrup e entrou no alarme\n");
                turn_on_leds();
                interruption = true;
                // Configura o alarme para desligar os LEDs após 3 segundos
                add_alarm_in_ms(3000, turn_led_on_callback, NULL, false);
                printf("já pode apagar os leds\n");
                while (!gpio_get(PIN_BUTTON)){
                    tight_loop_contents();
                }
            }
            tight_loop_contents();
        }
    }

    return 1;
}

// Função de inicialização das GPIOs
void inicialization_pins() {
    // inicializa as GPIOs
    gpio_init(LED_RED);
    gpio_init(LED_BLUE);
    gpio_init(LED_GREEN);
    gpio_init(PIN_BUTTON);
    // define o sentido paras as GPIOs
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(PIN_BUTTON, GPIO_IN);
    // Habilita o resitor de pull-up para o pino do botão
    gpio_pull_up(PIN_BUTTON);
}

// Função para ligar todos os LEDs
void turn_on_leds() {
    gpio_put(LED_RED, true);
    gpio_put(LED_BLUE, true);
    gpio_put(LED_GREEN, true);
}

// Função para desligar um LED específico
void turn_off_led(int led_number) {
    if (led_number == 0) {
        gpio_put(LED_BLUE, false);
    } else if (led_number == 1) {
        gpio_put(LED_RED, false);
    } else if (led_number == 2) {
        gpio_put(LED_GREEN, false);
    }
}

// Função de callback do alarme inicial
int64_t turn_led_on_callback(alarm_id_t id, void *user_data) {
    printf("Alarme disparado, iniciando temporizador para desligar os LEDs.\n");
    // Inicializa o LED a ser desligado
    leds_para_desligar = 0;
     // Inicia o temporizador repetitivo para desligar os LEDs sequencialmente
    add_repeating_timer_ms(1000, turn_led_off_callback, NULL, &timer);

    return 0; // Não reagenda o alarme
}

// Função de callback do temporizador repetitivo
bool turn_led_off_callback(struct repeating_timer *t) {
   if (leds_para_desligar < 3) {
        // Desliga o LED correspondente
        turn_off_led(leds_para_desligar);
        printf("LED %d desligado.\n", leds_para_desligar + 1);
         // Avança para o próximo LED
        leds_para_desligar+= 1;
        return true;
    } else {
        // Cancela o timer se todos os LEDs foram desligados
        cancel_repeating_timer(&timer);
        interruption = false;
        printf("Todos os LEDs desligados. Temporizador cancelado.\n");
       return false;
    }
}