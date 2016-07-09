
// From spacekookie
#define CHECK_BUFFER(type, bfr, max_s, curr_s) \
    { if(curr_s >= max_s) { \
        max_s *= 2; type *tmp = calloc(sizeof(type), max_s); \
        if(!tmp) return QCRY_STATUS_MALLOC_FAIL; \
        memcpy(tmp, bfr, sizeof(type) * curr_s); \
        free(bfr); \
        bfr = tmp; \
    } else if(curr_s * 3<= max_s) { max_s /= 2 ; \
    if(max_s < MIN_BFR_S) max_s = MIN_BFR_S; \
        type *tmp = calloc(sizeof(type), max_s); \
        if(!tmp) return QCRY_STATUS_MALLOC_FAIL; \
        memcpy(tmp, bfr, sizeof(type) * curr_s); \
        free(bfr); \
        bfr = tmp; } \
    }
    
typedef struct s_fastlist fastlist;

fastlist *new_fastlist(unsigned long size);
void *fastlist-dispose(fastlist *ctx);

void *fastlist_get(fastlist *ctx, unsigned long index);

int fastlist_add(fastlist *ctx, void** item);
void *fastlist_remove(fastlist *ctx, unsigned long index);

void **fastlist_dma(fastlist *ctx, &unsigned long size);


