#pragma once
#ifndef _StbGMaker_AreaSailCreator_Const_Header
#define _StbGMaker_AreaSailCreator_Const_Header

#include <StbGMaker_AreaSailCreator.hxx>

namespace tnbLib
{

	namespace stbGmakerLib
	{

		class AreaSailCreator_Const
			: public StbGMaker_AreaSailCreator
		{

			/*Private Data*/

			Standard_Real theArea_;
			Standard_Real theZbar_;

		public:

			AreaSailCreator_Const
			(
				const Standard_Real theArea, 
				const Standard_Real theZbar
			);

			AreaSailCreator_Const
			(
				const Standard_Integer theIndex, 
				const Standard_Real theArea,
				const Standard_Real theZbar
			);

			AreaSailCreator_Const
			(
				const Standard_Integer theIndex, 
				const word& theName,
				const Standard_Real theArea, 
				const Standard_Real theZbar
			);

			auto Area() const
			{
				return theArea_;
			}

			auto zBar() const
			{
				return theZbar_;
			}

			stbGmakerLib::sailCreatotType Type() const override;

			void ExportAs
			(
				std::shared_ptr<Marine_Model>& theModel
			) const override;
		};
	}
}

#endif // !_StbGMaker_AreaSailCreator_Const_Header
