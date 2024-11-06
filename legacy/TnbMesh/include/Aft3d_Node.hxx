#pragma once
#ifndef _Aft3d_Node_Header
#define _Aft3d_Node_Header

#include <Aft3d_NodeAdaptor.hxx>
#include <Aft3d_NodeGeometry.hxx>
#include <Aft3d_Entity.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft3d_Node
			: public Aft3d_NodeAdaptor
			, public Aft3d_NodeGeometry
			, public Aft3d_Entity
		{

			/*Private Data*/


			// Private functions and operators [2/27/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft3d_NodeAdaptor>(*this);
				ar& boost::serialization::base_object<Aft3d_NodeGeometry>(*this);
				ar& boost::serialization::base_object<Aft3d_Entity>(*this);
			}

		public:

			typedef Pnt3d ptType;

		protected:

			// default constructor [2/26/2023 Payvand]

			Aft3d_Node()
			{}

			// constructors [2/26/2023 Payvand]

			explicit Aft3d_Node(const Standard_Integer theIndex)
				: Aft3d_Entity(theIndex)
			{}

			Aft3d_Node
			(
				const Standard_Integer theIndex, 
				const Pnt3d& theCoord
			)
				: Aft3d_Entity(theIndex)
				, Aft3d_NodeGeometry(theCoord)
			{}

			Aft3d_Node
			(
				const Standard_Integer theIndex,
				Pnt3d&& theCoord
			)
				: Aft3d_Entity(theIndex)
				, Aft3d_NodeGeometry(std::move(theCoord))
			{}

		public:

			// Public functions and operators [2/26/2023 Payvand]

			TnbLegMesh_EXPORT virtual Standard_Boolean IsBoundary() const;
			TnbLegMesh_EXPORT virtual Standard_Boolean IsInterior() const;

		};
	}
}

#include <Aft3d_NodeI.hxx>

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::legLib::Aft3d_Node);

#endif // !_Aft3d_Node_Header
