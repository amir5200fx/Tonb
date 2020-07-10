#pragma once
#ifndef _Marine_Model_ProfileAreaSail_Header
#define _Marine_Model_ProfileAreaSail_Header

#include <Standard_Handle.hxx>
#include <Marine_AreaSailModel.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Geo_ProfileFun;

	namespace marineLib
	{

		class Model_ProfileAreaSail
			: public Marine_AreaSailModel
		{

			/*Private Data*/

			std::shared_ptr<Geo_ProfileFun> theProfile_;

		public:

			Model_ProfileAreaSail
			(
				const std::shared_ptr<Geo_ProfileFun>& theFun, 
				const Pnt2d& theCentre
			);

			Model_ProfileAreaSail
			(
				std::shared_ptr<Geo_ProfileFun>&& theFun,
				Pnt2d&& theCentre
			);

			Model_ProfileAreaSail
			(
				const Standard_Integer theIndex,
				const word& theName, 
				const std::shared_ptr<Geo_ProfileFun>& theFun, 
				const Pnt2d& theCentre
			);

			Model_ProfileAreaSail
			(
				const Standard_Integer theIndex, 
				const word& theName, 
				std::shared_ptr<Geo_ProfileFun>&& theFun, 
				Pnt2d&& theCentre
			);


			const auto& Profile() const
			{
				return theProfile_;
			}
		};
	}
}

#endif // !_Marine_Model_ProfileAreaSail_Header
