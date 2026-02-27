#include "services/report_service.h"

#include <stdio.h>
#include <string.h>

static void write_error(char *error, size_t error_size, const char *message) {
    if (error != NULL && error_size > 0) {
        snprintf(error, error_size, "%s", message);
    }
}

int report_build(const ProductCatalog *catalog, SalesReport *report, char *error, size_t error_size) {
    if (catalog == NULL || report == NULL) {
        write_error(error, error_size, "Invalid report arguments.");
        return 0;
    }

    report->total_units = 0;
    report->total_revenue = 0.0;
    report->average_ticket = 0.0;
    report->best_seller_code = -1;
    report->best_seller_units = 0;
    report->best_seller_revenue = 0.0;
    snprintf(report->best_seller_name, sizeof(report->best_seller_name), "%s", "N/A");

    for (size_t i = 0; i < catalog->count; ++i) {
        const Product *product = &catalog->items[i];
        double product_revenue = product->price * (double)product->sold_quantity;

        report->total_units += product->sold_quantity;
        report->total_revenue += product_revenue;

        if (product->sold_quantity > report->best_seller_units) {
            report->best_seller_units = product->sold_quantity;
            report->best_seller_revenue = product_revenue;
            report->best_seller_code = product->code;
            snprintf(report->best_seller_name, sizeof(report->best_seller_name), "%s", product->name);
        }
    }

    if (catalog->count > 0) {
        report->average_ticket = report->total_revenue / (double)catalog->count;
    }

    return 1;
}
