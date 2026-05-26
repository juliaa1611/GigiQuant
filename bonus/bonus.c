#include "bonus.h"

double randament(double pt, double pt_anterior) {
    return ((pt-pt_anterior)/pt_anterior);
}

double calculareRandamentTotal(double *prices, int price_count) {
    double randament_total = 0;
    for (int i = 1; i < price_count; i ++) 
        randament_total += randament(prices[i], prices[i - 1]);
    return randament_total;
}

double trunchiere(double x) {
    return trunc(x * 1000.0)/1000.0;
}

double deviatia_standard(double *prices, int price_count, double r_mediu) {
    double suma = 0;
    for (int i = 1; i < price_count; i ++) {
        double r_curent = randament(prices[i], prices[i - 1]);
        double diferenta = (r_mediu - r_curent);
        suma += (diferenta * diferenta);
    }
    return suma;
}

void calculare_volat(double *prices, int price_count) {
    double rand_mediu = (calculareRandamentTotal(prices, price_count));
    printf("Randamentul mediu: %.3lf\n", trunchiere(rand_mediu));
    double volat = sqrt(deviatia_standard(prices, price_count, rand_mediu));
    printf("Volatilitatea: %.3lf\n", trunchiere(volat));
    double sharpe_ratio = 0;
    if (volat) 
        sharpe_ratio = (rand_mediu / volat);
    printf("Sharpe Ratio: %.3lf\n", trunchiere(sharpe_ratio));
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *) userp;
    
    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) return 0;
    
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    
    return realsize;
}

double* get_open_prices(const char* symbol, const char* interval, const char* range, int *count_out) {
    CURL *curl_handle;
    struct MemoryStruct chunk = {malloc(1), 0};
    char url[256];
    double *prices = NULL;
    
    sprintf(url, "https://query1.finance.yahoo.com/v8/finance/chart/%s?interval=%s&range=%s", symbol, interval, range);
    
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    
    if (curl_easy_perform(curl_handle) == CURLE_OK) {
        cJSON *json = cJSON_Parse(chunk.memory);
        cJSON *result = cJSON_GetArrayItem(cJSON_GetObjectItem(cJSON_GetObjectItem(json, "chart"), "result"), 0);
        cJSON *quote = cJSON_GetArrayItem(cJSON_GetObjectItem(cJSON_GetObjectItem(result, "indicators"), "quote"), 0);
        cJSON *open_prices = cJSON_GetObjectItem(quote, "open");
        
        *count_out = cJSON_GetArraySize(open_prices);
        prices = malloc((*count_out) * sizeof(double));
        
        for (int i = 0; i < *count_out; i++) {
            cJSON *val = cJSON_GetArrayItem(open_prices, i);
            prices[i] = cJSON_IsNumber(val) ? val->valuedouble : -1.0;
        }
        cJSON_Delete(json);
    }
    
    curl_easy_cleanup(curl_handle);
    free(chunk.memory);
    
    return prices;
}

int main() {
    int price_count = 0;
    char cmp[5], interval[5], dur[5];
    printf("Frima (AAPL, AMZN, GOOG, NVDA, etc): "); scanf("%s", cmp); getchar();
    printf("Intervalul de timp intre preturi (ex: 1d): "); scanf("%s", interval);
    printf("Durata totala: "); scanf("%s", dur);
    double *prices = get_open_prices(cmp, interval, dur, &price_count);
    if (price_count == 0 || prices == 0) {
        printf("Eroare la descarcarea datelor!\n");
        return 1;
    }

    printf("Pentru firma %s s-au descarcat %d preturi:\n", cmp, price_count);
    for (int i = 0; i < price_count; i ++)
        printf("%.2f\n", prices[i]);
    printf("\n");
    calculare_volat(prices, price_count);
}