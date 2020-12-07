#pragma once
#ifndef _ShapePx_ParValue_Header
#define _ShapePx_ParValue_Header

#include <Standard_TypeDef.hxx>

#include <map>

namespace tnbLib
{

	class ShapePx_ParValue
	{

		/*Private Data*/

		std::map<Standard_Integer, Standard_Real> theValues_;

	public:

		ShapePx_ParValue()
		{}

		const auto& Values() const
		{
			return theValues_;
		}

		void SetValue(const Standard_Integer theParIndex, const Standard_Real x);

		void Remove(const Standard_Integer theParIndex);
	};
}

#endif // !_ShapePx_ParValue_Header
