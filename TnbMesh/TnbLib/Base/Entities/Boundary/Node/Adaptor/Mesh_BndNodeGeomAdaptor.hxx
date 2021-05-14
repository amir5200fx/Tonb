#pragma once
#ifndef _Mesh_BndNodeGeomAdaptor_Header
#define _Mesh_BndNodeGeomAdaptor_Header

#include <Mesh_EntityAdaptorM.hxx>
#include <Mesh_BndNode_Position.hxx>

#define MESH_MODULE TnbMesh_EXPORT

namespace tnbLib
{

	Mesh_EntityToEntityAdaptor(BndNode, Curve, CurveType);
	Mesh_EntityToEntityAdaptor(BndNode, Surface, SurfType);

	template<class CurveType, class SurfType, Mesh_BndNode_Position POS = Mesh_BndNode_Position_Corner>
	class Mesh_BndNodeGeomAdaptor
		: public Mesh_BndNodeToCurveAdaptor<CurveType>
		, public Mesh_BndNodeToSurfaceAdaptor<SurfType>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh_BndNodeToCurveAdaptor<CurveType>>(*this);
			ar & boost::serialization::base_object<Mesh_BndNodeToSurfaceAdaptor<SurfType>>(*this);
		}

	protected:

		// default constructor

		Mesh_BndNodeGeomAdaptor()
		{}

	public:

		

		//- public functions and operators

	};

	template<class CurveType, class SurfType>
	class Mesh_BndNodeGeomAdaptor<CurveType, SurfType, Mesh_BndNode_Position_Segment>
		: public Mesh_BndNodeToSurfaceAdaptor<SurfType>
	{

		/*private Data*/

		std::weak_ptr<CurveType> theCurve_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor

		Mesh_BndNodeGeomAdaptor()
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

	template<class CurveType, class SurfType>
	class Mesh_BndNodeGeomAdaptor<CurveType, SurfType, Mesh_BndNode_Position_Facet>
	{

		/*Private Data*/

		std::weak_ptr<CurveType> theCurve_;
		std::weak_ptr<SurfType> theSurface_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor

		Mesh_BndNodeGeomAdaptor()
		{}

	public:

		


		//- public functions and operators

		const auto& Curve() const
		{
			return theCurve_;
		}

		const auto& Surface() const
		{
			return theSurface_;
		}

		void SetCurve
		(
			const std::weak_ptr<CurveType>& theCurve
		)
		{
			theCurve_ = theCurve;
		}

		void SetSurface
		(
			const std::weak_ptr<SurfType>& theSurface
		)
		{
			theSurface_ = theSurface;
		}

	};

	template<class CurveType>
	class Mesh_BndNodeGeomAdaptor<CurveType, void, Mesh_BndNode_Position_Corner>
		: public Mesh_BndNodeToCurveAdaptor<CurveType>
	{

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Mesh_BndNodeToCurveAdaptor<CurveType>>(*this);
		}

	public:

		Mesh_BndNodeGeomAdaptor()
		{}


		//- public functions and operators

	};

	template<class CurveType>
	class Mesh_BndNodeGeomAdaptor<CurveType, void, Mesh_BndNode_Position_Segment>
	{

		/*Private Data*/

		std::weak_ptr<CurveType> theCurve_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		Mesh_BndNodeGeomAdaptor()
		{}


		//- public functions and operators

		const auto& Curve() const
		{
			return theCurve_;
		}

		void SetCurve(const std::weak_ptr<CurveType>& theCurve)
		{
			theCurve_ = theCurve;
		}

	};
}

#undef MESH_MODULE

#endif // !_Mesh_BndNodeGeomAdaptor_Header