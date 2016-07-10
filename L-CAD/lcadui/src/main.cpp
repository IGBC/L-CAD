#include <NK_Wrapper.hpp>
#include <cstdio>
	
static NK_WRAPPER NKW;
		
void GUI(struct nk_context *ctx) {
    struct nk_panel layout;

    if (nk_begin(ctx, &layout, (char*)"TOOLBARTHING", nk_rect(0, 0, 120, WINDOW_HEIGHT),
        NK_WINDOW_BORDER|NK_WINDOW_TITLE))
    {
        enum {EASY, HARD};
        static int op = EASY;
        static int property = 20;
        
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "Exit", NK_BUTTON_DEFAULT)) {
            fprintf(stdout, "button pressed\n");
            NKW.running = false;
        }
    }
    nk_end(ctx);


    if (nk_begin(ctx, &layout, (char*)"Floaty Thing", nk_rect(0, 0, 100, 100),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
        NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        enum {EASY, HARD};
        static int op = EASY;
        static int property = 20;
        
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "Exit", NK_BUTTON_DEFAULT)) {
            fprintf(stdout, "button pressed\n");
            NKW.running = false;
        }
    }
    nk_end(ctx);
}

void *GUICode(struct nk_context *ctx) {
		GUI(ctx);
}

int main(void) {
    printf("started NK_SDL\n");
    while (NKW.running) {
        NKW.draw(GUICode);
    }
}

