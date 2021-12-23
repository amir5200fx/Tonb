#pragma once
#ifndef _Aft2d_StdOptNode_Header
#define _Aft2d_StdOptNode_Header

#include <Aft2d_OptNode_Calculator.hxx>

namespace tnbLib
{

	class Aft2d_StdOptNode
		: public Aft2d_OptNode_Calculator
	{

		/*Private Data*/


		// Private functions and operators [12/21/2021 Amir]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<Aft2d_OptNode_Calculator>(*this);
		}

	public:

		// default constructor [11/27/2021 Amir]

		Aft2d_StdOptNode()
		{}


		// constructors [11/27/2021 Amir     

		TnbMesh_EXPORT void Perform() override;

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_StdOptNode);

#endif // !_Aft2d_StdOptNode_Header
