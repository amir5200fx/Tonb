#pragma once
#ifndef _ShipModeler_Basic_WPlane_Header
#define _ShipModeler_Basic_WPlane_Header

#include <ShipModeler_Basic_Entity.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Modeler;

	namespace shipModelerLib
	{

		class Basic_WPlane
			: public Basic_Entity
		{

			/*Private Data*/

			std::shared_ptr<Cad2d_Modeler> theModeler_;

			Standard_Real theX_;


			//- private functions and operators

			void Constructor();

		public:

			/*template<class... _Types>
			Basic_WPlane(_Types&&... _Args)
				: Basic_Entity(_Args...)
			{
				Constructor();
			}*/

			template<class... _Types>
			Basic_WPlane(const Standard_Real theX, _Types&&... _Args)
				: Basic_Entity(_Args...)
				, theX_(theX)
			{
				Constructor();
			}

			const auto& Modify() const
			{
				return theModeler_;
			}

			void SetX(const Standard_Real theX)
			{
				theX_ = theX;
			}
		};
	}
}

#endif // !_ShipModeler_Basic_WPlane_Header
