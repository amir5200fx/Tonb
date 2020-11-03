#pragma once
#ifndef _Marine_CG_Header
#define _Marine_CG_Header

#include <Marine_Entity.hxx>
#include <Global_AccessMethod.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_LCG;
	class Marine_VCG;
	class Marine_TCG;

	class Marine_CG
		: public Marine_Entity
	{

		/*Private Data*/

		std::shared_ptr<Marine_LCG> theLCG_;
		std::shared_ptr<Marine_VCG> theVCG_;
		std::shared_ptr<Marine_TCG> theTCG_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<Marine_Entity>(*this);

			ar & theLCG_;
			ar & theVCG_;
			ar & theTCG_;
		}

	public:

		Marine_CG
		(
			const std::shared_ptr<Marine_LCG>& theLcg, 
			const std::shared_ptr<Marine_VCG>& theVcg, 
			const std::shared_ptr<Marine_TCG>& theTcg
		);

		Marine_CG
		(
			std::shared_ptr<Marine_LCG>&& theLcg,
			std::shared_ptr<Marine_VCG>&& theVcg,
			std::shared_ptr<Marine_TCG>&& theTcg
		);

		Marine_CG
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<Marine_LCG>& theLcg, 
			const std::shared_ptr<Marine_VCG>& theVcg, 
			const std::shared_ptr<Marine_TCG>& theTcg
		);

		Marine_CG
		(
			const Standard_Integer theIndex,
			const word& theName,
			std::shared_ptr<Marine_LCG>&& theLcg,
			std::shared_ptr<Marine_VCG>&& theVcg,
			std::shared_ptr<Marine_TCG>&& theTcg
		);


		//- Macros
		GLOBAL_ACCESS_SINGLE(std::shared_ptr<Marine_LCG>, LCG)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Marine_VCG>, VCG)
			GLOBAL_ACCESS_SINGLE(std::shared_ptr<Marine_TCG>, TCG)
	};
}

#endif // !_Marine_CG_Header
