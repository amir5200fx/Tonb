#pragma once
#ifndef _Aft_MetricPrcsr_Header
#define _Aft_MetricPrcsr_Header

#include <Aft_MetricPrcsrIdentifier.hxx>
#include <Mesh_Module.hxx>
#include <Geo_MetricPrcsr.hxx>
#include <Entity_Box.hxx>
#include <Aft_TypeTraits.hxx>
#include <Aft2d_EdgeFwd.hxx>
#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Aft3d_FacetFwd.hxx>
#include <Aft3d_FacetAnIsoFwd.hxx>
#include <Aft_MetricPrcsrAnIso_Info.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Aft_MetricPrcsrAnIso_Info;
	class Entity2d_Eigen;

	template<class FrontType, class SizeFun, class MetricFun = void>
	class Aft_MetricPrcsr
		: public Geo_MetricPrcsr<SizeFun, MetricFun>
		, public Aft_MetricPrcsrIdentifier<FrontType>
	{

	public:

		typedef Aft_MetricPrcsrAnIso_Info info;
		typedef Geo_MetricPrcsr<SizeFun, MetricFun> base;
		typedef FrontType frontType;

		typedef typename SizeFun::ptType Point;
		typedef typename base::info integInfo;
		typedef typename base::metricType metricType;

		typedef typename sub_type<frontType, (int)frontType::rank - 1>::type subFront;

		typedef Entity_Box<Point> box;

		using base::CalcElementSize;
		using base::CalcDistance;
		using base::CalcSquareDistance;

	private:

		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;

		/*Private Data*/

		std::shared_ptr<info> theInfo_;



		// Private functions and operators [11/24/2021 Amir]

		Point CorrEffRegion
		(
			const Point& theCentre,
			const Point& theP,
			const Standard_Real theRadius
		) const;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			/*ar & boost::serialization::base_object<base>(*this);
			ar & theInfo_;*/

			tnbLib::Info << "This function is not supposed to be called!" << endl;
			NotImplemented;
		}

	protected:

		// default constructor [11/24/2021 Amir]

		Aft_MetricPrcsr()
		{}

		// Protected functions and operators [10/17/2022 Amir]

		void OverrideInfo(const std::shared_ptr<info>& theInfo)
		{
			theInfo_ = theInfo;
		}

	public:


		// Public functions and operators [11/24/2021 Amir]

		Aft_MetricPrcsr
		(
			const std::shared_ptr<info>& theInfo
		)
			: base(theInfo)
			, theInfo_(theInfo)
		{}

		Aft_MetricPrcsr
		(
			const std::shared_ptr<SizeFun>& theSizeFunction,
			const std::shared_ptr<MetricFun>& theMetricFunction,
			const std::shared_ptr<info>& theInfo
		)
			: base(theSizeFunction, theMetricFunction, theInfo)
			, theInfo_(theInfo)
		{}

		Aft_MetricPrcsr
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SizeFun>& theSizeFunction,
			const std::shared_ptr<MetricFun>& theMetricFunction,
			const std::shared_ptr<info>& theInfo
		)
			: base(theIndex, theName, theSizeFunction, theMetricFunction, theInfo)
			, theInfo_(theInfo)
		{}


		// Public functions and operators [11/24/2021 Amir]

		const std::shared_ptr<info>& Info() const
		{
			return theInfo_;
		}

		Standard_Real Oriented(const Point& thePt, const frontType& theFront) const;
		Standard_Real CalcDistance(const Point& thePt, const frontType& theFront) const;
		Standard_Real CalcSquareDistance(const Point& thePt, const frontType& theFront) const;
		
		virtual Standard_Real CalcElementSize(const std::shared_ptr<frontType>& theFront) const;

		template<class U = Standard_Real>
		resolvedType<is_three_dimension<(int)Point::dim>::value, U> CalcDistance(const Point& thePt, const subFront& theEntity) const;

		template<class U = Standard_Real>
		resolvedType<is_three_dimension<(int)Point::dim>::value, U> CalcSquareDistance(const Point& thePt, const subFront& theEntity) const;

		template<class U = Standard_Real>
		resolvedType<is_three_dimension<(int)Point::dim>::value, U> CalcDistance(const subFront& theEntity0, const subFront& theEntity1) const;

		template<class U = Standard_Real>
		resolvedType<is_three_dimension<(int)Point::dim>::value, U> CalcSquareDistance(const subFront& theEntity0, const subFront& theEntity1) const;

		Point CalcCentreOf(const frontType& theFront) const;

		virtual box CalcSearchRegion(const Standard_Real theRadius, const metricType& theMetric, const Point& theCentre) const;
		virtual box CalcSearchRegion(const Standard_Real theRadius, const Point& theCentre, const frontType& theFront) const;
		virtual box CalcSearchRegion(const Standard_Real theRadius, const frontType& theFront) const;
		virtual box CalcEffectiveFront(const Standard_Real theRadius, const Point& theCentre, const frontType& theFront) const;

		//metricType CalcEffectiveMetric(const Point& theP0, const Point& theP1) const;
	};

	TnbMesh_EXPORT extern std::shared_ptr<Entity2d_Eigen> mesh2d_aft_metric_prcsr_eigen_calculator;


	template<class FrontType, class SizeFun>
	class Aft_MetricPrcsr<FrontType, SizeFun, void>
		: public Geo_MetricPrcsr<SizeFun, void>
	{

	public:

		typedef Geo_MetricPrcsr<SizeFun, void> base;
		typedef FrontType frontType;

		typedef typename SizeFun::ptType Point;
		typedef typename base::info info;

		typedef typename sub_type<frontType, (int)frontType::rank - 1>::type subFront;

		typedef Entity_Box<Point> box;

		using base::CalcElementSize;
		using base::CalcDistance;
		using base::CalcSquareDistance;

	private:

		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;

		/*Private Data*/

		std::shared_ptr<info> theInfo_;


		// Private functions and operators [11/24/2021 Amir]


		friend class boost::serialization::access;


		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			/*ar & boost::serialization::base_object<base>(*this);
			ar & theInfo_;*/
			tnbLib::Info << "This functions is not supposed to be called!" << endl;
			NotImplemented;
		}

	protected:

		// default constructor [11/24/2021 Amir]


		Aft_MetricPrcsr()
		{}

	public:


		// constructors [11/24/2021 Amir]

		Aft_MetricPrcsr
		(
			const std::shared_ptr<info>& theInfo
		)
			: base(theInfo)
		{}

		Aft_MetricPrcsr
		(
			const std::shared_ptr<info>& theInfo,
			const std::shared_ptr<SizeFun>& theFun
		)
			: base(theInfo, theFun)
		{}

		Aft_MetricPrcsr
		(
			const std::shared_ptr<SizeFun>& theFun,
			const std::shared_ptr<info>& theInfo
		)
			: base(theFun, theInfo)
		{}

		Aft_MetricPrcsr
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<SizeFun>& theFun,
			const std::shared_ptr<info>& theInfo
		)
			: base(theIndex, theName, theFun, theInfo)
		{}


		// Public functions and operators [11/24/2021 Amir]

		Standard_Real Oriented(const Point& thePt, const frontType& theFront) const;
		Standard_Real CalcDistance(const Point& thePt, const frontType& theFront) const;
		Standard_Real CalcSquareDistance(const Point& thePt, const frontType& theFront) const;

		virtual Standard_Real CalcElementSize(const std::shared_ptr<frontType>& theFront) const;

		template<class U = Standard_Real>
		resolvedType<is_three_dimension<(int)Point::dim>::value, U> CalcDistance(const Point& thePt, const subFront& theEntity) const;

		template<class U = Standard_Real>
		resolvedType<is_three_dimension<(int)Point::dim>::value, U> CalcSquareDistance(const Point& thePt, const subFront& theEntity) const;

		template<class U = Standard_Real>
		resolvedType<is_three_dimension<(int)Point::dim>::value, U> CalcDistance(const subFront& theEntity0, const subFront& theEntity1) const;

		template<class U = Standard_Real>
		resolvedType<is_three_dimension<(int)Point::dim>::value, U> CalcSquareDistance(const subFront& theEntity0, const subFront& theEntity1) const;

		Point CalcCentreOf(const frontType& theFront) const;

		virtual box CalcSearchRegion(const Standard_Real theRadius, const Point& theCentre) const;
		virtual box CalcSearchRegion(const Standard_Real theRadius, const Point& theCentre, const frontType& theFront) const;
		virtual box CalcSearchRegion(const Standard_Real theRadius, const frontType& theFront) const;
		virtual box CalcEffectiveFront(const Standard_Real theRadius, const Point& theCentre, const frontType& theFront) const;
	};
}

#include <Aft_MetricPrcsrI.hxx>

#endif // !_Aft_MetricPrcsr_Header
