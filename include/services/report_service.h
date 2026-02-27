#ifndef SERVICES_REPORT_SERVICE_H
#define SERVICES_REPORT_SERVICE_H

#include <stddef.h>

#include "core/app_context.h"

typedef struct {
    int total_units;
    double total_revenue;
    double average_ticket;
    int best_seller_code;
    char best_seller_name[MAX_NAME_LENGTH];
    int best_seller_units;
    double best_seller_revenue;
} SalesReport;

int report_build(const ProductCatalog *catalog, SalesReport *report, char *error, size_t error_size);

#endif
