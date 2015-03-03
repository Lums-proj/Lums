/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*    FrameDescriptor.hpp                            oooooo       oooooo      */
/*                                                 oooooooooo   oooooooooo    */
/*                                                         o%%%%%o            */
/*                                                         %:::::%            */
/*                                                        %:::::::%           */
/*    This file is part of the                             %:::::%            */
/*    Lums library.                                         %%%%%             */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAME_DESCRIPTOR_HPP
#define FRAME_DESCRIPTOR_HPP

namespace lm
{
	template <class T>
	struct FrameDescriptor
	{
		T		x;
		T		y;
		T		w;
		T		h;
		int		offX;
		int		offY;
	};

	typedef FrameDescriptor<int>	FrameDescriptori;
	typedef FrameDescriptor<double>	FrameDescriptord;
}

#endif
