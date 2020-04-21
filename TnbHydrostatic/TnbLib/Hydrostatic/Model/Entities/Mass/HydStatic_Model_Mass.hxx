#pragma once
#ifndef _HydStatic_Model_Mass_Header
#define _HydStatic_Model_Mass_Header

#include <Marine_VesselParam_MASS.hxx>
#include <HydStatic_Model_CG.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class Model_Mass
			: public Model_Entity
		{

			/*Private Data*/

			std::shared_ptr<Model_CG> theCg_;

			marineLib::MASS theMass_;

		public:

			Model_Mass();

			const auto& CG() const
			{
				return theCg_;
			}

			const auto& Mass() const
			{
				return theMass_;
			}

			void LoadCG
			(
				const std::shared_ptr<Model_CG>& theCg
			)
			{
				theCg_ = theCg;
			}

			void SetMass
			(
				const Standard_Real theMass
			)
			{
				theMass_() = theMass;
			}
		};
	}
}

#endif // !_HydStatic_Model_Mass_Header
