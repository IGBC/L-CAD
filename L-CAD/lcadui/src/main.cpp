#include <NK_Wrapper.hpp>
#include <cstdio>
	
static NK_WRAPPER NKW;
		
void GUI(struct nk_context *ctx, char *name) {
	struct nk_panel layout;
    if (nk_begin(ctx, &layout, name, nk_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT),
        0/*NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
        NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE*/))
    {
        enum {EASY, HARD};
        static int op = EASY;
        static int property = 20;
        
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button", NK_BUTTON_DEFAULT)) {
            fprintf(stdout, "button pressed\n");
            NKW.running = false;
        }
        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
        nk_layout_row_dynamic(ctx, 25, 1);
        nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);
		
        {struct nk_panel combo;
        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 1);
        /*if (nk_combo_begin_color(ctx, &combo, background, 400)) {
            nk_layout_row_dynamic(ctx, 120, 1);
            //background = nk_color_picker(ctx, background, NK_RGBA);
            nk_layout_row_dynamic(ctx, 25, 1);
            background.r = (nk_byte)nk_propertyi(ctx, "#R:", 0, background.r, 255, 1,1);
            background.g = (nk_byte)nk_propertyi(ctx, "#G:", 0, background.g, 255, 1,1);
            background.b = (nk_byte)nk_propertyi(ctx, "#B:", 0, background.b, 255, 1,1);
            background.a = (nk_byte)nk_propertyi(ctx, "#A:", 0, background.a, 255, 1,1);
            nk_combo_end(ctx);
        }*/}
    }
    nk_end(ctx);
}

void *GUICode(struct nk_context *ctx) {
		GUI(ctx, "1");
		GUI(ctx, "2");
}

int main(void) {
    printf("started NK_SDL\n");
    while (NKW.running) {
        NKW.draw(GUICode);
    }
}

