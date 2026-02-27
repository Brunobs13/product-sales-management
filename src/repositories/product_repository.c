#include "repositories/product_repository.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void write_error(char *error, size_t error_size, const char *message) {
    if (error != NULL && error_size > 0) {
        snprintf(error, error_size, "%s", message);
    }
}

static void trim(char *text) {
    size_t len = strlen(text);
    while (len > 0 && (text[len - 1] == '\n' || text[len - 1] == '\r' || isspace((unsigned char)text[len - 1]))) {
        text[len - 1] = '\0';
        len--;
    }

    size_t start = 0;
    while (text[start] != '\0' && isspace((unsigned char)text[start])) {
        start++;
    }

    if (start > 0) {
        memmove(text, text + start, strlen(text + start) + 1);
    }
}

void catalog_init(ProductCatalog *catalog) {
    if (catalog == NULL) {
        return;
    }

    catalog->count = 0;
}

Product *catalog_find_by_code(ProductCatalog *catalog, int code) {
    if (catalog == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < catalog->count; ++i) {
        if (catalog->items[i].code == code) {
            return &catalog->items[i];
        }
    }

    return NULL;
}

const Product *catalog_find_by_code_const(const ProductCatalog *catalog, int code) {
    if (catalog == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < catalog->count; ++i) {
        if (catalog->items[i].code == code) {
            return &catalog->items[i];
        }
    }

    return NULL;
}

int catalog_add(ProductCatalog *catalog, Product product, char *error, size_t error_size) {
    if (catalog == NULL) {
        write_error(error, error_size, "Catalog is NULL.");
        return 0;
    }

    if (catalog->count >= MAX_PRODUCTS) {
        write_error(error, error_size, "Catalog capacity reached.");
        return 0;
    }

    if (product.code <= 0 || product.price < 0 || strlen(product.name) == 0) {
        write_error(error, error_size, "Invalid product payload.");
        return 0;
    }

    if (catalog_find_by_code(catalog, product.code) != NULL) {
        write_error(error, error_size, "Product code already exists.");
        return 0;
    }

    product.sold_quantity = 0;
    catalog->items[catalog->count++] = product;
    return 1;
}

int catalog_remove(ProductCatalog *catalog, int code, char *error, size_t error_size) {
    if (catalog == NULL) {
        write_error(error, error_size, "Catalog is NULL.");
        return 0;
    }

    for (size_t i = 0; i < catalog->count; ++i) {
        if (catalog->items[i].code == code) {
            for (size_t j = i; j + 1 < catalog->count; ++j) {
                catalog->items[j] = catalog->items[j + 1];
            }
            catalog->count--;
            return 1;
        }
    }

    write_error(error, error_size, "Product not found.");
    return 0;
}

int catalog_update(ProductCatalog *catalog, int code, const char *new_name, double new_price, char *error, size_t error_size) {
    Product *product = catalog_find_by_code(catalog, code);
    if (product == NULL) {
        write_error(error, error_size, "Product not found.");
        return 0;
    }

    if (new_price < 0) {
        write_error(error, error_size, "Price cannot be negative.");
        return 0;
    }

    if (new_name != NULL && strlen(new_name) > 0) {
        snprintf(product->name, sizeof(product->name), "%s", new_name);
    }

    product->price = new_price;
    return 1;
}

int catalog_apply_sale(ProductCatalog *catalog, int product_code, int quantity, char *error, size_t error_size) {
    Product *product = catalog_find_by_code(catalog, product_code);
    if (product == NULL) {
        write_error(error, error_size, "Sale references unknown product.");
        return 0;
    }

    if (quantity <= 0) {
        write_error(error, error_size, "Quantity must be positive.");
        return 0;
    }

    product->sold_quantity += quantity;
    return 1;
}

int catalog_load_from_csv(ProductCatalog *catalog, const char *path, char *error, size_t error_size) {
    if (catalog == NULL || path == NULL) {
        write_error(error, error_size, "Invalid catalog load arguments.");
        return 0;
    }

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        write_error(error, error_size, "Products CSV not found. Starting with an empty catalog.");
        return 0;
    }

    catalog_init(catalog);
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        Product product;
        char *code_text;
        char *name_text;
        char *price_text;

        trim(line);
        if (strlen(line) == 0) {
            continue;
        }

        code_text = strtok(line, ",");
        name_text = strtok(NULL, ",");
        price_text = strtok(NULL, ",");

        if (code_text == NULL || name_text == NULL || price_text == NULL) {
            continue;
        }

        trim(code_text);
        trim(name_text);
        trim(price_text);

        product.code = atoi(code_text);
        snprintf(product.name, sizeof(product.name), "%s", name_text);
        product.price = atof(price_text);
        product.sold_quantity = 0;

        if (product.code <= 0 || product.price < 0 || strlen(product.name) == 0) {
            continue;
        }

        if (catalog->count >= MAX_PRODUCTS) {
            write_error(error, error_size, "Products file exceeds max capacity.");
            fclose(file);
            return 0;
        }

        if (catalog_find_by_code(catalog, product.code) == NULL) {
            catalog->items[catalog->count++] = product;
        }
    }

    fclose(file);
    return 1;
}

int catalog_save_to_csv(const ProductCatalog *catalog, const char *path, char *error, size_t error_size) {
    if (catalog == NULL || path == NULL) {
        write_error(error, error_size, "Invalid catalog save arguments.");
        return 0;
    }

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        write_error(error, error_size, "Unable to open products CSV for writing.");
        return 0;
    }

    for (size_t i = 0; i < catalog->count; ++i) {
        fprintf(file, "%d,%s,%.2f\n", catalog->items[i].code, catalog->items[i].name, catalog->items[i].price);
    }

    fclose(file);
    return 1;
}
