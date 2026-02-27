#ifndef MODELS_SALE_H
#define MODELS_SALE_H

#define MAX_DATE_LENGTH 11

typedef struct {
    int product_code;
    int quantity;
    char date[MAX_DATE_LENGTH];
} Sale;

#endif
