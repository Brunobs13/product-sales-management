#ifndef REPOSITORIES_PRODUCT_REPOSITORY_H
#define REPOSITORIES_PRODUCT_REPOSITORY_H

#include <stddef.h>

#include "core/app_context.h"

void catalog_init(ProductCatalog *catalog);
int catalog_load_from_csv(ProductCatalog *catalog, const char *path, char *error, size_t error_size);
int catalog_save_to_csv(const ProductCatalog *catalog, const char *path, char *error, size_t error_size);
Product *catalog_find_by_code(ProductCatalog *catalog, int code);
const Product *catalog_find_by_code_const(const ProductCatalog *catalog, int code);
int catalog_add(ProductCatalog *catalog, Product product, char *error, size_t error_size);
int catalog_remove(ProductCatalog *catalog, int code, char *error, size_t error_size);
int catalog_update(ProductCatalog *catalog, int code, const char *new_name, double new_price, char *error, size_t error_size);
int catalog_apply_sale(ProductCatalog *catalog, int product_code, int quantity, char *error, size_t error_size);

#endif
