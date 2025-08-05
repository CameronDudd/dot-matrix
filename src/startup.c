#include <stdint.h>

extern uint32_t _stack;
extern uint32_t _data_loadaddr, _data, _edata;
extern uint32_t _bss, _ebss;

void reset_handler(void);
void default_handler(void);

__attribute__((section(".vectors"))) void (*const vector_table[])(void) = {
    (void (*)(void))(&_stack),
    reset_handler,
    default_handler,
    default_handler,
};

void reset_handler(void) {
  uint32_t *src = &_data_loadaddr;
  uint32_t *dst = &_data;
  while (dst < &_edata) {
    *dst++ = *src++;
  }

  dst = &_bss;
  while (dst < &_ebss) {
    *dst++ = 0;
  }

  extern int main(void);
  main();

  while (1) {
  }
}

void default_handler(void) {
  while (1) {
  }
}
