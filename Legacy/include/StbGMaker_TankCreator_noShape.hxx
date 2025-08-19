#pragma once
#ifndef _StbGMaker_TankCreator_noShape_Header
#define _StbGMaker_TankCreator_noShape_Header

#include <StbGMaker_TankCreator.hxx>

namespace tnbLib
{

	namespace stbGmakerLib
	{

		class TankCreator_noShape
			: public StbGMaker_TankCreator
		{

			/*Private Data*/

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int version)
			{
				ar & boost::serialization::base_object<StbGMaker_TankCreator>(*this);
			}

		protected:

			

		public:

			//- default constructor 

			TankCreator_noShape()
			{}
			
			//- constructors

			TnbStbGMaker_EXPORT explicit TankCreator_noShape
			(
				const Standard_Integer theIndex
			);

			TnbStbGMaker_EXPORT TankCreator_noShape
			(
				const Standard_Integer theIndex, 
				const word& theName
			);


			//- public functions and operators

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

BOOST_CLASS_EXPORT_KEY(tnbLib::stbGmakerLib::TankCreator_noShape);

#endif // !_StbGMaker_TankCreator_noShape_Header
