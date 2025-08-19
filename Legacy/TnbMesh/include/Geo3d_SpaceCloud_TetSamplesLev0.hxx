#pragma once
#ifndef _Geo3d_SpaceCloud_TetSamplesLev0_Header
#define _Geo3d_SpaceCloud_TetSamplesLev0_Header

#include <Geo3d_SpaceCloud_TetSamples.hxx>

namespace tnbLib
{

	class Geo3d_SpaceCloud_TetSamplesLev0
		: public Geo3d_SpaceCloud_TetSamples
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & boost::serialization::base_object<Geo3d_SpaceCloud_TetSamples>(*this);
		}

	public:

		// default constructor [10/28/2022 Amir]

		Geo3d_SpaceCloud_TetSamplesLev0()
		{}


		// constructors [10/28/2022 Amir]


		// public functions and operators [10/28/2022 Amir]

		TnbMesh_EXPORT std::vector<Pnt3d>
			CalcSamples
			(
				const Pnt3d& theP0, 
				const Pnt3d& theP1,
				const Pnt3d& theP2,
				const Pnt3d& theP3
			) const override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Geo3d_SpaceCloud_TetSamplesLev0);

#endif // !_Geo3d_SpaceCloud_TetSamplesLev0_Header
