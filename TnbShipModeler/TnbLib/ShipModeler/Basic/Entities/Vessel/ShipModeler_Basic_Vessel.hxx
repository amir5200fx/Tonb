#pragma once
#ifndef _ShipModeler_Basic_Vessel_Header
#define _ShipModeler_Basic_Vessel_Header

#include <ShipModeler_Basic_Entity.hxx>

#include <vector>

namespace tnbLib
{

	namespace shipModelerLib
	{

		// Forward Declarations
		class Basic_Hull;
		class Basic_Sail;
		class Basic_Tank;

		class Basic_Vessel
			: public Basic_Entity
		{

			/*Private Data*/

			std::vector<std::shared_ptr<Basic_Tank>> theTanks_;
			std::vector<std::shared_ptr<Basic_Sail>> theSails_;

			std::shared_ptr<Basic_Hull> theHull_;


			//- private functions and operators

			auto& ChangeTanks()
			{
				return theTanks_;
			}

			auto& ChangeSails()
			{
				return theSails_;
			}

			auto& ChangeHull()
			{
				return theHull_;
			}

		public:

			template<class... _Types>
			Basic_Vessel(_Types&&... _Args)
				: Basic_Entity(_Args...)
			{}

			auto NbTanks() const
			{
				return (Standard_Integer)theTanks_.size();
			}

			auto NbSails() const
			{
				return (Standard_Integer)theSails_.size();
			}

			const auto& Hull() const
			{
				return theHull_;
			}

			const auto& Tanks() const
			{
				return theTanks_;
			}

			const auto& Sails() const
			{
				return theSails_;
			}

		};
	}
}

#endif // !_ShipModeler_Basic_Vessel_Header
