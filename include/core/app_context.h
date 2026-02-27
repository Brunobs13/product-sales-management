#ifndef CORE_APP_CONTEXT_H
#define CORE_APP_CONTEXT_H

#include <stddef.h>

#include "models/product.h"
#include "models/sale.h"

#define MAX_PRODUCTS 1000
#define MAX_SALES 20000
#define MAX_ERROR_LENGTH 256

typedef struct {
    Product items[MAX_PRODUCTS];
    size_t count;
} ProductCatalog;

typedef struct {
    Sale items[MAX_SALES];
    size_t count;
} SalesRegistry;

#endif
