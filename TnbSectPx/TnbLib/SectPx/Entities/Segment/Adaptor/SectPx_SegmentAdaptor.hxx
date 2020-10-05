#pragma once
#ifndef _SectPx_SegmentAdaptor_Header
#define _SectPx_SegmentAdaptor_Header

#include <Standard_TypeDef.hxx>
#include <Pnt2d.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_SegmentController;

	class SectPx_SegmentAdaptor
	{

		/*Private Data*/

		std::weak_ptr<SectPx_SegmentController> theController_;


	protected:

		SectPx_SegmentAdaptor()
		{}

	public:

		Standard_Boolean HasController() const
		{
			return (Standard_Boolean)theController_.lock();
		}

		const auto& Controller() const
		{
			return theController_;
		}

		void SetController
		(
			const std::shared_ptr<SectPx_SegmentController>& theController
		)
		{
			theController_ = theController;
		}

		//std::vector<Pnt2d> RetrieveControlPoints() const;
	};
}

#endif // !_SectPx_SegmentAdaptor_Header
