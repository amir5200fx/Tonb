#pragma once
#ifndef _StbGMaker_GeometricSailCreator_noShape_Header
#define _StbGMaker_GeometricSailCreator_noShape_Header

#include <StbGMaker_VolumeSailCreator.hxx>
#include <StbGMaker_Alg.hxx>
#include <Marine_ShapesFwd.hxx>

namespace tnbLib
{

	namespace stbGmakerLib
	{

		class VolumeSailCreator_noShape
			: public StbGMaker_VolumeSailCreator
		{

			/*Private Data*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<StbGMaker_VolumeSailCreator>(*this);
				ar & boost::serialization::base_object<StbGMaker_Alg>(*this);
			}

		public:

			VolumeSailCreator_noShape()
			{}

			TnbStbGMaker_EXPORT VolumeSailCreator_noShape
			(
				const Standard_Integer theIndex, 
				const word& theName
			);

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

BOOST_CLASS_EXPORT_KEY(tnbLib::stbGmakerLib::VolumeSailCreator_noShape);

#endif // !_StbGMaker_GeometricSailCreator_noShape_Header
