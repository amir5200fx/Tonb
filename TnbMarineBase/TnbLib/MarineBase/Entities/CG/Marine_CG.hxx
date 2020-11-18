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


		//- private functions and operators

		DECLARE_SAVE_LOAD_HEADER(TnbMarine_EXPORT);

	protected:


		Marine_CG()
		{}

	public:


		//- constructors

		TnbMarine_EXPORT Marine_CG
		(
			const std::shared_ptr<Marine_LCG>& theLcg, 
			const std::shared_ptr<Marine_VCG>& theVcg, 
			const std::shared_ptr<Marine_TCG>& theTcg
		);

		TnbMarine_EXPORT Marine_CG
		(
			std::shared_ptr<Marine_LCG>&& theLcg,
			std::shared_ptr<Marine_VCG>&& theVcg,
			std::shared_ptr<Marine_TCG>&& theTcg
		);

		TnbMarine_EXPORT Marine_CG
		(
			const Standard_Integer theIndex,
			const word& theName, 
			const std::shared_ptr<Marine_LCG>& theLcg, 
			const std::shared_ptr<Marine_VCG>& theVcg, 
			const std::shared_ptr<Marine_TCG>& theTcg
		);

		TnbMarine_EXPORT Marine_CG
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

BOOST_CLASS_EXPORT_KEY(tnbLib::Marine_CG);

#endif // !_Marine_CG_Header
