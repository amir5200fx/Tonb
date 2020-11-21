#pragma once
#ifndef _StbGMaker_GeometricSailCreator_noShape_Header
#define _StbGMaker_GeometricSailCreator_noShape_Header

#include <StbGMaker_GeometricSailCreator.hxx>
#include <StbGMaker_Alg.hxx>
#include <Marine_ShapesFwd.hxx>

namespace tnbLib
{

	namespace stbGmakerLib
	{

		class GeometricSailCreator_noShape
			: public StbGMaker_GeometricSailCreator
			, public StbGMaker_Alg
		{

			/*Private Data*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<StbGMaker_GeometricSailCreator>(*this);
				ar & boost::serialization::base_object<StbGMaker_Alg>(*this);
			}

		public:

			GeometricSailCreator_noShape()
			{}

			TnbStbGMaker_EXPORT GeometricSailCreator_noShape
			(
				const Standard_Integer theIndex, 
				const word& theName
			);

			TnbStbGMaker_EXPORT Standard_Integer
				CreateWorkingPlane
				(
					const Standard_Real x
				) override;

			TnbStbGMaker_EXPORT stbGmakerLib::sailCreatotType Type() const override;

			TnbStbGMaker_EXPORT void ExportAs
			(
				std::shared_ptr<Marine_Model>& theModel
			) const override;
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::stbGmakerLib::GeometricSailCreator_noShape);

#endif // !_StbGMaker_GeometricSailCreator_noShape_Header
