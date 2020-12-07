#pragma once
#ifndef _ShapePx_Spacing_Header
#define _ShapePx_Spacing_Header

#include <ShapePx_Entity.hxx>

#include <vector>

namespace tnbLib
{

	class ShapePx_Spacing
		: public ShapePx_Entity
	{

		/*Private Data*/

		Standard_Real theLower_;
		Standard_Real theUpper_;

	protected:

		template<class... _Types>
		ShapePx_Spacing(_Types&&... _Args)
			: ShapePx_Entity(_Args...)
			, theLower_(0)
			, theUpper_(1)
		{}

	public:

		auto Lower() const
		{
			return theLower_;
		}

		auto Upper() const
		{
			return theUpper_;
		}

		void SetLower(const Standard_Real x)
		{
			theLower_ = x;
		}

		void SetUpper(const Standard_Real x)
		{
			theUpper_ = x;
		}

		Standard_Real NormalizedParameter(const Standard_Real x) const
		{
			return (x - Lower()) / (Upper() - Lower());
		}

		virtual Standard_Integer NbSections() const = 0;

		virtual std::vector<Standard_Real> Sections() const = 0;
	};
}

#endif // !_ShapePx_Spacing_Header
