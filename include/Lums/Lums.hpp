/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    Lums.hpp                                       oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_HPP
#define LUMS_HPP

#define LUMS_STR2(str)      #str
#define LUMS_STR(str)       LUMS_STR2(str)
#define LUMS_VERSION_MAJOR  2
#define LUMS_VERSION_MINOR  6
#define LUMS_VERSION_TEENY  1
#define LUMS_VERSION_PATCH  0

#define LUMS_VERSION_NUMBER LUMS_STR(LUMS_VERSION_MAJOR) "."	\
							LUMS_STR(LUMS_VERSION_MINOR) "." 	\
							LUMS_STR(LUMS_VERSION_TEENY)

#if LUMS_VERSION_PATCH == 0
# define LUMS_VERSION   LUMS_VERSION_NUMBER
#else
# define LUMS_VERSION   LUMS_VERSION_NUMBER "p" LUMS_STR(LUMS_VERSION_PATCH)
#endif

#include <Lums/Angle.hpp>
#include <Lums/Core.hpp>
#include <Lums/Event.hpp>
#include <Lums/Font.hpp>
#include <Lums/GameState.hpp>
#include <Lums/GL.hpp>
#include <Lums/Image.hpp>
#include <Lums/Key.hpp>
#include <Lums/OperatingSystem.hpp>
#include <Lums/Rect2.hpp>
#include <Lums/Script.hpp>
#include <Lums/Sound.hpp>
#include <Lums/SoundManager.hpp>
#include <Lums/Sprite.hpp>
#include <Lums/SpriteBatch.hpp>
#include <Lums/Vector2.hpp>
#include <Lums/Vector3.hpp>
#include <Lums/VertexArray.hpp>
#include <Lums/Window.hpp>

#endif
