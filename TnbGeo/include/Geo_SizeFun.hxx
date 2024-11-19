#pragma once
#ifndef _Geo_SizeFun_Header
#define _Geo_SizeFun_Header

#include <Global_TypeDef.hxx>

#include <memory>

namespace tnbLib
{

	template<class Point>
	class Geo_SizeFun
		: public std::enable_shared_from_this<Geo_SizeFun<Point>>
	{

		/*Private Data*/

	protected:

		// default constructor [6/5/2022 Amir]

		Geo_SizeFun() = default;


		// constructors [6/5/2022 Amir]


	public:
		virtual ~Geo_SizeFun() = default;

		typedef Point ptType;

		virtual Standard_Real Value(const Point&) const = 0;
	};
}

#endif // !_Geo_SizeFun_Header
