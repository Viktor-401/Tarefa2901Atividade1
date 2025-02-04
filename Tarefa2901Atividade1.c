#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"

#define BUTTON 5
#define GREEN_LED 11
#define BLUE_LED 12
#define RED_LED 13
#define SEMAFORO_VERMELHO 0
#define SEMAFORO_AMARELO 1
#define SEMAFORO_VERDE 2

bool semaforo(struct repeating_timer *timer);

int estado_semaforo = -1;

int main()
{
    stdio_init_all();
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
    gpio_init(BLUE_LED);
    gpio_set_dir(BLUE_LED, GPIO_OUT);
    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, semaforo, NULL, &timer);

    char estado_texto[30];

    while (true) {
        sleep_ms(1000);
        switch (estado_semaforo)
        {
        case SEMAFORO_VERMELHO:
            strcpy(estado_texto, "Pare!(Vermelho)");
            break;
        case SEMAFORO_AMARELO:
            strcpy(estado_texto, "Atenção!(Amarelo/Azul)");
            break;
        case SEMAFORO_VERDE:
            strcpy(estado_texto, "Siga!(Verde)");
            break;
        }
        printf("Estado atual: %s\n", estado_texto);
    }
}

bool semaforo(struct repeating_timer *timer)
{
    estado_semaforo++;
    if (estado_semaforo > 2)
    {
        estado_semaforo = 0;
    }
    
    switch (estado_semaforo)
    {
        case SEMAFORO_VERMELHO:
            gpio_put(RED_LED, 1);
            gpio_put(GREEN_LED, 0);
            gpio_put(BLUE_LED, 0);
        break;

        case SEMAFORO_AMARELO:
            gpio_put(RED_LED, 0);
            gpio_put(GREEN_LED, 0);
            gpio_put(BLUE_LED, 1);
        break;

        case SEMAFORO_VERDE:
            gpio_put(RED_LED, 0);
            gpio_put(GREEN_LED, 1);
            gpio_put(BLUE_LED, 0);
        break;
    }
    return true;
}

