#pragma once
#ifndef _HydStatic_HeelSpacing_Stb_Header
#define _HydStatic_HeelSpacing_Stb_Header

#include <HydStatic_HeelSpacing.hxx>

#include <vector>

namespace tnbLib
{

	namespace hydStcLib
	{

		class HeelSpacing_Stb
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

		public:

			HeelSpacing_Stb()
			{}

			TnbHydStatic_EXPORT HeelSpacing_Stb
			(
				const Standard_Integer theIndex, 
				const word& theName
			);

			hydStcLib::CurveMakerType HeelType() const override
			{
				return hydStcLib::CurveMakerType::starboard;
			}

			TnbHydStatic_EXPORT Standard_Boolean IsStarboard() const override;

			TnbHydStatic_EXPORT void Perform(const Standard_Integer theNbHeels);

			TnbHydStatic_EXPORT void Perform(const std::vector<Standard_Real>& theHeels);

		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::hydStcLib::HeelSpacing_Stb);

#endif // !_HydStatic_HeelSpacing_Stb_Header
