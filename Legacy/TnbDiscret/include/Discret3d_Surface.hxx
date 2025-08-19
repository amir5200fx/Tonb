#pragma once
#ifndef _Discret3d_Surface_Header
#define _Discret3d_Surface_Header

#include <Discret_Module.hxx>
#include <Entity2d_PolygonFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Global_Done.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{


	// Forward Declarations [11/7/2022 Amir]

	class Discret3d_Surface_Function;
	class Discret3d_SurfaceInfo;
	class GModel_Surface;
	class GModel_Edge;
	class Cad_GeomSurface;

	class Discret3d_Surface
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Cad_GeomSurface> theSurface_;
		std::shared_ptr<Entity2d_Box> theDomain_;

		std::shared_ptr<Discret3d_SurfaceInfo> theInfo_;

		std::shared_ptr<Entity2d_Polygon> theOuter_;
		std::shared_ptr<std::vector<std::shared_ptr<Entity2d_Polygon>>> theInners_;

		std::shared_ptr<Discret3d_Surface_Function> theFun_;

		// results [11/15/2022 Amir]

		std::shared_ptr<std::vector<Pnt2d>> theCoords_;

		// Private functions and operators [11/9/2022 Amir]

	public:

		static TnbDiscret_EXPORT unsigned short verbose;

		// default constructor [11/7/2022 Amir]

		Discret3d_Surface()
		{}


		// constructors [11/7/2022 Amir]


		// public functions and operators [11/7/2022 Amir]

		const auto& Surface() const
		{
			return theSurface_;
		}

		const auto& AlgInfo() const
		{
			return theInfo_;
		}

		const auto& Outer() const
		{
			return theOuter_;
		}

		const auto& Inners() const
		{
			return theInners_;
		}

		const auto& SizeFun() const
		{
			return theFun_;
		}

		const auto& Samples() const
		{
			return theCoords_;
		}

		const auto& Domain() const
		{
			return theDomain_;
		}

		TnbDiscret_EXPORT void Perform();

		void SetSurface(const std::shared_ptr<Cad_GeomSurface>& theSurface)
		{
			theSurface_ = theSurface;
		}

		void SetDomain(const std::shared_ptr<Entity2d_Box>& theDomain)
		{
			theDomain_ = theDomain;
		}

		void SetOuter(const std::shared_ptr<Entity2d_Polygon>& thePoly)
		{
			theOuter_ = thePoly;
		}

		void SetInners(const std::shared_ptr<std::vector<std::shared_ptr<Entity2d_Polygon>>>& thePolys)
		{
			theInners_ = thePolys;
		}

		void SetInfo(const std::shared_ptr<Discret3d_SurfaceInfo>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void SetSizeFun(const std::shared_ptr<Discret3d_Surface_Function>& theFun)
		{
			theFun_ = theFun;
		}
	};
}

#endif // !_Discret3d_Surface_Header
