#pragma once
#ifndef _Marine_WaterDomain_Still_Header
#define _Marine_WaterDomain_Still_Header

#include <Marine_WaterDomain.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_Domain;
	class Marine_Body;
	class Marine_CmpSection;

	class Marine_WaterDomain_Still
		: public Marine_WaterDomain
	{

		/*Private Data*/

		Standard_Real theZ_;

	public:

		Marine_WaterDomain_Still
		(
			const std::shared_ptr<Marine_Domain>& theDomain,
			const Standard_Real theZ
		);

		Marine_WaterDomain_Still
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<Marine_Domain>& theDomain,
			const Standard_Real theZ
		);

		Marine_WaterDomain_Still
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<Marine_Domain>& theDomain,
			const Standard_Real theZ
		);

		auto Z() const
		{
			return theZ_;
		}

	};
}

#endif // !_Marine_WaterDomain_Still_Header
