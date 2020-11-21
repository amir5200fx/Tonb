#pragma once
#ifndef _StbGMaker_HullCreator_noShape_Header
#define _StbGMaker_HullCreator_noShape_Header

#include <StbGMaker_HullCreator.hxx>

namespace tnbLib
{

	namespace stbGmakerLib
	{

		class HullCreator_noShape
			: public StbGMaker_HullCreator
		{

			/*Private Data*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<StbGMaker_HullCreator>(*this);
			}

		public:

			TnbStbGMaker_EXPORT HullCreator_noShape();

			TnbStbGMaker_EXPORT HullCreator_noShape
			(
				const Standard_Integer theIndex,
				const word& theName
			);

			Standard_Boolean HasShape() const override
			{
				return Standard_False;
			}

			TnbStbGMaker_EXPORT Standard_Integer
				CreateWorkingPlane
				(
					const Standard_Real x
				) override;

			TnbStbGMaker_EXPORT void ExportAs
			(
				std::shared_ptr<Marine_Model>& theModel
			) const override;
		};
	}
}

#endif // !_StbGMaker_HullCreator_noShape_Header
