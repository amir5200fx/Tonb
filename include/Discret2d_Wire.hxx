#pragma once
#ifndef _Discret2d_Wire_Header
#define _Discret2d_Wire_Header

#include <Discret_Module.hxx>

#include <Entity2d_PolygonFwd.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/13/2023 Payvand]
	class Pln_Wire;
	class Discret2d_PlnCurve_Function;
	class Discret_CurveInfo;

	class Discret2d_Wire
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Pln_Wire> theWire_;

		std::shared_ptr<Discret2d_PlnCurve_Function> theFun_;
		std::shared_ptr<Discret_CurveInfo> theInfo_;

		// results [7/13/2023 Payvand]

		std::shared_ptr<Entity2d_Polygon> thePolygon_;

	public:

		// default constructor [7/13/2023 Payvand]

		Discret2d_Wire()
		{}


		// constructors [7/13/2023 Payvand]

		Discret2d_Wire
		(
			const std::shared_ptr<Pln_Wire>& theWire,
			const std::shared_ptr<Discret2d_PlnCurve_Function>& theFun, 
			const std::shared_ptr<Discret_CurveInfo>& theInfo
		)
			: theWire_(theWire)
			, theFun_(theFun)
			, theInfo_(theInfo)
		{}

		// Public functions and operators [7/13/2023 Payvand]

		const auto& Function() const { return theFun_; }
		const auto& ApprxInfo() const { return theInfo_; }

		const auto& Wire() const { return theWire_; }

		const auto& Polygon() const { return thePolygon_; }

		TnbDiscret_EXPORT void Perform();

		void SetWire(const std::shared_ptr<Pln_Wire>& theWire) { theWire_ = theWire; }

		void SetFunction(const std::shared_ptr<Discret2d_PlnCurve_Function>& theFun) { theFun_ = theFun; }
		void SetInfo(const std::shared_ptr<Discret_CurveInfo>& theInfo) { theInfo_ = theInfo; }

	};
}

#endif // !_Discret2d_Wire_Header
