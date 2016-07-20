/* nuklear - v1.00 - public domain */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GL3_IMPLEMENTATION
#include "nuklear.h"
#include "nuklear_sdl_gl3.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

class NK_WRAPPER {
	public:
	
		bool running = false;
		
		NK_WRAPPER() {
			/* SDL setup */
			SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
			SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_EVENTS);
			SDL_GL_SetAttribute (SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
			SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			win = SDL_CreateWindow("Demo",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
			glContext = SDL_GL_CreateContext(win);
			SDL_GetWindowSize(win, &win_width, &win_height);

			/* OpenGL setup */
			glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			glewExperimental = 1;
			if (glewInit() != GLEW_OK) {
				fprintf(stderr, "Failed to setup GLEW\n");
				exit(1);
			}

			/* Generate NK context */
			ctx = nk_sdl_init(win);
			
			/* Load Default Font  */
			struct nk_font_atlas *atlas;
			nk_sdl_font_stash_begin(&atlas);
			nk_sdl_font_stash_end();

			background = nk_rgb(28,48,62);
			
			/* set running status */
			running = true;
		};

		~NK_WRAPPER() {
			nk_sdl_shutdown();
			SDL_GL_DeleteContext(glContext);
			SDL_DestroyWindow(win);
			SDL_Quit();
		};
		
		void draw(void *GUICode(struct nk_context *uictx)) {
			/* Handle Input Events */
       		SDL_Event evt;
        	nk_input_begin(ctx);
        	while (SDL_PollEvent(&evt)) {
            	if (evt.type == SDL_QUIT) {
            		running = false;
            		return;
            	}
            	nk_sdl_handle_event(&evt);
        	}
        	nk_input_end(ctx);
        	
        	/* Call GUI Code */
        	GUICode(ctx);
        	
        	/* Finally the draw calls */
		    {
				float bg[4];
				nk_color_fv(bg, background);
				SDL_GetWindowSize(win, &win_width, &win_height);
				glViewport(0, 0, win_width, win_height);
				glClear(GL_COLOR_BUFFER_BIT);
				glClearColor(bg[0], bg[1], bg[2], bg[3]);
				/* IMPORTANT: `nk_sdl_render` modifies some global OpenGL state
				 * with blending, scissor, face culling, depth test and viewport and
				 * defaults everything back into a default state.
				 * Make sure to either a.) save and restore or b.) reset your own state after
				 * rendering the UI. */
				nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
				SDL_GL_SwapWindow(win);
		    }
        	
        	
		};
		
	private:
		/* Platform Variables */
		SDL_Window *win;
		SDL_GLContext glContext;
		struct nk_color background;
		int win_width, win_height;
		
		/* GUI Context */
		struct nk_context *ctx;
};
