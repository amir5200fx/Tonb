#pragma once
#ifndef _ShapePx_UniformSpacing_Header
#define _ShapePx_UniformSpacing_Header

#include <ShapePx_Spacing.hxx>

namespace tnbLib
{

	class ShapePx_UniformSpacing
		: public ShapePx_Spacing
	{

		/*Private Data*/

		Standard_Integer theNbSections_;

	public:

		ShapePx_UniformSpacing()
		{}

		ShapePx_UniformSpacing(const Standard_Integer theIndex, const word& theName);


		Standard_Integer NbSections() const override
		{
			return theNbSections_;
		}

		std::vector<Standard_Real> Sections() const override;
	};
}

#endif // !_ShapePx_UniformSpacing_Header
