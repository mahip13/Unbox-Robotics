#include <stdint.h>

#define F_CPU 16000000UL

typedef struct {
    volatile uint8_t UCSRA;  // Status
    volatile uint8_t UCSRB;  // Control B (Enable)
    volatile uint8_t UCSRC;  // (Frame)
    uint8_t RESERVED;
    volatile uint8_t UBRRL;  // Baud Low
    volatile uint8_t UBRRH;  // Baud High
    volatile uint8_t UDR;    // Data Buffer
} USART_TypeDef;

#define USART_0 ((USART_TypeDef*)0xC0)

#define RXC0   7  // Receive Complete
#define UDRE0  5  // Data Register Empty
#define TXEN0  3  // Transmitter Enable
#define RXEN0  4  // Receiver Enable
#define UCSZ00 1  // Character Size bit 0
#define UCSZ01 2  // Character Size bit 1

void USART_Init(uint32_t baud);
void USART_Transmit(unsigned char data);
void USART_Print(const char* str);
uint8_t USART_Receive(void);

void setup() {
    USART_Init(9600);
}

void loop() {
    USART_Print("Hello from UART\r\n");
    delay(1000);
}

void USART_Init(uint32_t baud) {
  
    uint16_t ubrr_value = (F_CPU / (16 * baud)) - 1;
    
    // Set Baud Rate
    USART_0->UBRRH = (uint8_t)(ubrr_value >> 8);
    USART_0->UBRRL = (uint8_t)ubrr_value;
    
    // Enable Transmitter and Receiver
    USART_0->UCSRB = (1 << TXEN0) | (1 << RXEN0);
    
    // 8N1
    USART_0->UCSRC = (1 << UCSZ01) | (1 << UCSZ00);
}

void USART_Transmit(unsigned char data) {
    while (!(USART_0->UCSRA & (1 << UDRE0)));
    USART_0->UDR = data;
}

void USART_Print(const char* str) {
    while (*str) {
        USART_Transmit(*str++);
    }
}

uint8_t USART_Receive(void) {
    while (!(USART_0->UCSRA & (1 << RXC0)));
    return USART_0->UDR;
}
