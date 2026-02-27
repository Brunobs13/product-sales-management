#ifndef VIEWS_CONSOLE_VIEW_H
#define VIEWS_CONSOLE_VIEW_H

#include <stddef.h>

#include "core/app_context.h"
#include "services/report_service.h"

int view_show_menu(void);
void view_show_message(const char *message);
void view_show_error(const char *message);
void view_list_products(const ProductCatalog *catalog);
void view_print_report(const SalesReport *report);
int view_read_int(const char *prompt, int *value);
int view_read_double(const char *prompt, double *value);
int view_read_text(const char *prompt, char *buffer, size_t size);

#endif
