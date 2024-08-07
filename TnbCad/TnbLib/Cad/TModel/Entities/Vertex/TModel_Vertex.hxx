#pragma once
#ifndef _TModel_Vertex_Header
#define _TModel_Vertex_Header

#include <Cad_EntityPrecision.hxx>
#include <Global_AccessMethod.hxx>
#include <TModel_Entity.hxx>
#include <TModel_VertexAdaptor.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	class TModel_Vertex
		: public TModel_Entity
		, public TModel_VertexAdaptor
		, public Cad_EntityPrecision
	{

		/*Private Data*/

		Pnt3d theCoord_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbCad_EXPORT);

		/*friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<TModel_Entity>(*this);
			ar & boost::serialization::base_object<TModel_VertexAdaptor>(*this);
			ar & theCoord_;
		}*/

	protected:


		//- default constructor

		TModel_Vertex()
		{}

	public:

		typedef Pnt3d pType;

		//- constructors

		explicit TModel_Vertex
		(
			const Standard_Integer theIndex
		)
			: TModel_Entity(theIndex)
		{}


		// constructors [1/5/2022 Amir]

		TModel_Vertex
		(
			const Standard_Integer theIndex,
			const Pnt3d& theCoord
		)
			: TModel_Entity(theIndex)
			, theCoord_(theCoord)
		{}

		TModel_Vertex
		(
			const Standard_Integer theIndex,
			Pnt3d&& theCoord
		)
			: TModel_Entity(theIndex)
			, theCoord_(std::move(theCoord))
		{}

		TModel_Vertex
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Pnt3d& theCoord
		)
			: TModel_Entity(theIndex, theName)
			, theCoord_(theCoord)
		{}

		TModel_Vertex
		(
			const Standard_Integer theIndex,
			const word& theName,
			Pnt3d&& theCoord
		)
			: TModel_Entity(theIndex, theName)
			, theCoord_(std::move(theCoord))
		{}


		//- public functions and operators

		Standard_Integer NbRings() const;

		Standard_Boolean IsOrphan() const;

		//- Macros
		GLOBAL_ACCESS_SINGLE(Pnt3d, Coord)
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::TModel_Vertex);

#endif // !_TModel_Vertex_Header
