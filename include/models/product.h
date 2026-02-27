#ifndef MODELS_PRODUCT_H
#define MODELS_PRODUCT_H

#include <stddef.h>

#define MAX_NAME_LENGTH 64

typedef struct {
    int code;
    char name[MAX_NAME_LENGTH];
    double price;
    int sold_quantity;
} Product;

#endif
