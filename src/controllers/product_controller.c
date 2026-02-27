#include "controllers/product_controller.h"

#include <stdio.h>
#include <string.h>

#include "repositories/product_repository.h"
#include "repositories/sale_repository.h"
#include "views/console_view.h"

void product_controller_list(const ProductCatalog *catalog) {
    view_list_products(catalog);
}

void product_controller_add(ProductCatalog *catalog) {
    Product product;
    char error[MAX_ERROR_LENGTH] = {0};

    memset(&product, 0, sizeof(product));

    if (!view_read_int("Product code: ", &product.code) || product.code <= 0) {
        view_show_error("Invalid code.");
        return;
    }

    if (!view_read_text("Product name: ", product.name, sizeof(product.name)) || strlen(product.name) == 0) {
        view_show_error("Invalid name.");
        return;
    }

    if (!view_read_double("Product price: ", &product.price) || product.price < 0) {
        view_show_error("Invalid price.");
        return;
    }

    if (!catalog_add(catalog, product, error, sizeof(error))) {
        view_show_error(error);
        return;
    }

    view_show_message("Product added successfully.");
}

void product_controller_edit(ProductCatalog *catalog) {
    int code;
    double price;
    char name[MAX_NAME_LENGTH];
    char error[MAX_ERROR_LENGTH] = {0};

    if (!view_read_int("Code to edit: ", &code)) {
        view_show_error("Invalid code.");
        return;
    }

    if (!view_read_text("New name: ", name, sizeof(name)) || strlen(name) == 0) {
        view_show_error("Invalid name.");
        return;
    }

    if (!view_read_double("New price: ", &price) || price < 0) {
        view_show_error("Invalid price.");
        return;
    }

    if (!catalog_update(catalog, code, name, price, error, sizeof(error))) {
        view_show_error(error);
        return;
    }

    view_show_message("Product updated successfully.");
}

void product_controller_remove(ProductCatalog *catalog) {
    int code;
    char error[MAX_ERROR_LENGTH] = {0};

    if (!view_read_int("Code to remove: ", &code)) {
        view_show_error("Invalid code.");
        return;
    }

    if (!catalog_remove(catalog, code, error, sizeof(error))) {
        view_show_error(error);
        return;
    }

    view_show_message("Product removed successfully.");
}

void product_controller_register_sale(ProductCatalog *catalog, SalesRegistry *sales) {
    Sale sale;
    char error[MAX_ERROR_LENGTH] = {0};

    memset(&sale, 0, sizeof(sale));

    if (!view_read_int("Product code sold: ", &sale.product_code)) {
        view_show_error("Invalid code.");
        return;
    }

    if (!view_read_int("Quantity sold: ", &sale.quantity) || sale.quantity <= 0) {
        view_show_error("Invalid quantity.");
        return;
    }

    if (!view_read_text("Date (YYYY-MM-DD): ", sale.date, sizeof(sale.date))) {
        view_show_error("Invalid date.");
        return;
    }

    if (!sales_add(sales, catalog, sale, error, sizeof(error))) {
        view_show_error(error);
        return;
    }

    view_show_message("Sale registered successfully.");
}
