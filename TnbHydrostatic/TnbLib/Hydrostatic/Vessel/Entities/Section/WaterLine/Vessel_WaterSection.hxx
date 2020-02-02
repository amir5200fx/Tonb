#pragma once
#ifndef _Vessel_WaterSection_Header
#define _Vessel_WaterSection_Header

#include <Vessel_Section.hxx>

namespace tnbLib
{

	class Vessel_WaterSection
		: public Vessel_Section
	{

		typedef std::vector<std::shared_ptr<Pln_Wire>> wireList;

		/*Private Data*/


	public:

		Vessel_WaterSection
		(
			const std::shared_ptr<wireList>& theOuter, 
			const std::shared_ptr<wireList>& theInner = nullptr
		);

		Vessel_WaterSection
		(
			const Standard_Integer theIndex, 
			const std::shared_ptr<wireList>& theOuter, 
			const std::shared_ptr<wireList>& theInner = nullptr
		);

		Vessel_WaterSection
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const std::shared_ptr<wireList>& theOuter, 
			const std::shared_ptr<wireList>& theInner = nullptr
		);
	};
}

#endif // !_Vessel_WaterSection_Header
