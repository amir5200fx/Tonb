#pragma once
#ifndef _HsSection_WaterLine_Header
#define _HsSection_WaterLine_Header

#include <HsSection_Wetted.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;

	class HsSection_WaterLine
		: public HsSection_Wetted
	{

		/*Private Data*/

	public:

		HsSection_WaterLine();


		Standard_Boolean IsWaterLine() const override
		{
			return Standard_True;
		}

		const std::shared_ptr<Pln_Curve>& WaterLine() const;
	};
}

#endif // !_HsSection_WaterLine_Header
