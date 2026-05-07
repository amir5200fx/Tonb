#pragma once
#ifndef _Geo_NormalSizeFun_Header
#define _Geo_NormalSizeFun_Header

#include <Geo_SizeFun.hxx>

namespace tnbLib
{

	template<class Point>
	class Geo_NormalSizeFun
		: public Geo_SizeFun<Point>
	{

		/*Private Data*/

	public:

		using typename Geo_SizeFun<Point>::ptType;

		// default constructor [6/5/2022 Amir]

		Geo_NormalSizeFun()
		{}

		// constructors [6/5/2022 Amir]


		// override functions and operators [6/5/2022 Amir]

		Standard_Real Value(const Point&) const override
		{
			return 1.0;
		}

		// public functions and operators [6/5/2022 Amir]
	};
}

#endif // !_Geo_NormalSizeFun_Header
