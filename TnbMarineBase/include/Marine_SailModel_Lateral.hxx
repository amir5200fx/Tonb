#pragma once
#ifndef _Marine_SailModel_Lateral_Header
#define _Marine_SailModel_Lateral_Header

#include <Marine_PlnSailModel.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;

	namespace marineLib
	{

		class SailModel_Lateral
			: public Marine_PlnSailModel
		{

			/*Private Data*/

			std::shared_ptr<Cad2d_Plane> thePlane_;

		public:

			SailModel_Lateral(const std::shared_ptr<Cad2d_Plane>& thePlane);

			SailModel_Lateral(std::shared_ptr<Cad2d_Plane>&& thePlane);

			SailModel_Lateral(const Standard_Integer theIndex, const std::shared_ptr<Cad2d_Plane>& thePlane);

			SailModel_Lateral(const Standard_Integer theIndex, std::shared_ptr<Cad2d_Plane>&& thePlane);

			SailModel_Lateral(const Standard_Integer theIndex, const word& theName, const std::shared_ptr<Cad2d_Plane>& thePlane);

			SailModel_Lateral(const Standard_Integer theIndex, const word& theName, std::shared_ptr<Cad2d_Plane>&& thePlane);


			const auto& Plane() const
			{
				return thePlane_;
			}


		};
	}
}

#endif // !_Marine_SailModel_Lateral_Header
