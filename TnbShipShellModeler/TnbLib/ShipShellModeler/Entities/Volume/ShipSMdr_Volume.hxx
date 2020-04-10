#pragma once
#ifndef _ShipSMdr_Volume_Header
#define _ShipSMdr_Volume_Header

#include <Global_AccessMethod.hxx>
#include <ShipSMdr_Entity.hxx>
#include <ShipSMdr_VolumeType.hxx>

#include <memory>
#include <vector>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class NModel_Surface;
	class NModel_Shell;

	class ShipSMdr_Volume
		: public ShipSMdr_Entity
	{

		typedef std::vector<std::shared_ptr<NModel_Shell>> shellList;

		typedef std::shared_ptr<NModel_Shell> outer;
		typedef std::shared_ptr<shellList> inner;

		/*Private Data*/

		outer theOuter_;
		inner theInner_;

		ShipSMdr_VolumeType theType_;

		auto& ChangeInner()
		{
			return theInner_;
		}

		auto& ChangeOuter()
		{
			return theOuter_;
		}

	public:

		ShipSMdr_Volume();

		ShipSMdr_Volume
		(
			const Standard_Integer theIndex
		);

		ShipSMdr_Volume
		(
			const Standard_Integer theIndex, 
			const word& theName
		);

		const auto& Inner() const
		{
			return theInner_;
		}

		const auto& Outer() const
		{
			return theOuter_;
		}

		//- Macros
		GLOBAL_ACCESS_PRIM_SINGLE(ShipSMdr_VolumeType, Type)
	};
}

#endif // !_ShipSMdr_Volume_Header
