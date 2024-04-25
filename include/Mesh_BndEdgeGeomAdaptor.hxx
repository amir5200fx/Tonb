#pragma once
#ifndef _Mesh_BndEdgeGeomAdaptor_Header
#define _Mesh_BndEdgeGeomAdaptor_Header

#include <Mesh_EntityAdaptorM.hxx>
#include <Mesh_BndEdge_Position.hxx>

#define MESH_MODULE TnbMesh_EXPORT

namespace tnbLib
{

	Mesh_EntityToEntityAdaptor(BndEdge, Surface, SurfType);
	Mesh_EntityToEntityAdaptor(BndEdge, Pair, EdgeType);

	template<class CurveType>
	class Mesh_BndEdgeGeomAdaptorBase
	{

		/*Private Data*/

		std::weak_ptr<CurveType> theCurve_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor

		Mesh_BndEdgeGeomAdaptorBase()
		{}

	public:


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

	template<class CurveType, class SurfType, class EdgeType, Mesh_BndEdge_Position POS = Mesh_BndEdge_Position_Segment>
	class Mesh_BndEdgeGeomAdaptor
		: public Mesh_BndEdgeToSurfaceAdaptor<SurfType>
		, public Mesh_BndEdgeGeomAdaptorBase<CurveType>
		, public Mesh_BndEdgeToPairAdaptor<EdgeType>
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

	protected:

		// default constructor

		Mesh_BndEdgeGeomAdaptor()
		{}


	public:

		

		//- public functions and operators

	};

	template<class CurveType>
	class Mesh_BndEdgeGeomAdaptor<CurveType, void, void, Mesh_BndEdge_Position_Segment>
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

	protected:

		// default constructor

		Mesh_BndEdgeGeomAdaptor()
		{}

	public:


		//- public functions and operators

	};

	template<class CurveType, class EdgeType>
	class Mesh_BndEdgeGeomAdaptor<CurveType, void, EdgeType, Mesh_BndEdge_Position_Segment>
		: public Mesh_BndEdgeGeomAdaptorBase<CurveType>
		, public Mesh_BndEdgeToPairAdaptor<EdgeType>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& boost::serialization::base_object<Mesh_BndEdgeGeomAdaptorBase<CurveType>>(*this);
		}

	protected:

		// default constructor

		Mesh_BndEdgeGeomAdaptor()
		{}

	public:


		//- public functions and operators

	};

	template<class SurfType>
	class Mesh_BndEdgeGeomAdaptor<void, SurfType, void, Mesh_BndEdge_Position_Facet>
	{

		/*Private Data*/

		std::weak_ptr<SurfType> theSurface_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor

		Mesh_BndEdgeGeomAdaptor()
		{}

	public:


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