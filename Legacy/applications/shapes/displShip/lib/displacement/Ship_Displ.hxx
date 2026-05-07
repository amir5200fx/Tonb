#pragma once
#ifndef _Ship_Displ_Header
#define _Ship_Displ_Header

#include <Ship_Params.hxx>
#include <Ship_xParams.hxx>
#include <Ship_Profiles.hxx>
#include <Cad_GeomSurface.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	class Ship_Displ
		: public Global_Done
	{

		/*Private Data*/

		Ship_Params theParameters_;
		Ship_xParams theXParams_;
		
		Ship_Profiles theProfiles_;

		// result [11/1/2022 Amir]

		std::shared_ptr<Cad_GeomSurface> thePatch_;


		// Private functions and operators [11/1/2022 Amir]

		auto& PatchRef()
		{
			return thePatch_;
		}

		auto& XParamsRef()
		{
			return theXParams_;
		}

		auto& ProfilesRef()
		{
			return theProfiles_;
		}

		void CalcxXSections();
		void CalcxYSections();

	public:

		// default constructor [11/1/2022 Amir]

		Ship_Displ()
		{}


		// constructors [11/1/2022 Amir]


		// public functions and operators [11/1/2022 Amir]


		const auto& Parameters() const
		{
			return theParameters_;
		}

		auto& ParametersRef()
		{
			return theParameters_;
		}

		const auto& XParams() const
		{
			return theXParams_;
		}

		const auto& Profiles() const
		{
			return theProfiles_;
		}

		const auto& Patch() const
		{
			return thePatch_;
		}

		void Perform();
	};
}

#endif // !_Ship_Displ_Header
