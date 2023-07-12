#pragma once
#ifndef _VoyageGeo_Path_Header
#define _VoyageGeo_Path_Header

#include <Pnt2d.hxx>
#include <Dir2d.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations [7/11/2023 Payvand]
	class VoyageGeo_SizeFun;
	class VoyageGeo_MetricFun;

	class VoyageGeo_Path
	{

		/*Private Data*/

	protected:

		// default constructor [7/10/2023 Payvand]

		VoyageGeo_Path()
		{}

		// constructors [7/10/2023 Payvand]

	public:

		// Public functions and operators [7/10/2023 Payvand]

		virtual Pnt2d Value(const Standard_Real) const = 0;
		virtual Dir2d CalcNormal(const Standard_Real) const = 0;

		virtual Pnt2d Start() const = 0;
		virtual Pnt2d End() const = 0;

		virtual std::vector<Standard_Real> Discrete(const std::shared_ptr<VoyageGeo_SizeFun>&, const std::shared_ptr<VoyageGeo_MetricFun>&) const = 0;

	};

}

#endif // !_VoyageGeo_Path_Header
