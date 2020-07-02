#pragma once
#ifndef _Marine_WireFrameShape_Offset_Header
#define _Marine_WireFrameShape_Offset_Header

#include <Marine_WireFrameShape.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_DisctLib;

	namespace marineLib
	{

		class WireFrameShape_Offset
			: public Marine_WireFrameShape
		{

			friend class Marine_DisctLib;

			/*Private Data*/

		public:

			template<class... _Types>
			WireFrameShape_Offset(_Types&&... _Args)
				: Marine_WireFrameShape(_Args...)
			{}

		};
	}
}

#endif // !_Marine_WireFrameShape_Offset_Header
