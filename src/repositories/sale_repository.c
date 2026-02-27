#include "repositories/sale_repository.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "repositories/product_repository.h"

static void write_error(char *error, size_t error_size, const char *message) {
    if (error != NULL && error_size > 0) {
        snprintf(error, error_size, "%s", message);
    }
}

static void trim(char *text) {
    size_t len = strlen(text);
    while (len > 0 && (text[len - 1] == '\n' || text[len - 1] == '\r' || isspace((unsigned char)text[len - 1]))) {
        text[len - 1] = '\0';
        len--;
    }

    size_t start = 0;
    while (text[start] != '\0' && isspace((unsigned char)text[start])) {
        start++;
    }

    if (start > 0) {
        memmove(text, text + start, strlen(text + start) + 1);
    }
}

static int is_valid_date(const char *date) {
    if (date == NULL || strlen(date) != 10) {
        return 0;
    }

    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') {
                return 0;
            }
        } else if (!isdigit((unsigned char)date[i])) {
            return 0;
        }
    }

    return 1;
}

void sales_init(SalesRegistry *sales) {
    if (sales == NULL) {
        return;
    }

    sales->count = 0;
}

int sales_add(SalesRegistry *sales, ProductCatalog *catalog, Sale sale, char *error, size_t error_size) {
    if (sales == NULL || catalog == NULL) {
        write_error(error, error_size, "Invalid sales add arguments.");
        return 0;
    }

    if (sales->count >= MAX_SALES) {
        write_error(error, error_size, "Sales capacity reached.");
        return 0;
    }

    if (sale.quantity <= 0 || !is_valid_date(sale.date)) {
        write_error(error, error_size, "Invalid sale payload.");
        return 0;
    }

    if (!catalog_apply_sale(catalog, sale.product_code, sale.quantity, error, error_size)) {
        return 0;
    }

    sales->items[sales->count++] = sale;
    return 1;
}

int sales_load_from_csv(SalesRegistry *sales, ProductCatalog *catalog, const char *path, char *error, size_t error_size) {
    if (sales == NULL || catalog == NULL || path == NULL) {
        write_error(error, error_size, "Invalid sales load arguments.");
        return 0;
    }

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        write_error(error, error_size, "Sales CSV not found. Starting with an empty sales registry.");
        return 0;
    }

    sales_init(sales);
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        Sale sale;
        char *code_text;
        char *quantity_text;
        char *date_text;
        char local_error[MAX_ERROR_LENGTH] = {0};

        trim(line);
        if (strlen(line) == 0) {
            continue;
        }

        code_text = strtok(line, ",");
        quantity_text = strtok(NULL, ",");
        date_text = strtok(NULL, ",");

        if (code_text == NULL || quantity_text == NULL || date_text == NULL) {
            continue;
        }

        trim(code_text);
        trim(quantity_text);
        trim(date_text);

        sale.product_code = atoi(code_text);
        sale.quantity = atoi(quantity_text);
        snprintf(sale.date, sizeof(sale.date), "%s", date_text);

        if (!sales_add(sales, catalog, sale, local_error, sizeof(local_error))) {
            continue;
        }
    }

    fclose(file);
    return 1;
}

int sales_save_to_csv(const SalesRegistry *sales, const char *path, char *error, size_t error_size) {
    if (sales == NULL || path == NULL) {
        write_error(error, error_size, "Invalid sales save arguments.");
        return 0;
    }

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        write_error(error, error_size, "Unable to open sales CSV for writing.");
        return 0;
    }

    for (size_t i = 0; i < sales->count; ++i) {
        fprintf(file, "%d,%d,%s\n", sales->items[i].product_code, sales->items[i].quantity, sales->items[i].date);
    }

    fclose(file);
    return 1;
}
