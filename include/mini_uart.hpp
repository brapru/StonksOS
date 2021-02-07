#pragma once

void uart_init(void);
char uart_recv(void);
void uart_send(char c);
void uart_send_string(const char* str);
void uart_hex(unsigned int d);
