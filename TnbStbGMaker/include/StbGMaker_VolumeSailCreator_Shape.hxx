#pragma once
#ifndef _StbGMaker_VolumeSailCreator_Shape_Header
#define _StbGMaker_VolumeSailCreator_Shape_Header

#include <StbGMaker_VolumeSailCreator.hxx>
#include <StbGMaker_Alg.hxx>
#include <Marine_ShapesFwd.hxx>

namespace tnbLib
{

	namespace stbGmakerLib
	{

		class VolumeSailCreator_Shape
			: public StbGMaker_VolumeSailCreator
		{

			/*Private Data*/

			std::shared_ptr<marineLib::Shape_Sail>
				theShape_;

			DECLARE_SAVE_LOAD_HEADER(TnbStbGMaker_EXPORT);

			VolumeSailCreator_Shape()
			{}

		public:


			TnbStbGMaker_EXPORT VolumeSailCreator_Shape
			(
				const std::shared_ptr<marineLib::Shape_Sail>& theShape
			);

			TnbStbGMaker_EXPORT VolumeSailCreator_Shape
			(
				std::shared_ptr<marineLib::Shape_Sail>&& theShape
			);

			TnbStbGMaker_EXPORT VolumeSailCreator_Shape
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<marineLib::Shape_Sail>& theShape
			);

			TnbStbGMaker_EXPORT VolumeSailCreator_Shape
			(
				const Standard_Integer theIndex, 
				std::shared_ptr<marineLib::Shape_Sail>&& theShape
			);

			TnbStbGMaker_EXPORT VolumeSailCreator_Shape
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const std::shared_ptr<marineLib::Shape_Sail>& theShape
			);

			TnbStbGMaker_EXPORT VolumeSailCreator_Shape
			(
				const Standard_Integer theIndex, 
				const word& theName,
				std::shared_ptr<marineLib::Shape_Sail>&& theShape
			);


			const auto& Shape() const
			{
				return theShape_;
			}

			TnbStbGMaker_EXPORT Standard_Integer
				CreateWorkingPlane
				(
					const Standard_Real x
				) override;

			TnbStbGMaker_EXPORT stbGmakerLib::sailCreatorType Type() const override;

			TnbStbGMaker_EXPORT void ExportAs
			(
				std::shared_ptr<Marine_Model>& theModel
			) const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::stbGmakerLib::VolumeSailCreator_Shape);

#endif // !_StbGMaker_VolumeSailCreator_Shape_Header
