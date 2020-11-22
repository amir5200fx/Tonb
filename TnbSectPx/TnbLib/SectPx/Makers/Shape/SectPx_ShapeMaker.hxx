#pragma once
#ifndef _SectPx_ShapeMaker_Header
#define _SectPx_ShapeMaker_Header

#include <SectPx_Maker.hxx>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Segment;
	class SectPx_Pole;
	class SectPx_Par;

	class SectPx_ShapeMaker
		: public SectPx_Maker
	{

		/*Private Data*/


		static void disJoinSegment
		(
			const std::shared_ptr<SectPx_Pole>& thePole,
			const std::shared_ptr<SectPx_Segment>& theSegment
		);

		static void disJoinSegment
		(
			const std::shared_ptr<SectPx_Segment>& theSegment
		);

		static void JoinSegment
		(
			const std::shared_ptr<SectPx_Pole>& thePole,
			const std::shared_ptr<SectPx_Segment>& theSegment,
			const short id
		);

		static void JoinSegment
		(
			const std::shared_ptr<SectPx_Segment>& theSegment
		);

	public:

		SectPx_ShapeMaker
		(
			const std::shared_ptr<SectPx_Registry>& theReg
		);

		Standard_Boolean IsContainPole(const std::shared_ptr<SectPx_Pole>& thePole) const;

		Standard_Boolean IsContainSegment(const std::shared_ptr<SectPx_Segment>& theSeg) const;

		std::shared_ptr<SectPx_Pole>
			SelectPole
			(
				const Standard_Integer theIndex
			) const;

		std::shared_ptr<SectPx_Segment>
			SelectSegment
			(
				const Standard_Integer theIndex
			) const;

		//- Throw an exception if the segment has a controller!
		std::tuple
			<
			std::pair<Standard_Integer, Standard_Integer>,
			Standard_Integer
			>
			CreateSlider
			(
				const std::shared_ptr<SectPx_Segment>& theSegment,
				const std::shared_ptr<SectPx_Par>& thePar
			);

		Standard_Integer
			CreateSymmTightnessDeg2
			(
				const std::shared_ptr<SectPx_Pole>& thePole,
				const std::shared_ptr<SectPx_Par>& thePar
			);

		std::vector<std::shared_ptr<SectPx_Pole>> RetrievePoles() const;

		std::vector<std::vector<std::shared_ptr<SectPx_Segment>>>
			RetrieveProfiles() const;

		/*void ImportProfiles
		(
			const sectPxLib::profileList& theProfiles
		);*/
	};
}

#endif // !_SectPx_ShapeMaker_Header
