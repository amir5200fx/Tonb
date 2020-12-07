#pragma once
#ifndef _ShapePx_GeoPatch_Header
#define _ShapePx_GeoPatch_Header

#include <Standard_Handle.hxx>
#include <ShapePx_Entity.hxx>

class Geom_Surface;

namespace tnbLib
{

	// Forward Declarations

	class ShapePx_GeoPatch
		: public ShapePx_Entity
	{

		/*Private Data*/

		Handle(Geom_Surface) theGeometry_;

	public:


		ShapePx_GeoPatch()
		{}


		ShapePx_GeoPatch(const Standard_Integer theIndex, const word& theName);

		ShapePx_GeoPatch(const Handle(Geom_Surface) theSurface);

		ShapePx_GeoPatch(const Standard_Integer theIndex, const word& theName, const Handle(Geom_Surface) theSurface);


		const auto& Geometry() const
		{
			return theGeometry_;
		}

		void SetGeometry(const Handle(Geom_Surface)& theSurf)
		{
			theGeometry_ = theSurf;
		}


	};
}

#endif // !_ShapePx_GeoPatch_Header