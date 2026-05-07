#pragma once
#ifndef _HydStatic_rArmCurve_TCG_Header
#define _HydStatic_rArmCurve_TCG_Header

#include <HydStatic_Entity.hxx>

namespace tnbLib
{

	namespace hydStcLib
	{

		// Forward Declarations
		class rArmCurve_LDT;

		class rArmCurve_TCG
			: public HydStatic_Entity
		{

			/*Private Data*/

			std::shared_ptr<rArmCurve_LDT> theLoad_;


			//- private functions and operators

			TNB_SERIALIZATION(TnbHydStatic_EXPORT);


		public:

			rArmCurve_TCG()
			{}

			rArmCurve_TCG
			(
				const std::shared_ptr<rArmCurve_LDT>&& theLoad
			)
				: theLoad_(std::move(theLoad))
			{}

			rArmCurve_TCG
			(
				const Standard_Integer theIndex
			)
				: HydStatic_Entity(theIndex)
			{}

			rArmCurve_TCG
			(
				const Standard_Integer theIndex,
				const word& theName
			)
				: HydStatic_Entity(theIndex, theName)
			{}

			const auto& Load() const
			{
				return theLoad_;
			}

			auto& ChangeLoad() 
			{
				return theLoad_;
			}

			void SetLoad
			(
				const std::shared_ptr<rArmCurve_LDT>&& theLoad
			)
			{
				theLoad_ = std::move(theLoad);
			}
		};
	}
}

#endif // !_HydStatic_rArmCurve_TCG_Header
