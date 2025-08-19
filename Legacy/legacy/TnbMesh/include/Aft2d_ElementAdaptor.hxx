#pragma once
#ifndef _Aft2d_ElementAdaptor_Header
#define _Aft2d_ElementAdaptor_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <array>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/1/2023 Payvand]

		class Aft2d_Element;

		class Aft2d_ElementAdaptor
		{

			/*Private Data*/

			std::array<std::shared_ptr<Aft2d_Element>, 3> theNeighbors_;


			// Private functions and operators [2/1/2023 Payvand]

			TNB_SERIALIZATION(TnbLegMesh_EXPORT);

		protected:

			// default constructor [2/1/2023 Payvand]

			Aft2d_ElementAdaptor()
			{}

			// constructors [2/1/2023 Payvand]


		public:

			// Public functions and operators [2/1/2023 Payvand]

			const auto& Neighbors() const
			{
				return theNeighbors_;
			}

			const auto& Neighbor0() const
			{
				return std::get<0>(Neighbors());
			}

			auto& Neighbor0Ref()
			{
				return std::get<0>(Neighbors());
			}

			const auto& Neighbor1() const
			{
				return std::get<1>(Neighbors());
			}

			auto& Neighbor1Ref()
			{
				return std::get<1>(Neighbors());
			}

			const auto& Neighbor2() const
			{
				return std::get<2>(Neighbors());
			}

			auto& Neighbor2Ref()
			{
				return std::get<2>(Neighbors());
			}
		};
	}
}

#endif // !_Aft2d_ElementAdaptor_Header
