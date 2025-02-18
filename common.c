#include "common.h"

void putchar(char c);

void *memset(void *buffer, char init_value, size_t size) {
  uint8_t *p = (uint8_t *)buffer;
  while (size--) {
    *p++ = init_value;
  }

  return buffer;
}

void *memcpy(void *destination, const void *source, size_t size) {
  uint8_t *d = (uint8_t *)destination;
  const uint8_t *s = (const uint8_t *)source;
  while (size--) {
    *d++ = *s++;
  }
  return destination;
}

// unhandled case: size(source) > size(destination), undefined behavour
void *strcpy(char *destination, const char *source) {
  char *d = destination;
  while (*source) {
    *d++ = *source++;
  }
  *d = '\0';
  return destination;
}

// s1 == s2 -> 0
// s1 > s2 -> positive
// s1 < s2 -> negative
int strcmp(const char *s1, const char *s2) {
  while (*s1 && *s2) {
    if (*s1 != *s2) {
      break;
    }
    s1++;
    s2++;
  }
  return *(unsigned char *)s1 - *(unsigned char *)s2; // casting to uchar*, see posix specs
}

void printf(const char *fmt, ...) {
  va_list vargs;
  va_start(vargs, fmt);
  while (*fmt) {
    if (*fmt == '%') {
      fmt++;
      switch (*fmt) {
      case '\0':
        putchar('%');
        goto end;
      case '%':
        putchar('%');
        break;
      case 's': {
        const char *s = va_arg(vargs, const char *);
        while (*s) {
          putchar(*s);
          s++;
        }
        break;
      }
      case 'd': {
        int value = va_arg(vargs, int);
        unsigned magnitude = value;
        if (value < 0) {
          putchar('-');
          magnitude = -magnitude;
        }

        unsigned divisor = 1;
        while (magnitude / divisor > 9)
          divisor *= 10;

        while (divisor > 0) {
          putchar('0' + magnitude / divisor);
          magnitude %= divisor;
          divisor /= 10;
        }

        break;
      }
      case 'x': {
        unsigned value = va_arg(vargs, unsigned);
        for (unsigned i = 7; i >= 0; i--) {
          unsigned nibble = (value >> (i * 4)) & 0xf;
          putchar("0123456789abcdef"[nibble]);
        }
      }
      }
    } else {
      putchar(*fmt);
    }

    fmt++;
  }

end:
  va_end(vargs);
}
