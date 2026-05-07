#pragma once
#ifndef _Geo3d_PatchCloud_EdgeSamplesLev1_Header
#define _Geo3d_PatchCloud_EdgeSamplesLev1_Header

#include <Geo3d_PatchCloud_EdgeSamples.hxx>

namespace tnbLib
{

	class Geo3d_PatchCloud_EdgeSamplesLev1
		: public Geo3d_PatchCloud_EdgeSamples
	{

		/*Private Data*/


		// Private functions and operators [10/16/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Geo3d_PatchCloud_EdgeSamples>(*this);
		}

	public:

		// default constructor [10/16/2022 Amir]

		Geo3d_PatchCloud_EdgeSamplesLev1()
		{}


		// constructors [10/16/2022 Amir]


		// public functions and operators [10/16/2022 Amir]

		TnbMesh_EXPORT std::vector<Pnt2d>
			CalcSamples(const Pnt2d& theP0, const Pnt2d& theP1) const override;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo3d_PatchCloud_EdgeSamplesLev1);

#endif // !_Geo3d_PatchCloud_EdgeSamplesLev1_Header
