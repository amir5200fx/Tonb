#pragma once
#ifndef _Aft3d_ElementAdaptor_Header
#define _Aft3d_ElementAdaptor_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <array>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [3/1/2023 Payvand]

		class Aft3d_Element;

		class Aft3d_ElementAdaptor
		{

		public:

			enum 
			{
				nbNeighbors = 4
			};

		private:

			/*Private Data*/

			std::array<std::weak_ptr<Aft3d_Element>, nbNeighbors> theNeighbors_;


			// Private functions and operators [3/1/2023 Payvand]

			TNB_SERIALIZATION(TnbLegMesh_EXPORT);

		protected:

			// default constructor [3/1/2023 Payvand]

			Aft3d_ElementAdaptor()
			{}

			// constructors [3/1/2023 Payvand]


		public:

			// Public functions and operators [3/1/2023 Payvand]

			const auto& Neighbors() const { return theNeighbors_; }

			TnbLegMesh_EXPORT std::shared_ptr<Aft3d_Element> 
				Neighbor(const Standard_Integer theIndex) const;

			TnbLegMesh_EXPORT std::shared_ptr<Aft3d_Element> Neighbor0() const;
			TnbLegMesh_EXPORT std::shared_ptr<Aft3d_Element> Neighbor1() const;
			TnbLegMesh_EXPORT std::shared_ptr<Aft3d_Element> Neighbor2() const;
			TnbLegMesh_EXPORT std::shared_ptr<Aft3d_Element> Neighbor3() const;

			TnbLegMesh_EXPORT void SetNeighbor0(const std::shared_ptr<Aft3d_Element>&);
			TnbLegMesh_EXPORT void SetNeighbor1(const std::shared_ptr<Aft3d_Element>&);
			TnbLegMesh_EXPORT void SetNeighbor2(const std::shared_ptr<Aft3d_Element>&);
			TnbLegMesh_EXPORT void SetNeighbor3(const std::shared_ptr<Aft3d_Element>&);

			TnbLegMesh_EXPORT void SetNeighbor
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Aft3d_Element>&
			);

		};
	}
}

#endif // !_Aft3d_ElementAdaptor_Header
