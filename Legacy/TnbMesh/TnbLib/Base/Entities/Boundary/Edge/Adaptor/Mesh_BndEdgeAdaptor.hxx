#pragma once
#ifndef _Mesh_BndEdgeAdaptor_Header
#define _Mesh_BndEdgeAdaptor_Header

#include <Mesh_BndEdgeGeomAdaptor.hxx>

namespace tnbLib
{

	template
		<
		class CurveType,
		class SurfType,
		class FacetType,
		class EdgeType,
		class MetricPrcsr,
		Mesh_BndEdge_Position POS = Mesh_BndEdge_Position_Segment
		>
		class Mesh_BndEdgeAdaptor
		: public Mesh_BndEdgeGeomAdaptor<CurveType, SurfType, EdgeType, POS>
	{


	public:

		typedef Mesh_BndEdgeGeomAdaptor<CurveType, SurfType, EdgeType, POS> base;

	private:


		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<base>(*this);
		}

	protected:

		//- default constructor

		Mesh_BndEdgeAdaptor()
		{}

	public:

		

		//- public functions and operators


	};

	template<class CurveType, class EdgeType>
	class Mesh_BndEdgeAdaptor<CurveType, void, void, EdgeType, void>
		: public Mesh_BndEdgeGeomAdaptor<CurveType, void, EdgeType, Mesh_BndEdge_Position_Segment>
	{

	public:

		typedef Mesh_BndEdgeGeomAdaptor<CurveType, void, EdgeType, Mesh_BndEdge_Position_Segment>
			base;

	private:

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<base>(*this);
		}

	public:

		Mesh_BndEdgeAdaptor()
		{}


		//- public functions and operators


	};

	template<class CurveType, class EdgeType, class MetricPrcsr>
	class Mesh_BndEdgeAdaptor<CurveType, void, void, EdgeType, MetricPrcsr>
		: public Mesh_BndEdgeGeomAdaptor<CurveType, void, EdgeType, Mesh_BndEdge_Position_Segment>
	{

	public:

		typedef Mesh_BndEdgeGeomAdaptor<CurveType, void, EdgeType, Mesh_BndEdge_Position_Segment>
			base;

	private:

		/*Private Data*/


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<base>(*this);
		}

	public:

		// default constructor
		Mesh_BndEdgeAdaptor()
			= default;


		//- public functions and operators

		virtual Standard_Boolean SingularityContraction(const MetricPrcsr&);
	};
}

#include <Mesh_BndEdgeAdaptorI.hxx>

#endif // !_Mesh_BndEdgeAdaptor_Header
