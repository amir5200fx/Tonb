#pragma once
#ifndef _Aft_OptNode_Uniform_Header
#define _Aft_OptNode_Uniform_Header

#include <Aft_OptNode.hxx>
#include <Aft_OptNode_UniformTraits.hxx>

namespace tnbLib
{

	template<class FrontType, class SizeFun>
	class Aft_OptNode<FrontType, SizeFun, void, void, void>
		: public Aft_OptNode_Calculator<FrontType, SizeFun>
	{

	public:

		typedef typename analytical_optNode_calculator<FrontType>::calcType analyOptNodeCalc;

	private:

		/*Private Data*/


		// Private functions and operators [3/10/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& boost::serialization::base_object<Aft_OptNode_Calculator<FrontType, SizeFun>>(*this);
		}

	public:

		// default constructor [3/1/2022 Amir]

		Aft_OptNode()
		{}

		// constructors [3/1/2022 Amir]


		// override functions and operators [3/1/2022 Amir]

		void Perform() override;

		// public functions and operators [3/1/2022 Amir]

	};
}

#include <Aft_OptNode_UniformI.hxx>

#endif // !_Aft_OptNode_Uniform_Header
