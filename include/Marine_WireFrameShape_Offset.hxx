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


			/*private functions and operators*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & boost::serialization::base_object<Marine_WireFrameShape>(*this);
			}

		public:

			
			//- constructors

			WireFrameShape_Offset()
			{}

			TnbMarine_EXPORT explicit WireFrameShape_Offset(const Standard_Integer theIndex);

			TnbMarine_EXPORT WireFrameShape_Offset
			(
				const Standard_Integer theIndex,
				const word& theName
			);

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::marineLib::WireFrameShape_Offset);

#endif // !_Marine_WireFrameShape_Offset_Header
