#pragma once
#ifndef _ShapePx_Section_Header
#define _ShapePx_Section_Header

#include <ShapePx_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_FrameRegistry;
	class SectPx_Par;

	class ShapePx_Section
		: public ShapePx_Entity
	{

		/*Private Data*/

		std::shared_ptr<SectPx_FrameRegistry> theRegistry_;

	public:

		//- default constructor

		ShapePx_Section()
		{}

		//- constructors

		ShapePx_Section(const Standard_Integer theIndex);

		ShapePx_Section(const Standard_Integer theIndex, const word& theName);

		ShapePx_Section(const std::shared_ptr<SectPx_FrameRegistry>& theReg);

		ShapePx_Section(const Standard_Integer theIndex, const word& theName, const std::shared_ptr<SectPx_FrameRegistry>& theReg);


		//- public functions and operators

		const auto& Registry() const
		{
			return theRegistry_;
		}

		std::vector<std::shared_ptr<SectPx_Par>> RetrieveParameters() const;

		void SetRegistry(const std::shared_ptr<SectPx_FrameRegistry>& theReg)
		{
			theRegistry_ = theReg;
		}

	};
}

#endif // !_ShapePx_Section_Header
