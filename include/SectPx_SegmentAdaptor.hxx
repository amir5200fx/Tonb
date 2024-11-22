#pragma once
#ifndef _SectPx_SegmentAdaptor_Header
#define _SectPx_SegmentAdaptor_Header

#include <SectPx_Module.hxx>
#include <Pnt2d.hxx>
#include <Global_Serialization.hxx>
#include <Global_TypeDef.hxx>

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


		//- private functions and operators

		TNB_SERIALIZATION(TnbSectPx_EXPORT);


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
