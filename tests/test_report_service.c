#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "services/report_service.h"

int main(void) {
    ProductCatalog catalog;
    SalesReport report;
    Product p1 = {101, "Keyboard", 50.0, 5};
    Product p2 = {102, "Mouse", 30.0, 7};
    char error[MAX_ERROR_LENGTH] = {0};

    catalog.count = 2;
    catalog.items[0] = p1;
    catalog.items[1] = p2;

    assert(report_build(&catalog, &report, error, sizeof(error)) == 1);
    assert(report.total_units == 12);
    assert(report.total_revenue == 460.0);
    assert(report.best_seller_code == 102);
    assert(strcmp(report.best_seller_name, "Mouse") == 0);

    printf("test_report_service: OK\n");
    return 0;
}
