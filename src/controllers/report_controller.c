#include "controllers/report_controller.h"

#include "services/report_service.h"
#include "views/console_view.h"

void report_controller_show(const ProductCatalog *catalog) {
    SalesReport report;
    char error[MAX_ERROR_LENGTH] = {0};

    if (!report_build(catalog, &report, error, sizeof(error))) {
        view_show_error(error);
        return;
    }

    view_print_report(&report);
}
