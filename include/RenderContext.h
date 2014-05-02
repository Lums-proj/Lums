/* ************************************************************************** */
/*                                                                            */
/*                                        ::::    :::  ::::::::  :::          */
/*    RenderContext.h                     :+:+:   :+: :+:    :+: :+:          */
/*                                        :+:+:+  +:+ +:+        +:+          */
/*                                        +#+ +:+ +#+ :#:        +#+          */
/*                                        +#+  +#+#+# +#+   +#+# +#+          */
/*    This file is part of the            #+#   #+#+# #+#    #+# #+#          */
/*    NGL library.                        ###    ####  ########  ##########   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERCONTEXT_H
#define RENDERCONTEXT_H

#include <SDL2/SDL.h>

namespace ngl
{

/**
 * @struct RenderContext
 * A POD class representing a render context.
 * All members are public.
 */
struct RenderContext
{
	SDL_Window*		window;
	SDL_Renderer*	renderer;
	int				w;
	int				h;
};

}

#endif /* !RENDERCONTEXT_H */