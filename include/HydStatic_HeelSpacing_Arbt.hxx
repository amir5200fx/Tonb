#pragma once
#ifndef _HydStatic_HeelSpacing_Arbt_Header
#define _HydStatic_HeelSpacing_Arbt_Header

#include <HydStatic_HeelSpacing.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class HeelSpacing_Arbt
			: public HydStatic_HeelSpacing
		{

			/*Private Data*/


			//- private functions and operators

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int /*file_version*/)
			{
				ar & boost::serialization::base_object<HydStatic_HeelSpacing>(*this);
			}

			HeelSpacing_Arbt()
			{}

		public:

			TnbHydStatic_EXPORT HeelSpacing_Arbt
			(
				const std::shared_ptr<HydStatic_Spacing>& theSpacing
			);

			TnbHydStatic_EXPORT HeelSpacing_Arbt
			(
				std::shared_ptr<HydStatic_Spacing>&& theSpacing
			);

			TnbHydStatic_EXPORT HeelSpacing_Arbt
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const std::shared_ptr<HydStatic_Spacing>& theSpacing
			);

			TnbHydStatic_EXPORT HeelSpacing_Arbt
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				std::shared_ptr<HydStatic_Spacing>&& theSpacing
			);


			hydStcLib::CurveMakerType HeelType() const override
			{
				return hydStcLib::CurveMakerType::arbitrary;
			}

			TnbHydStatic_EXPORT Standard_Boolean IsArbitrary() const override;

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::HeelSpacing_Arbt);

#endif // !_HydStatic_HeelSpacing_Arbt_Header
