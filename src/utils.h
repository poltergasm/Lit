#ifndef _UTILS_H_
#define _UTILS_H_

void print(const char *fmt, ...) {
	char buf[sizeof(fmt)+3];
	va_list args;
	va_start(args, fmt);
	strcpy(buf, fmt);
	strcat(buf, "\n");
	vprintf(buf, args);
	va_end(args);
}

#endif