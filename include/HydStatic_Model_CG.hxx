#pragma once
#ifndef _HydStatic_Model_CG_Header
#define _HydStatic_Model_CG_Header

#include <HydStatic_Model_Entity.hxx>
#include <Marine_VesselParam_LCG.hxx>
#include <Marine_VesselParam_VCG.hxx>
#include <Marine_VesselParam_TCG.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		class Model_CG
			: public Model_Entity
		{

			/*Private Data*/

			marineLib::LCG theLcg_;
			marineLib::TCG theTcg_;
			marineLib::VCG theVcg_;

		public:

			Model_CG();

			const auto& LCG() const
			{
				return theLcg_;
			}

			const auto& TCG() const
			{
				return theTcg_;
			}

			const auto& VCG() const
			{
				return theVcg_;
			}

			void SetLCG(const Standard_Real theLcg)
			{
				theLcg_() = theLcg;
			}

			void SetTCG(const Standard_Real theTcg)
			{
				theTcg_() = theTcg;
			}

			void SetVCG(const Standard_Real theVcg)
			{
				theVcg_() = theVcg;
			}
		};
	}
}

#endif // !_HydStatic_Model_CG_Header
