#ifndef REPOSITORIES_SALE_REPOSITORY_H
#define REPOSITORIES_SALE_REPOSITORY_H

#include <stddef.h>

#include "core/app_context.h"

void sales_init(SalesRegistry *sales);
int sales_load_from_csv(SalesRegistry *sales, ProductCatalog *catalog, const char *path, char *error, size_t error_size);
int sales_save_to_csv(const SalesRegistry *sales, const char *path, char *error, size_t error_size);
int sales_add(SalesRegistry *sales, ProductCatalog *catalog, Sale sale, char *error, size_t error_size);

#endif
