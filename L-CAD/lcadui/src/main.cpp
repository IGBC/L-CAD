/*
 * This file is part of the L-CAD project
 * Copyright (c) 2016  Ashley Brown, Katharina Sabel
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 */


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

