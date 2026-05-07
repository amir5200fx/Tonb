#pragma once
#ifndef _Mesh_RegionPlane_Header
#define _Mesh_RegionPlane_Header

#include <Global_Indexed.hxx>
#include <Global_Named.hxx>
#include <OFstream.hxx>
#include <TnbError.hxx>
#include <Mesh_RegionPlaneTraits.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	template<class CurveType, class SizeFun, class MetricFun>
	class Mesh_PlnCurve;

	template<class PlnCurve>
	class Mesh_PlnWire;

	template<class CurveType, class SizeFun, class MetricFun = void>
	class Mesh_RegionPlane
		: public Global_Indexed
		, public Global_Named
	{

	public:

		typedef Mesh_PlnCurve<CurveType, SizeFun, MetricFun>
			plnCurveType;

		typedef typename Mesh_RegionPlaneTraits<CurveType>::plnType
			plnType;

		typedef Mesh_PlnWire<plnCurveType> plnWireType;

		typedef std::shared_ptr<plnWireType> outer;
		typedef std::shared_ptr<std::vector<std::shared_ptr<plnWireType>>> inner;
		typedef std::vector<std::shared_ptr<plnWireType>> wireList;

		typedef SizeFun sizeFun;
		typedef MetricFun metricFun;

	private:

		/*Private Data*/

		std::shared_ptr<plnType> thePlane_;

		outer theOuter_;
		inner theInner_;


		//- default constructor

		Mesh_RegionPlane()
		{}


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& /*ar*/, const unsigned int /*file_version*/)
		{
			Info << "WARNING! This function is not supposed to be called." << endl;
			NotImplemented;
		}

	public:

		//- default constructor


		//- constructors

		Mesh_RegionPlane
		(
			const std::shared_ptr<plnType>& thePlane,
			const outer& theOuter,
			const inner& theInner = nullptr
		)
			: thePlane_(thePlane)
			, theOuter_(theOuter)
			, theInner_(theInner)
		{}

		Mesh_RegionPlane
		(
			const Standard_Integer theIndex,
			const word& theName,
			const std::shared_ptr<plnType>& thePlane,
			const outer& theOuter,
			const inner& theInner = nullptr
		)
			: Global_Indexed(theIndex)
			, Global_Named(theName)
			, thePlane_(thePlane)
			, theOuter_(theOuter)
			, theInner_(theInner)
		{}


		//- public functions and operators

		const auto& Plane() const
		{
			return thePlane_;
		}

		auto HasHole() const
		{
			return (Standard_Boolean)theInner_;
		}

		auto NbHoles() const
		{
			if (!HasHole()) return 0;
			return (Standard_Integer)theInner_->size();
		}

		const auto& Inner() const
		{
			return theInner_;
		}

		const auto& Outer() const
		{
			return theOuter_;
		}

		void SetPlane(const std::shared_ptr<plnType>& thePlane)
		{
			thePlane_ = thePlane;
		}

		void RetrieveWiresTo(wireList& theWires) const;

		void ExportToPlt(OFstream& File) const;


		//- Static functions and operators

		template<class WireType>
		static std::shared_ptr<plnWireType>
			MakeMeshWire
			(
				const WireType& theWire
			);

		static std::shared_ptr<Mesh_RegionPlane>
			MakePlane
			(
				const std::shared_ptr<plnType>& thePlane
			);

		template<class PlnType>
		static std::shared_ptr<PlnType> MakeOrignPlane(const std::shared_ptr<Mesh_RegionPlane>&);

	};
}

#include <Mesh_RegionPlaneI.hxx>

#endif // !_Mesh_RegionPlane_Header
