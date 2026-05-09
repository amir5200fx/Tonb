#pragma once
#ifndef _VoyageWP_Connect2_Header
#define _VoyageWP_Connect2_Header

#include <Voyage_Module.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class VoyageWP_Net;
	class Pnt2d;

	class VoyageWP_Connect2
		: public Global_Done
	{

	public:

		typedef std::function<Standard_Boolean(const Pnt2d&, const Pnt2d&)> StateFunc;

	private:

		/*Private Data*/

		std::shared_ptr<VoyageWP_Net> theNet_;
		StateFunc theStateFun_;

		Standard_Integer theSize_;

	public:

		// default constructor

		VoyageWP_Connect2()
			: theSize_(5)
		{}

		// constructors

		// Public functions and operators

		[[nodiscard]] const auto& Net() const { return theNet_; }
		[[nodiscard]] auto Size() const { return theSize_; }

		TnbVoyage_EXPORT void Perform();

		void SetNet(const std::shared_ptr<VoyageWP_Net>& theNet) { theNet_ = theNet; }
		void SetStateFun(const StateFunc& theFun) { theStateFun_ = theFun; }
		void SetSize(const Standard_Integer theSize) { theSize_ = theSize; }
		
	};
}

#endif
