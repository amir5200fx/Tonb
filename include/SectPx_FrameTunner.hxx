#pragma once
#ifndef _SectPx_FrameTunner_Header
#define _SectPx_FrameTunner_Header

#include <SectPx_Entity.hxx>
#include <tuple>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Frame;
	class SectPx_FrameRegistry;
	class SectPx_Pole;
	class SectPx_Segment;
	class SectPx_Par;

	class SectPx_FrameTunner
		: public SectPx_Entity
	{

		/*Private Data*/

		std::shared_ptr<SectPx_FrameRegistry> theFrameReg_;

		//- private functions and operators

		const auto& FrameRegistry() const
		{
			return theFrameReg_;
		}

		static TnbSectPx_EXPORT void disJoinSegment
		(
			const std::shared_ptr<SectPx_Pole>& thePole,
			const std::shared_ptr<SectPx_Segment>& theSegment
		);

		static TnbSectPx_EXPORT void disJoinSegment
		(
			const std::shared_ptr<SectPx_Segment>& theSegment
		);

		static TnbSectPx_EXPORT void JoinSegment
		(
			const std::shared_ptr<SectPx_Pole>& thePole,
			const std::shared_ptr<SectPx_Segment>& theSegment,
			const short id
		);

		static TnbSectPx_EXPORT void JoinSegment
		(
			const std::shared_ptr<SectPx_Segment>& theSegment
		);

	public:

		typedef Standard_Integer segmentId;
		typedef Standard_Integer sliderId;
		typedef Standard_Integer tightnessId;

		SectPx_FrameTunner()
		{}

		TnbSectPx_EXPORT Standard_Boolean IsContainPole(const std::shared_ptr<SectPx_Pole>& thePole) const;

		TnbSectPx_EXPORT Standard_Boolean IsContainSegment(const std::shared_ptr<SectPx_Segment>& theSeg) const;

		//- select a pole from the registry
		TnbSectPx_EXPORT std::shared_ptr<SectPx_Pole>
			SelectPole
			(
				const Standard_Integer theIndex
			) const;

		TnbSectPx_EXPORT std::shared_ptr<SectPx_Segment>
			SelectSegment
			(
				const Standard_Integer theIndex
			) const;

		//- Throw an exception if the segment has a controller!
		TnbSectPx_EXPORT std::tuple
			<
			std::pair<segmentId, segmentId>,
			sliderId
			>
			CreateSlider
			(
				const std::shared_ptr<SectPx_Segment>& theSegment,
				const std::shared_ptr<SectPx_Par>& thePar
			);

		TnbSectPx_EXPORT tightnessId
			CreateSymmTightnessDeg2
			(
				const std::shared_ptr<SectPx_Pole>& thePole,
				const std::shared_ptr<SectPx_Par>& thePar
			);

		TnbSectPx_EXPORT void ImportFrame
		(
			const std::shared_ptr<SectPx_Frame>& theFrame
		);
	};
}

#endif // !_SectPx_FrameTunner_Header
