struct s_dispatcher;
typedef struct s_dispatcher dispatcher;

dispatcher *create_dispatcher(int threads);
void delete_dispatcher(dispatcher *ctx);
int step_dispatcher();


