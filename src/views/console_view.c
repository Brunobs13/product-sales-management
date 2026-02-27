#include "views/console_view.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int view_show_menu(void) {
    int option = -1;

    printf("\n=== Product Sales Management ===\n");
    printf("1 - List products\n");
    printf("2 - Add product\n");
    printf("3 - Edit product\n");
    printf("4 - Remove product\n");
    printf("5 - Register sale\n");
    printf("6 - Generate sales report\n");
    printf("0 - Exit\n");
    view_read_int("Choose an option: ", &option);
    return option;
}

void view_show_message(const char *message) {
    printf("%s\n", message);
}

void view_show_error(const char *message) {
    fprintf(stderr, "[ERROR] %s\n", message);
}

void view_list_products(const ProductCatalog *catalog) {
    printf("\n%-8s %-32s %-12s %-12s\n", "Code", "Name", "Price", "Sold Units");
    printf("%-8s %-32s %-12s %-12s\n", "--------", "--------------------------------", "------------", "------------");

    if (catalog == NULL || catalog->count == 0) {
        printf("No products available.\n");
        return;
    }

    for (size_t i = 0; i < catalog->count; ++i) {
        printf("%-8d %-32s %-12.2f %-12d\n",
               catalog->items[i].code,
               catalog->items[i].name,
               catalog->items[i].price,
               catalog->items[i].sold_quantity);
    }
}

void view_print_report(const SalesReport *report) {
    if (report == NULL) {
        return;
    }

    printf("\n=== Sales Report ===\n");
    printf("Total units sold: %d\n", report->total_units);
    printf("Total revenue: %.2f\n", report->total_revenue);
    printf("Average ticket per product: %.2f\n", report->average_ticket);
    printf("Best seller: [%d] %s\n", report->best_seller_code, report->best_seller_name);
    printf("Best seller units: %d\n", report->best_seller_units);
    printf("Best seller revenue: %.2f\n", report->best_seller_revenue);
}

int view_read_int(const char *prompt, int *value) {
    char buffer[64];
    char *end = NULL;
    long parsed;

    if (value == NULL) {
        return 0;
    }

    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    parsed = strtol(buffer, &end, 10);
    if (end == buffer) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

int view_read_double(const char *prompt, double *value) {
    char buffer[64];
    char *end = NULL;
    double parsed;

    if (value == NULL) {
        return 0;
    }

    printf("%s", prompt);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    parsed = strtod(buffer, &end);
    if (end == buffer) {
        return 0;
    }

    *value = parsed;
    return 1;
}

int view_read_text(const char *prompt, char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return 0;
    }

    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL) {
        return 0;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return 1;
}
