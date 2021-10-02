#pragma once
#ifndef _Marine_xSectionParam_Header
#define _Marine_xSectionParam_Header

#include <Standard_TypeDef.hxx>
#include <Pnt2d.hxx>

#include <vector>
#include <math.h>

namespace tnbLib
{

	namespace marineLib
	{

		struct xSectionParam
		{
			Standard_Real x;
			Standard_Real value;

			inline auto Distance(const xSectionParam& theOther) const
			{
				auto dx = x - theOther.x;
				auto dy = value - theOther.value;
				return std::sqrt(dx*dx + dy * dy);
			}
		};

		inline auto distance(const xSectionParam& q0, const xSectionParam& q1)
		{
			return q0.Distance(q1);
		}

		inline auto point(const xSectionParam& q)
		{
			Pnt2d pt(q.x, q.value);
			return std::move(pt);
		}

		inline auto reverse_point(const xSectionParam& q)
		{
			Pnt2d pt(q.value, q.x);
			return std::move(pt);
		}
	}

	typedef std::vector<marineLib::xSectionParam> xSectParList;
}

#endif // !_Marine_xSectionParam_Header
