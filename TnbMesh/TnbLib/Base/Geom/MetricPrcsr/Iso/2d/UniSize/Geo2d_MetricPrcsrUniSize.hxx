#pragma once
#ifndef _Geo2d_MetricPrcsrUniSize_Header
#define _Geo2d_MetricPrcsrUniSize_Header

#include <Geo_MetricPrcsr.hxx>
#include <GeoSizeFun2d_Uniform.hxx>
#include <Geo2d_MetricPrcsrUniSizeFwd.hxx>
#include <Vec2d.hxx>

namespace tnbLib
{

	template<>
	class Geo_MetricPrcsr<GeoSizeFun2d_Uniform, void>
		: public std::enable_shared_from_this<Geo_MetricPrcsr<GeoSizeFun2d_Uniform, void>>
	{

		/*Private Data*/

		std::shared_ptr<GeoSizeFun2d_Uniform> theSizeFunction_;

		Standard_Real theDimSize_;


		// private functions and operators [3/4/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theSizeFunction_;
			ar & theDimSize_;
		}

	protected:

		

	public:

		static TnbMesh_EXPORT const std::string extension;


		// default constructor [3/4/2022 Amir]

		Geo_MetricPrcsr()
			: theDimSize_(RealLast())
		{}

		// constructors [3/4/2022 Amir]

		Geo_MetricPrcsr
		(
			const std::shared_ptr<GeoSizeFun2d_Uniform>& theSizeFun,
			const Standard_Real theDimSize
		)
			: theSizeFunction_(theSizeFun)
			, theDimSize_(theDimSize)
		{}

		// public functions and operators [3/4/2022 Amir]

		const auto& SizeFunction() const
		{
			return theSizeFunction_;
		}

		TnbMesh_EXPORT Entity2d_Box BoundingBox() const;

		auto DimSize() const
		{
			return theDimSize_;
		}

		inline Pnt2d CalcCentre
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		) const;

		virtual Standard_Real CalcElementSize
		(
			const Pnt2d& theCoord
		) const;

		inline Standard_Real CalcDistance
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		) const;

		inline Standard_Real CalcSquareDistance
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		) const;

		inline Standard_Real CalcUnitDistance
		(
			const Pnt2d& theP0,
			const Pnt2d& theP1
		) const;

		inline Standard_Real Integrand
		(
			const Pnt2d& thePoint,
			const Pnt2d& theVector
		) const;

		inline Standard_Real Integrand
		(
			const Pnt2d& thePoint,
			const Vec2d& theVector
		) const;

		inline Standard_Real IntegrandPerSize
		(
			const Pnt2d& thePoint,
			const Pnt2d& theVector
		) const;

		inline Standard_Real IntegrandPerSize
		(
			const Pnt2d& thePoint,
			const Vec2d& theVector
		) const;

		void SetDimSize(const Standard_Real theSize)
		{
			theDimSize_ = theSize;
		}


	};
}

#include <Geo2d_MetricPrcsrUniSizeI.hxx>

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo2d_MetricPrcsrUniSize);

#endif // !_Geo2d_MetricPrcsrUniSize_Header
