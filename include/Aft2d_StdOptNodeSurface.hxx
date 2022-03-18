#pragma once
#ifndef _Aft2d_StdOptNodeSurface_Header
#define _Aft2d_StdOptNodeSurface_Header

#include <Aft2d_OptNodeSurface_Calculator.hxx>

namespace tnbLib
{

	// Forward Declarations [2/24/2022 Amir]
	class Aft2d_StdOptNodeSurface_Info;

	class Aft2d_StdOptNodeSurface
		: public Aft2d_OptNodeSurface_Calculator
	{

		/*Private Data*/

		std::shared_ptr<Aft2d_StdOptNodeSurface_Info> theInfo_;


		// private functions and operators [2/24/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);


		// private static functions [2/24/2022 Amir]

	protected:

		// default constructor [2/24/2022 Amir]

		Aft2d_StdOptNodeSurface()
		{}

	public:

		// default constructor [2/24/2022 Amir]

		

		// constructors [2/24/2022 Amir]

		explicit Aft2d_StdOptNodeSurface
		(
			const std::shared_ptr<Aft2d_StdOptNodeSurface_Info>& theInfo
		)
			: theInfo_(theInfo)
		{}

		// override functions and operators [2/24/2022 Amir]

		TnbMesh_EXPORT void Perform() override;

		// public functions and operators [2/24/2022 Amir]

		const auto& IterInfo() const
		{
			return theInfo_;
		}

		void SetInfo(const std::shared_ptr<Aft2d_StdOptNodeSurface_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}

		void SetInfo(std::shared_ptr<Aft2d_StdOptNodeSurface_Info>&& theInfo)
		{
			theInfo_ = std::move(theInfo);
		}

		static TnbMesh_EXPORT Pnt2d
			CorrectCoord
			(
				const Pnt2d& theCentre,
				const Pnt2d& theCoord,
				const Entity2d_Box&
			);

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_StdOptNodeSurface);

#endif // !_Aft2d_StdOptNodeSurface_Header
