#pragma once
#ifndef _VoyageMesh_EdgeIdentifier_Header
#define _VoyageMesh_EdgeIdentifier_Header

#include <Aft2d_EdgeIdentifierSurface.hxx>
#include <Entity2d_Metric1.hxx>

namespace tnbLib
{

	// Forward Declarations [8/22/2023 aamir]
	class VoyageMesh_Node;

	struct VoyageMesh_EdgeIdentifier_Traits
	{
		typedef Pnt2d ptType;
	};

	template<>
	class Aft_EntityIdentifier<VoyageMesh_Node, true>
		: public Aft_EntityIdentifier<VoyageMesh_EdgeIdentifier_Traits, true>
	{

		/*Private Data*/

		Entity2d_Metric1 theMetric_;

		Standard_Real theLength3d_;

		// Private functions and operators [8/22/2023 aamir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Aft_EntityIdentifier<VoyageMesh_EdgeIdentifier_Traits, true>>(*this);
			ar& theMetric_;
			ar& theLength3d_;
		}

	public:

		// default constructor [8/22/2023 aamir]

		Aft_EntityIdentifier()
			: theLength3d_(0)
		{}

		// constructors [8/22/2023 aamir]


		// Public functions and operators [8/22/2023 aamir]

		const auto& EffectiveMetric() const { return theMetric_; }
		auto& EffectiveMetric() { return theMetric_; }

		auto Length3D() const { return theLength3d_; }
		auto& Length3D() { return theLength3d_; }

		void SetEffectiveMetric(const Entity2d_Metric1& theMetric)
		{
			theMetric_ = theMetric;
		}

		void SetLength3D(const Standard_Real theLength)
		{
			theLength3d_ = theLength;
		}

	};

}

#endif // !_VoyageMesh_EdgeIdentifier_Header
