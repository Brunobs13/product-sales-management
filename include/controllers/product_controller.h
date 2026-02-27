#ifndef CONTROLLERS_PRODUCT_CONTROLLER_H
#define CONTROLLERS_PRODUCT_CONTROLLER_H

#include "core/app_context.h"

void product_controller_list(const ProductCatalog *catalog);
void product_controller_add(ProductCatalog *catalog);
void product_controller_edit(ProductCatalog *catalog);
void product_controller_remove(ProductCatalog *catalog);
void product_controller_register_sale(ProductCatalog *catalog, SalesRegistry *sales);

#endif
