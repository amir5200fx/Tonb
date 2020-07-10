#pragma once
#ifndef _Marine_AreaSailModel_Header
#define _Marine_AreaSailModel_Header

#include <Pnt2d.hxx>
#include <Marine_SailModel.hxx>

namespace tnbLib
{

	class Marine_AreaSailModel
		: public Marine_SailModel
	{

		/*Private Data*/

		Pnt2d theCentre_;

	protected:

		Marine_AreaSailModel(const Pnt2d& theCentre)
			: theCentre_(theCentre)
		{}

		Marine_AreaSailModel(Pnt2d&& theCentre)
			: theCentre_(std::move(theCentre))
		{}

		Marine_AreaSailModel
		(
			const Standard_Integer theIndex, 
			const Pnt2d& theCentre
		);

		Marine_AreaSailModel
		(
			const Standard_Integer theIndex,
			Pnt2d&& theCentre
		);

		Marine_AreaSailModel
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const Pnt2d& theCentre
		);

		Marine_AreaSailModel
		(
			const Standard_Integer theIndex, 
			const word& theName,
			Pnt2d&& theCentre
		);

	public:

		const auto& Centre() const
		{
			return theCentre_;
		}
	};
}

#endif // !_Marine_AreaSailModel_Header
