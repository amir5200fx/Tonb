#pragma once
#ifndef _ShapePx_Spacing_Header
#define _ShapePx_Spacing_Header

#include <ShapePx_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Limits;

	class ShapePx_Spacing
		: public ShapePx_Entity
	{

		/*Private Data*/

		std::shared_ptr<SectPx_Limits> theLimits_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbShapePx_EXPORT);


	protected:

		ShapePx_Spacing()
		{}

		TnbShapePx_EXPORT ShapePx_Spacing
		(
			const std::shared_ptr<SectPx_Limits>& theLimits
		);

		TnbShapePx_EXPORT ShapePx_Spacing
		(
			const Standard_Integer theIndex, 
			const word& theName, 
			const std::shared_ptr<SectPx_Limits>& theLimits
		);

	public:

		const auto& Limits() const
		{
			return theLimits_;
		}

		TnbShapePx_EXPORT Standard_Real Lower() const;

		TnbShapePx_EXPORT Standard_Real Upper() const;

		Standard_Real NormalizedParameter(const Standard_Real x) const
		{
			return (x - Lower()) / (Upper() - Lower());
		}

		virtual Standard_Integer NbSections() const = 0;

		virtual std::vector<Standard_Real> Sections() const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::ShapePx_Spacing);

#endif // !_ShapePx_Spacing_Header
