#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

#define BUTTON_PIN 5
#define LED_BLUE 11
#define LED_RED 12
#define LED_GREEN 13

volatile bool processando = false;  // Variável de controle para evitar múltiplas execuções

// Callback do temporizador para controle dos LEDs
int64_t controle_leds(alarm_id_t id, void *user_data) {
    static int etapa = 0;

    switch (etapa) {
        case 0:  // Liga todos os LEDs
            gpio_put(LED_BLUE, 1);
            gpio_put(LED_RED, 1);
            gpio_put(LED_GREEN, 1);
            break;
        case 1:  // Apaga o LED azul
            gpio_put(LED_BLUE, 0);
            break;
        case 2:  // Apaga o LED vermelho
            gpio_put(LED_RED, 0);
            break;
        case 3:  // Apaga o LED verde e libera o botão
            gpio_put(LED_GREEN, 0);
            processando = false;  // Permite nova execução
            etapa = 0;  // Reseta a sequência

            // Reativa a interrupção do botão após a conclusão da sequência
            gpio_set_irq_enabled(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true);
            return 0; // Finaliza o temporizador
    }

    etapa++; // Avança para a próxima etapa
    add_alarm_in_ms(3000, controle_leds, NULL, false); // Próxima chamada após 3s
    return 0;
}

// Interrupção do botão
void botao_irq(uint gpio, uint32_t events) {
    if (!processando) {
        processando = true;

        // Desativa a interrupção do botão para evitar novas execuções antes do fim do ciclo
        gpio_set_irq_enabled(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, false);

        controle_leds(0, NULL); // Inicia a sequência de LEDs
    }
}



int main()
{
    stdio_init_all();

    // Set up our UART
    uart_init(UART_ID, BAUD_RATE);
    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    
    // Use some the various UART functions to send out data
    // In a default system, printf will also output via the default UART
    
    // Send out a string, with CR/LF conversions
    uart_puts(UART_ID, " Hello, UART!\n");
    
    // Configuração dos LEDs
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Configuração do botão
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &botao_irq);

    while (true) {
        sleep_ms(1000);
        printf("Aguardando botão...\n");
    }
}
