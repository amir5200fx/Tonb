#pragma once
#ifndef _Geo3d_SpaceCloud_TetSamples_Header
#define _Geo3d_SpaceCloud_TetSamples_Header

#include <Mesh_Module.hxx>
#include <Pnt3d.hxx>
#include <Global_Serialization.hxx>

#include <vector>

namespace tnbLib
{

	class Geo3d_SpaceCloud_TetSamples
	{

		/*Private Data*/

		// Private functions and operators [10/28/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			// Empty body [10/28/2022 Amir]
		}

	protected:

		// default constructor [10/28/2022 Amir]

		Geo3d_SpaceCloud_TetSamples()
		{}


		// constructors [10/28/2022 Amir]


	public:


		// public functions and operators [10/28/2022 Amir]

		virtual std::vector<Pnt3d> CalcSamples(const Pnt3d& theP0, const Pnt3d& theP1, const Pnt3d& theP2, const Pnt3d& theP3) const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo3d_SpaceCloud_TetSamples);

#endif // !_Geo3d_SpaceCloud_TetSamples_Header
