#pragma once
#ifndef _Aft2d_Node_Header
#define _Aft2d_Node_Header

#include <Aft2d_NodeGeometry.hxx>
#include <Aft2d_NodeAdaptor.hxx>
#include <Aft2d_Entity.hxx>

namespace tnbLib
{

	namespace legLib
	{

		class Aft2d_Node
			: public Aft2d_Entity
			, public Aft2d_NodeGeometry
			, public Aft2d_NodeAdaptor
		{

			/*Private Data*/


			// Private functions and operators [2/1/2023 Payvand]

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive& ar, const unsigned int file_version)
			{
				ar& boost::serialization::base_object<Aft2d_Entity>(*this);
				ar& boost::serialization::base_object<Aft2d_NodeGeometry>(*this);
				ar& boost::serialization::base_object<Aft2d_NodeAdaptor>(*this);
			}

		protected:

			// default constructor [2/1/2023 Payvand]

			Aft2d_Node()
			{}


			// constructors [2/1/2023 Payvand]

			Aft2d_Node(const Standard_Integer theIndex, const Pnt2d& theCoord)
				: Aft2d_Entity(theIndex)
				, Aft2d_NodeGeometry(theCoord)
			{}

			Aft2d_Node(const Standard_Integer theIndex, Pnt2d&& theCoord)
				: Aft2d_Entity(theIndex)
				, Aft2d_NodeGeometry(std::move(theCoord))
			{}

		public:

			// Public functions and operators [2/1/2023 Payvand]

			virtual TnbLegMesh_EXPORT Standard_Boolean IsInterior() const;
			virtual TnbLegMesh_EXPORT Standard_Boolean IsBoundary() const;
		};
	}
}

#include <Aft2d_NodeI.hxx>

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::legLib::Aft2d_Node);

#endif // !_Aft2d_Node_Header
