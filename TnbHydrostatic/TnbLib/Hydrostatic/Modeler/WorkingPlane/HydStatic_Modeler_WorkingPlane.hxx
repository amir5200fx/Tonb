#pragma once
#ifndef _HydStatic_Modeler_WorkingPlane_Header
#define _HydStatic_Modeler_WorkingPlane_Header

#include <HydStatic_Modeler_Entity.hxx>

#include <map>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;

	namespace hydStcLib
	{

		class Modeler_WorkingPlane
			: public Modeler_Entity
		{

			/*Private Data*/

			std::map<Standard_Integer, std::shared_ptr<Pln_Curve>> theCurves_;


		protected:

			Modeler_WorkingPlane();

			Modeler_WorkingPlane(const Standard_Integer theIndex);

			Modeler_WorkingPlane(const Standard_Integer theIndex, const word& theName);

		public:


			auto NbCurves() const
			{
				return (Standard_Integer)theCurves_.size();
			}

			const auto& Curves() const
			{
				return theCurves_;
			}
		};
	}
}

#endif // !_HydStatic_Modeler_WorkingPlane_Header
