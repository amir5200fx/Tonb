#pragma once
#ifndef _Aft2d_StdOptNodeAnIso_Header
#define _Aft2d_StdOptNodeAnIso_Header

#include <Aft2d_OptNodeAnIso_Calculator.hxx>

namespace tnbLib
{

	class Aft2d_StdOptNodeAnIso
		: public Aft2d_OptNodeAnIso_Calculator
	{

		/*Private Data*/

		// private functions and operators [12/23/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Aft2d_OptNodeAnIso_Calculator>(*this);
		}

	public:

		// default constructor [12/23/2021 Amir]

		Aft2d_StdOptNodeAnIso()
		{}


		// constructors [12/23/2021 Amir]


		// public functions and operators [12/23/2021 Amir]

		TnbMesh_EXPORT void Perform() override;
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_StdOptNodeAnIso);

#endif // !_Aft2d_StdOptNodeAnIso_Header
