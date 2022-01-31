#pragma once
#ifndef _Cad2d_SearchCrv_Header
#define _Cad2d_SearchCrv_Header

#include <Cad2d_Module.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Standard_TypeDef.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [1/26/2022 Amir]
	class Pln_Curve;
	class Pln_Edge;

	class Cad2d_SearchCrv
	{

		/*Private Data*/

	protected:

		// default constructor [1/26/2022 Amir]

		Cad2d_SearchCrv()
		{}

		// constructors [1/26/2022 Amir]


	public:

		// public functions and operators [1/26/2022 Amir]

		virtual Standard_Integer NbCurves() const = 0;

		virtual std::vector<std::shared_ptr<Pln_Edge>> Find(const std::shared_ptr<Pln_Edge>&) const = 0;
		virtual std::vector<std::shared_ptr<Pln_Edge>> AllCurves() const = 0;
	};
}

#endif // !_Cad2d_SearchCrv_Header
