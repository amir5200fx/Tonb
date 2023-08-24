#pragma once
#ifndef _Geo2d_2ndNurbsPx_Header
#define _Geo2d_2ndNurbsPx_Header

#include <Geo2d_NurbsPx.hxx>

namespace tnbLib
{

	class Geo2d_2ndNurbsPx
		: public Geo2d_NurbsPx
	{

		/*Private Data*/

		// Private functions and operators [8/15/2023 aamir]

		friend class boost::serialization::access;
			
		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Geo2d_NurbsPx>(*this);
		}

	protected:

		// default constructor [8/15/2023 aamir]

		Geo2d_2ndNurbsPx()
		{}

		// constrcutors [8/15/2023 aamir]


	public:

		// Public functions and operators [8/15/2023 aamir]



	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Geo2d_2ndNurbsPx);

#endif // !_Geo2d_2ndNurbsPx_Header
