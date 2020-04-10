#pragma once
#ifndef _HydroStatic_ModelMaker_Header
#define _HydroStatic_ModelMaker_Header

#include <Standard_TypeDef.hxx>

#include <memory>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class HsModeler_Tank;
	class HsModeler_Sail;
	class HsModeler_Hull;

	class HydroStatic_ModelMaker
	{

		/*Private Data*/

		std::map<Standard_Integer, std::shared_ptr<HsModeler_Hull>>
			theHulls_;

		std::map<Standard_Integer, std::shared_ptr<HsModeler_Hull>>
			theSails_;

		std::map<Standard_Integer, std::shared_ptr<HsModeler_Hull>>
			theTanks_;

	public:

		HydroStatic_ModelMaker();

		const auto& Hulls() const
		{
			return theHulls_;
		}

		const auto& Sails() const
		{
			return theSails_;
		}

		const auto& Tanks() const
		{
			return theTanks_;
		}
	};
}

#endif // !_HydroStatic_ModelMaker_Header

