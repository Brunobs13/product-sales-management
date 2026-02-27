#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "repositories/product_repository.h"

int main(void) {
    ProductCatalog catalog;
    Product apple = {1, "Apple", 1.50, 0};
    Product banana = {2, "Banana", 2.00, 0};
    Product duplicate = {1, "Duplicate", 3.10, 0};
    char error[MAX_ERROR_LENGTH] = {0};

    catalog_init(&catalog);

    assert(catalog_add(&catalog, apple, error, sizeof(error)) == 1);
    assert(catalog_add(&catalog, banana, error, sizeof(error)) == 1);
    assert(catalog.count == 2);

    assert(catalog_add(&catalog, duplicate, error, sizeof(error)) == 0);
    assert(catalog.count == 2);

    assert(catalog_apply_sale(&catalog, 1, 4, error, sizeof(error)) == 1);
    assert(catalog_find_by_code(&catalog, 1)->sold_quantity == 4);

    assert(catalog_update(&catalog, 2, "Banana Premium", 2.45, error, sizeof(error)) == 1);
    assert(strcmp(catalog_find_by_code(&catalog, 2)->name, "Banana Premium") == 0);

    assert(catalog_remove(&catalog, 1, error, sizeof(error)) == 1);
    assert(catalog.count == 1);
    assert(catalog_find_by_code(&catalog, 1) == NULL);

    printf("test_product_repository: OK\n");
    return 0;
}
