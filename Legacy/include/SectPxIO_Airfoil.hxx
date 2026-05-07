#pragma once
#ifndef _SectPxIO_Airfoil_Header
#define _SectPxIO_Airfoil_Header

#include <SectPx_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [4/23/2023 Payvand]

	class SectPx_Registry;
	class SectPx_Frame;
	class SectPx_FrameTuner;

	namespace maker
	{
		class Profile;
	}

	class SectPxIO_Airfoil
	{

		/*Private Data*/

		std::shared_ptr<SectPx_Registry> theRegistry_;
		std::shared_ptr<SectPx_Frame> theFrame_;
		std::shared_ptr<SectPx_FrameTuner> theTuner_;

		std::vector<std::shared_ptr<maker::Profile>> theThickness_;
		std::vector<std::shared_ptr<maker::Profile>> theCamber_;


		// Private functions and operators [4/23/2023 Payvand]

		TNB_SERIALIZATION(TnbSectPx_EXPORT);

	public:

		static TnbSectPx_EXPORT const std::string extension;


		// default constructor [4/23/2023 Payvand]

		SectPxIO_Airfoil()
		{}


		// Public functions and operators [4/23/2023 Payvand]

		const auto& Registry() const
		{
			return theRegistry_;
		}

		const auto& Frame() const
		{
			return theFrame_;
		}

		const auto& Tuner() const
		{
			return theTuner_;
		}

		const auto& Thickness() const
		{
			return theThickness_;
		}

		const auto& Camber() const
		{
			return theCamber_;
		}

		void SetRegistry(const std::shared_ptr<SectPx_Registry>& theRegistry)
		{
			theRegistry_ = theRegistry;
		}

		void SetRegistry(std::shared_ptr<SectPx_Registry>&& theRegistry)
		{
			theRegistry_ = std::move(theRegistry);
		}

		void SetFrame(const std::shared_ptr<SectPx_Frame>& theFrame)
		{
			theFrame_ = theFrame;
		}

		void SetFrame(std::shared_ptr<SectPx_Frame>&& theFrame)
		{
			theFrame_ = std::move(theFrame);
		}

		void SetTuner(const std::shared_ptr<SectPx_FrameTuner>& theTuner)
		{
			theTuner_ = theTuner;
		}

		void SetTuner(std::shared_ptr<SectPx_FrameTuner>&& theTuner)
		{
			theTuner_ = std::move(theTuner);
		}

		void SetThickness(const std::vector<std::shared_ptr<maker::Profile>>& theThickness)
		{
			theThickness_ = theThickness;
		}

		void SetThickness(std::vector<std::shared_ptr<maker::Profile>>&& theThickness)
		{
			theThickness_ = std::move(theThickness);
		}

		void SetCamber(const std::vector<std::shared_ptr<maker::Profile>>& theCamber)
		{
			theCamber_ = theCamber;
		}

		void SetCamber(std::vector<std::shared_ptr<maker::Profile>>&& theCamber)
		{
			theCamber_ = std::move(theCamber);
		}

	};
}

#endif // !_SectPxIO_Airfoil_Header
