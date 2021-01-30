#include "exlog.h"

void verbose(const char *tag, const char *fmt, ...) {
    print(ANDROID_LOG_VERBOSE, tag, fmt);
}

void debug(const char *tag, const char *fmt, ...) {
    print(ANDROID_LOG_DEBUG, tag, fmt);
}

void info(const char *tag, const char *fmt, ...) {
    print(ANDROID_LOG_INFO, tag, fmt);
}

void warn(const char *tag, const char *fmt, ...) {
    print(ANDROID_LOG_WARN, tag, fmt);
}

void error(const char *tag, const char *fmt, ...) {
    print(ANDROID_LOG_ERROR, tag, fmt);
}

#define DEFAULT_BUFF_SIZE 64

char *buf = nullptr;
unsigned int bufSize = 64;
int position = 0;

static void putchar(char c) {
    if (buf == nullptr) {
        buf = (char *) malloc(bufSize * sizeof(char));
        bufSize = DEFAULT_BUFF_SIZE;
        position = 0;
    } else if (position >= bufSize) {
        bufSize = (bufSize * 2) - (bufSize / 2);
        char *tmp = (char *) malloc(bufSize * sizeof(char));
        memcpy(tmp, buf, position);
        free(buf);
        buf = tmp;
    }
    buf[position++] = c;
}

static void print(int prio, const char *tag, const char *fmt, ...) {
#if LOG_ENABLED
    va_list ap = nullptr;
    va_start(ap, fmt);
    int count = 0;
    for (int i = 0; *(fmt + i) != '\0'; ++i) {
        if (*(fmt + i) == '%') {
            char c = *(fmt + i + 1);
            if (c == 'd' || c == 'f' || c == 'c' || c == 's') {
                switch (c) {
                    case 'd':
                        putchar((char) va_arg(ap, int));
                        break;
                    case 'f':
                        break;
                    case 'c':
                        putchar(va_arg(ap, char));
                        break;
                    case 's':
                        break;
                }
                ++i;
            }
        }
    }

    va_end(ap);
    __android_log_print(prio, tag, fmt, ap);
#endif
}