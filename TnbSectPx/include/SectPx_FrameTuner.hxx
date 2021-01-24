#pragma once
#ifndef _SectPx_FrameTuner_Header
#define _SectPx_FrameTuner_Header

#include <SectPx_Entity.hxx>
#include <tuple>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Frame;
	class SectPx_ParRegistry;
	class SectPx_FrameRegistry;
	class SectPx_Pole;
	class SectPx_Segment;
	class SectPx_Par;
	class SectPx_Coord;

	class SectPx_FrameTuner
		: public SectPx_Entity
	{

		/*Private Data*/

		std::shared_ptr<SectPx_ParRegistry> theParRegistry_;
		std::shared_ptr<SectPx_FrameRegistry> theFrameReg_;

		Standard_Boolean IsLoaded_;


		//- private functions and operators


		TNB_SERIALIZATION(TnbSectPx_EXPORT);
		

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


		SectPx_FrameTuner()
			: IsLoaded_(Standard_False)
		{}

	public:

		typedef Standard_Integer segmentId;
		typedef Standard_Integer sliderId;
		typedef Standard_Integer tightnessId;

		SectPx_FrameTuner
		(
			const std::shared_ptr<SectPx_ParRegistry>& theParRegistry,
			const std::shared_ptr<SectPx_FrameRegistry>& theFrameReg
		)
			: theParRegistry_(theParRegistry)
			, theFrameReg_(theFrameReg)
			, IsLoaded_(Standard_False)
		{}


		const auto& ParRegistry() const
		{
			return theParRegistry_;
		}

		const auto& FrameRegistry() const
		{
			return theFrameReg_;
		}

		Standard_Boolean IsFrameLoaded() const
		{
			return IsLoaded_;
		}

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

		TnbSectPx_EXPORT std::tuple
			<
			std::pair<segmentId, segmentId>,
			sliderId
			> CreateSlider
			(
				const std::shared_ptr<SectPx_Segment>& theSegment, 
				const std::shared_ptr<SectPx_Coord>& theCoord
			);

		TnbSectPx_EXPORT tightnessId
			CreateSymmTightnessDeg2
			(
				const std::shared_ptr<SectPx_Pole>& thePole,
				const std::shared_ptr<SectPx_Par>& thePar
			);

		TnbSectPx_EXPORT Standard_Integer
			CreateWeight
			(
				const std::shared_ptr<SectPx_Pole>& thePole,
				const std::shared_ptr<SectPx_Par>& theWeight
			);

		TnbSectPx_EXPORT void ImportFrame
		(
			const std::shared_ptr<SectPx_Frame>& theFrame
		);

		TnbSectPx_EXPORT void PrintRegistry() const;
	};
}

#endif // !_SectPx_FrameTuner_Header
