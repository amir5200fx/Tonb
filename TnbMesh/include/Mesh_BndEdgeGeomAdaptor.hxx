#pragma once
#ifndef _Mesh_BndEdgeGeomAdaptor_Header
#define _Mesh_BndEdgeGeomAdaptor_Header

#include <Mesh_EntityAdaptorM.hxx>
#include <Mesh_BndEdge_Position.hxx>

#define MESH_MODULE TnbMesh_EXPORT

namespace tnbLib
{

	Mesh_EntityToEntityAdaptor(BndEdge, Surface, SurfType);

	template<class CurveType>
	class Mesh_BndEdgeGeomAdaptorBase
	{

		/*Private Data*/

		std::weak_ptr<CurveType> theCurve_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		Mesh_BndEdgeGeomAdaptorBase()
		{}


		//- public functions and operators

		const auto& Curve() const
		{
			return theCurve_;
		}

		void SetCurve
		(
			const std::weak_ptr<CurveType>& theCurve
		)
		{
			theCurve_ = theCurve;
		}

	};

	template<class CurveType, class SurfType, Mesh_BndEdge_Position POS = Mesh_BndEdge_Position_Segment>
	class Mesh_BndEdgeGeomAdaptor
		: public Mesh_BndEdgeToSurfaceAdaptor<SurfType>
		, public Mesh_BndEdgeGeomAdaptorBase<CurveType>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh_BndEdgeToSurfaceAdaptor<SurfType>>(*this);
			ar & boost::serialization::base_object<Mesh_BndEdgeGeomAdaptorBase<CurveType>>(*this);
		}

	public:

		Mesh_BndEdgeGeomAdaptor()
		{}


		//- public functions and operators

	};

	template<class CurveType>
	class Mesh_BndEdgeGeomAdaptor<CurveType, void, Mesh_BndEdge_Position_Segment>
		: public Mesh_BndEdgeGeomAdaptorBase<CurveType>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh_BndEdgeGeomAdaptorBase<CurveType>>(*this);
		}

	public:

		Mesh_BndEdgeGeomAdaptor()
		{}


		//- public functions and operators

	};

	template<class SurfType>
	class Mesh_BndEdgeGeomAdaptor<void, SurfType, Mesh_BndEdge_Position_Facet>
	{

		/*Private Data*/

		std::weak_ptr<SurfType> theSurface_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		Mesh_BndEdgeGeomAdaptor()
		{}


		//- public functions and operators

		const auto& Surface() const
		{
			return theSurface_;
		}

		void SetSurface
		(
			const std::weak_ptr<SurfType>& theSurface
		)
		{
			theSurface_ = theSurface;
		}
	};
}

#undef MESH_MODULE

#endif // !_Mesh_BndEdgeGeomAdaptor_Header