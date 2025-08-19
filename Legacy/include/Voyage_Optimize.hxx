#pragma once
#ifndef _Voyage_Optimize_Header
#define _Voyage_Optimize_Header

#include <Pnt2d.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	//- Forward Declarations
	class VoyageWP_Net;

	class Voyage_Optimize
		: public Global_Done
	{

	public:

		typedef std::function
			<
			Standard_Real
			(
				const std::pair<Pnt2d, Standard_Real>&,
				const std::pair<Pnt2d, Standard_Real>&
			)> ResistFun;

	private:

		/*Private Data*/

		std::shared_ptr<VoyageWP_Net> theNet_;
		ResistFun theResist_;

	public:

		//- default constructor

		Voyage_Optimize()
		{}

		//- constructors

		void Perform();

		//- Public functions and operators

		const auto& ResistFunction() const { return theResist_; }

		void SetResistFunction(const ResistFun& theFun) { theResist_ = theFun; }

	};

}

#endif // !_Voyage_Optimize_Header
