#pragma once
#ifndef _SectPx_FieldFun_readX_Header
#define _SectPx_FieldFun_readX_Header

#include <SectPx_nonParFieldFun.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Coord;


	namespace sectPxLib
	{

		class FieldFun_readX
			: public SectPx_nonParFieldFun
		{

			/*Private Data*/

			std::shared_ptr<SectPx_Coord> theCoord_;

		public:

			static const char* typeName_;

			FieldFun_readX
			(
				const std::shared_ptr<SectPx_Coord>& theCoord
			);

			FieldFun_readX
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<SectPx_Coord>& theCoord
			);

			FieldFun_readX
			(
				const Standard_Integer theIndex,
				const word& theName,
				const std::shared_ptr<SectPx_Coord>& theCoord
			);


			const auto& Coord() const
			{
				return theCoord_;
			}

			word RegObjTypeName() const override;

			Standard_Real Value() const override;
		};
	}
}

#endif // !_SectPx_FieldFun_readX_Header
