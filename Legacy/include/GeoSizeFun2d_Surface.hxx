#pragma once
#ifndef _GeoSizeFun2d_Surface_Header
#define _GeoSizeFun2d_Surface_Header

#include <Geo2d_SizeFunction.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Entity2d_Box.hxx>
#include <Global_Handle.hxx>

class Geom_Surface;

#include <memory>

namespace tnbLib
{

	class GeoSizeFun2d_Surface
		: public Geo2d_SizeFunction
	{

		/*Private Data*/

		Handle(Geom_Surface) theSurface_;

		std::shared_ptr<Geo3d_SizeFunction> theSize3d_;

		// private functions and operators [3/12/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor [3/12/2022 Amir]

		GeoSizeFun2d_Surface()
		{}

	public:

		// constructors [3/12/2022 Amir]

		explicit GeoSizeFun2d_Surface(const Entity2d_Box& theDomain)
			: Geo2d_SizeFunction(theDomain)
		{}

		GeoSizeFun2d_Surface
		(
			const Handle(Geom_Surface)& theSurface,
			const std::shared_ptr<Geo3d_SizeFunction>& theSize3d,
			const Entity2d_Box& theBox
		)
			: Geo2d_SizeFunction(theBox)
			, theSurface_(theSurface)
			, theSize3d_(theSize3d)
		{}


		// override functions and operators [3/12/2022 Amir]

		TnbMesh_EXPORT Standard_Real Value(const Pnt2d& theCoord) const override;

		// public functions and operators [3/12/2022 Amir]

		const auto& Surface() const
		{
			return theSurface_;
		}

		const auto& SizeFun3d() const
		{
			return theSize3d_;
		}

		void LoadSurface(const Handle(Geom_Surface)& theSurface)
		{
			theSurface_ = theSurface;
		}

		void LoadSurface(Handle(Geom_Surface)&& theSurface)
		{
			theSurface_ = std::move(theSurface);
		}

		void LoadSizeFun3d(const std::shared_ptr<Geo3d_SizeFunction>& theSize3d)
		{
			theSize3d_ = theSize3d;
		}

		void LoadSizeFun3d(std::shared_ptr<Geo3d_SizeFunction>&& theSize3d)
		{
			theSize3d_ = std::move(theSize3d);
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::GeoSizeFun2d_Surface);

#endif // !_GeoSizeFun2d_Surface_Header
