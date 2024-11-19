#pragma once
#ifndef _Geo_TessellatePolygon_Header
#define _Geo_TessellatePolygon_Header

#include <Global_Done.hxx>
#include <Global_TypeDef.hxx>

#include <memory>


namespace tnbLib
{

	// Forward Declarations [5/20/2022 Amir]
	template<class Point>
	class Entity_Polygon;

	template<class Point>
	class Geo_TessellatePolygon
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Entity_Polygon<Point>> thePoly_;


		// results [5/20/2022 Amir]

		std::shared_ptr<Entity_Polygon<Point>> theTessellated_;

	protected:

		// default constructor [5/20/2022 Amir]

		Geo_TessellatePolygon()
		{}

		// constructors [5/20/2022 Amir]

		explicit Geo_TessellatePolygon(const std::shared_ptr<Entity_Polygon<Point>>& thePoly)
			: thePoly_(thePoly)
		{}


		// protected functions and operators [5/20/2022 Amir]

		auto& TessellatedRef()
		{
			return theTessellated_;
		}

	public:

		// public functions and operators [5/20/2022 Amir]

		const auto& Polygon() const
		{
			return thePoly_;
		}

		const auto& Tessellated() const
		{
			return theTessellated_;
		}

		virtual void Tessellate(const Standard_Integer nbLevels) = 0;
	};
}

#endif // !_Geo_TessellatePolygon_Header
