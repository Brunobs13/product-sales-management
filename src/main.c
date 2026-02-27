#include <stdio.h>
#include <stdlib.h>

#include "controllers/product_controller.h"
#include "controllers/report_controller.h"
#include "repositories/product_repository.h"
#include "repositories/sale_repository.h"
#include "views/console_view.h"

int main(void) {
    ProductCatalog catalog;
    SalesRegistry sales;
    char error[MAX_ERROR_LENGTH] = {0};

    const char *products_path = getenv("PSM_PRODUCTS_CSV");
    const char *sales_path = getenv("PSM_SALES_CSV");

    if (products_path == NULL || products_path[0] == '\0') {
        products_path = "data/products.csv";
    }

    if (sales_path == NULL || sales_path[0] == '\0') {
        sales_path = "data/sales.csv";
    }

    catalog_init(&catalog);
    sales_init(&sales);

    if (!catalog_load_from_csv(&catalog, products_path, error, sizeof(error))) {
        view_show_message(error);
    }

    if (!sales_load_from_csv(&sales, &catalog, sales_path, error, sizeof(error))) {
        view_show_message(error);
    }

    for (;;) {
        int option = view_show_menu();

        switch (option) {
            case 1:
                product_controller_list(&catalog);
                break;
            case 2:
                product_controller_add(&catalog);
                break;
            case 3:
                product_controller_edit(&catalog);
                break;
            case 4:
                product_controller_remove(&catalog);
                break;
            case 5:
                product_controller_register_sale(&catalog, &sales);
                break;
            case 6:
                report_controller_show(&catalog);
                break;
            case 0:
                if (!catalog_save_to_csv(&catalog, products_path, error, sizeof(error))) {
                    view_show_error(error);
                }
                if (!sales_save_to_csv(&sales, sales_path, error, sizeof(error))) {
                    view_show_error(error);
                }
                view_show_message("State persisted. Goodbye.");
                return 0;
            default:
                view_show_error("Invalid option.");
                break;
        }
    }
}
