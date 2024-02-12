#pragma once
#ifndef _MeshPost2d_LaplacianSmoothing_AdjEdges_Header
#define _MeshPost2d_LaplacianSmoothing_AdjEdges_Header

#include <MeshPost2d_LaplacianSmoothing_AvgFun.hxx>

namespace tnbLib
{

	class MeshPost2d_LaplacianSmoothing_AdjEdges
		: public MeshPost2d_LaplacianSmoothing_AvgFun
	{

		/*Private Data*/

		// Private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar& boost::serialization::base_object<MeshPost2d_LaplacianSmoothing_AvgFun>(*this);
		}

	public:

		// default constructor [9/19/2022 Amir]

		MeshPost2d_LaplacianSmoothing_AdjEdges()
			= default;

		// constructors [9/19/2022 Amir]


		// public functions and operators [9/19/2022 Amir]

		TnbMeshPost_EXPORT Pnt2d CalcAverage(const std::shared_ptr<Aft2d_Node>&) const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::MeshPost2d_LaplacianSmoothing_AdjEdges);

#endif // !_MeshPost2d_LaplacianSmoothing_AdjEdges_Header
