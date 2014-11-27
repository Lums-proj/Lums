/* ************************************************************************** */
/*                                                                            */
/*                                                  &&&&&&       &&&&&&       */
/*    Lums.h                                       &------&     &------&      */
/*                                                  &&-----&   &-----&&       */
/*                                                    &&&&#######&&&&         */
/*                                                       #.......#            */
/*                                                       #.....  #            */
/*    This file is part of the                           #...    #            */
/*    Lums library.                                       #######             */
/*                                                                            */
/* ************************************************************************** */

#ifndef LUMS_H
#define LUMS_H

#define LUMS_STR2(str)      #str
#define LUMS_STR(str)       LUMS_STR2(str)
#define LUMS_VERSION_MAJOR  2
#define LUMS_VERSION_MINOR  1
#define LUMS_VERSION_TEENY  0
#define LUMS_VERSION_PATCH  0

#define LUMS_VERSION_NUMBER LUMS_STR(LUMS_VERSION_MAJOR) "." LUMS_STR(LUMS_VERSION_MINOR) "." LUMS_STR(LUMS_VERSION_TEENY)

#if LUMS_VERSION_PATCH == 0
# define LUMS_VERSION   LUMS_VERSION_NUMBER
#else
# define LUMS_VERSION   LUMS_VERSION_NUMBER "p" LUMS_STR(LUMS_VERSION_PATCH)
#endif

#include <Lums/Angle.h>
#include <Lums/Core.h>
#include <Lums/GameState.h>
#include <Lums/GL.h>
#include <Lums/Image.h>
#include <Lums/OperatingSystem.h>
#include <Lums/Vector2.h>
#include <Lums/Vector3.h>

#endif