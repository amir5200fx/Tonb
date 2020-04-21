#pragma once
#ifndef _HydStatic_Modeler_Corner_Header
#define _HydStatic_Modeler_Corner_Header

#include <Pnt3d.hxx>
#include <HydStatic_Modeler_Entity.hxx>

#include <map>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Vertex;
	class HydStatic_Modeler;

	namespace hydStcLib
	{

		class Modeler_Corner
			: public Modeler_Entity
		{

			friend class HydStatic_Modeler;

			/*Private Data*/

			Pnt3d theCoord_;

			Standard_Real theRadius_;

			std::map<Standard_Integer, std::shared_ptr<NModel_Vertex>>
				theVertices_;


			void Insert(const std::shared_ptr<NModel_Vertex>& theVertex);

			void Remove(const std::shared_ptr<NModel_Vertex>& theVertex);

			void SetCoord(const Pnt3d& theCoord)
			{
				theCoord_ = theCoord;
			}

			void SetRadius(const Standard_Real theRadius)
			{
				theRadius_ = theRadius;
			}

			void Update();

		public:

			typedef Pnt3d ptType;

			Modeler_Corner()
			{}

			Modeler_Corner(const Standard_Integer theIndex, const word& theName);

			auto Radius() const
			{
				return theRadius_;
			}

			const auto& Coord() const
			{
				return theCoord_;
			}

			auto NbVertices() const
			{
				return (Standard_Integer)theVertices_.size();
			}

			const auto& Vertices() const
			{
				return theVertices_;
			}

			static Standard_Boolean 
				IsLess
				(
					const std::shared_ptr<Modeler_Corner>& theCorner0,
					const std::shared_ptr<Modeler_Corner>& theCorner1
				);
		};
	}
}

#endif // !_HydStatic_Modeler_Corner_Header
