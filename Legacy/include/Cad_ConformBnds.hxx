#pragma once
#ifndef _Cad_ConformBnds_Header
#define _Cad_ConformBnds_Header

#include <Global_Done.hxx>
#include <Cad_Module.hxx>

#include <memory>

namespace tnbLib
{


	//- Forward Declarations
	class Cad_TModel;

	class Cad_ConformBnds
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Cad_TModel> theSolid_;

		std::shared_ptr<Cad_TModel> theConformed_;

	public:

		//- default constructor

		Cad_ConformBnds()
		{}


		//- constructors


		//- public functions and operators

		const auto& Solid() const
		{
			return theSolid_;
		}

		const auto& Conformed() const
		{
			return theConformed_;
		}

		void Perform();

		void LoadSolid(const std::shared_ptr<Cad_TModel>& theSolid)
		{
			theSolid_ = theSolid;
		}
	};
}

#endif // !_Cad_ConformBnds_Header
