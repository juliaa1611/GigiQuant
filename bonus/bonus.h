#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <math.h>
#include "cJSON.h"

struct MemoryStruct {
    char *memory;
    size_t size;
};

double randament(double pt, double pt_anterior);
double calculareRandamentTotal(double *prices, int price_count);
double trunchiere(double x);
double deviatia_standard(double *prices, int price_count, double r_mediu);
void calculare_volat(double *prices, int price_count);
static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
double* get_open_prices(const char* symbol, const char* interval, const char* range, int *count_out);