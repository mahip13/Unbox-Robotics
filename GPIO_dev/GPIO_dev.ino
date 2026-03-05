#include <stdint.h>

typedef struct {
    volatile uint8_t PIN;
    volatile uint8_t DDR;
    volatile uint8_t PORT;
} GPIO_TypeDef;

#define GPIO_B ((GPIO_TypeDef*)0x23)
#define GPIO_C ((GPIO_TypeDef*)0x26)
#define GPIO_D ((GPIO_TypeDef*)0x29)

void gpio_set_mode(GPIO_TypeDef* port, uint8_t pin, uint8_t is_output);
void gpio_write(GPIO_TypeDef* port, uint8_t pin, uint8_t state);
uint8_t gpio_input_read(GPIO_TypeDef* port, uint8_t pin);
void gpio_toggle(GPIO_TypeDef* port, uint8_t pin);

void setup() {
  gpio_set_mode(GPIO_B, 5, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  gpio_toggle(GPIO_B, 5);
  delay(500);
}

void gpio_set_mode(GPIO_TypeDef* port, uint8_t pin, uint8_t is_output) {
  if (is_output)
    port->DDR |= (1 << pin);  // Set bit for Output
  else 
    port->DDR &= ~(1 << pin); // Clear bit for Input
}

void gpio_write(GPIO_TypeDef* port, uint8_t pin, uint8_t state) {
  if (state)
    port->PORT |= (1 << pin);  // High
  else
    port->PORT &= ~(1 << pin); // Low
}

uint8_t gpio_input_read(GPIO_TypeDef* port, uint8_t pin){
  if((port->PIN) & (1 << pin))
    return HIGH;
  else
    return LOW;
}

void gpio_toggle(GPIO_TypeDef* port, uint8_t pin) {
  port->PORT ^= (1 << pin);
}