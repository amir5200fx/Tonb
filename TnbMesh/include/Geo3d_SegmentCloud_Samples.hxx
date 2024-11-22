#pragma once
#ifndef _Geo3d_SegmentCloud_Samples_Header
#define _Geo3d_SegmentCloud_Samples_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

#include <vector>

namespace tnbLib
{

	class Geo3d_SegmentCloud_Samples
	{

		/*Private Data*/

		// private functions and operators [10/19/2022 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			// empty body [10/19/2022 Amir]
		}

	protected:

		// default constructor [10/19/2022 Amir]

		Geo3d_SegmentCloud_Samples()
		{}


		// constructors [10/19/2022 Amir]

	public:

		// public functions and operators [10/19/2022 Amir]

		virtual std::vector<Standard_Real> CalcSamples(const Standard_Real x0, const Standard_Real x1) const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo3d_SegmentCloud_Samples);

#endif // !_Geo3d_SegmentCloud_Samples_Header
