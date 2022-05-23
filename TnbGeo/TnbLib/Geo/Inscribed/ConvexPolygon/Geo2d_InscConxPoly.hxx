#pragma once
#ifndef _Geo2d_InscConxPoly_Header
#define _Geo2d_InscConxPoly_Header

#include <Entity2d_PolygonFwd.hxx>
#include <Geo_Module.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	class Geo2d_InscConxPoly
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Entity2d_Polygon> thePolygon_;

		Standard_Real theTol_;

		// results [5/19/2022 Amir]

		std::shared_ptr<Entity2d_Polygon> theHull_;


		// private functions and operators [5/19/2022 Amir]

		auto& HullRef()
		{
			return theHull_;
		}

		static TnbGeo_EXPORT std::shared_ptr<Entity2d_Polygon> 
			CreatePolygon
			(
				const std::vector<Pnt2d>&, 
				const std::vector<Standard_Integer>& theIds
			);

	public:


		static TnbGeo_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		// default constructor [5/19/2022 Amir]

		Geo2d_InscConxPoly()
			: theTol_(DEFAULT_TOLERANCE)
		{}


		// constructors [5/19/2022 Amir]

		Geo2d_InscConxPoly
		(
			const std::shared_ptr<Entity2d_Polygon>& thePoly,
			const Standard_Real theTol
		)
			: thePolygon_(thePoly)
			, theTol_(theTol)
		{}

		// public functions and operators [5/19/2022 Amir]

		auto Tolerance() const
		{
			return theTol_;
		}

		const auto& Polygon() const
		{
			return thePolygon_;
		}

		const auto& ConvexHull() const
		{
			return theHull_;
		}

		TnbGeo_EXPORT void Perform();

		void SetPolygon(const std::shared_ptr<Entity2d_Polygon>& thePoly)
		{
			thePolygon_ = thePoly;
		}

		void SetPolygon(std::shared_ptr<Entity2d_Polygon>&& thePoly)
		{
			thePolygon_ = std::move(thePoly);
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTol_ = theTol;
		}
	};
}

#endif // !_Geo2d_InscConxPoly_Header
