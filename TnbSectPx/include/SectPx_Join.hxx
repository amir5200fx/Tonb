#pragma once
#ifndef _SectPx_Join_Header
#define _SectPx_Join_Header

#include <Global_Done.hxx>
#include <SectPx_Module.hxx>
#include <SectPx_JoinPriority.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_TopoProfile;
	class SectPx_Registry;

	class SectPx_Join
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<SectPx_TopoProfile> theLeft_;
		std::shared_ptr<SectPx_TopoProfile> theRight_;

		const std::shared_ptr<SectPx_Registry>& theRegistry_;

		Standard_Integer theNewLeftId_;
		Standard_Integer theNewRightId_;

		Standard_Integer theNewPntId_;


		//- private functions and operators

		auto& ChangeNewLeftInterfaceId()
		{
			return theNewLeftId_;
		}

		auto& ChangeNewRightInterfaceId()
		{
			return theNewRightId_;
		}

		auto& ChangeNewPntId()
		{
			return theNewPntId_;
		}

	public:

		SectPx_Join
		(
			const std::shared_ptr<SectPx_Registry>& theRegistry
		)
			: theRegistry_(theRegistry)
		{}

		SectPx_Join
		(
			const std::shared_ptr<SectPx_Registry>& theRegistry,
			const std::shared_ptr<SectPx_TopoProfile>& theLeft,
			const std::shared_ptr<SectPx_TopoProfile>& theRight
		)
			: theRegistry_(theRegistry)
			, theLeft_(theLeft)
			, theRight_(theRight)
		{}

		const auto& LeftProfile() const
		{
			return theLeft_;
		}

		const auto& RightProfile() const
		{
			return theRight_;
		}

		const auto& Registry() const
		{
			return theRegistry_;
		}

		auto NewLeftInterfaceId() const
		{
			return theNewLeftId_;
		}

		auto NewRightInterfaceId() const
		{
			return theNewRightId_;
		}

		auto NewPointId() const
		{
			return theNewPntId_;
		}

		TnbSectPx_EXPORT void MakeJoint(const SectPx_JoinPriority priority = SectPx_JoinPriority::left);

		void SetLeftProfile
		(
			const std::shared_ptr<SectPx_TopoProfile>& theProfile
		)
		{
			theLeft_ = theProfile;
		}

		void SetRightProfile
		(
			const std::shared_ptr<SectPx_TopoProfile>& theProfile
		)
		{
			theRight_ = theProfile;
		}
	};
}

#endif // !_SectPx_Join_Header
