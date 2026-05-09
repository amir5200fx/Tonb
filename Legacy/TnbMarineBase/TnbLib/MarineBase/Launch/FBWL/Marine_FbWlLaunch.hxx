#pragma once
#ifndef _Marine_FbWlLaunch_Header
#define _Marine_FbWlLaunch_Header

#include <Marine_Launch.hxx>
#include <Global_AccessMethod.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Marine_FreeBoard;

	class Marine_FbWlLaunch
		: public Marine_Launch
	{

		/*Private Data*/

		std::shared_ptr<Marine_FreeBoard> theSB_;
		std::shared_ptr<Marine_FreeBoard> thePT_;
		std::shared_ptr<Marine_FreeBoard> theFR_;
		std::shared_ptr<Marine_FreeBoard> theAF_;

	public:

		Marine_FbWlLaunch();

		const auto& SB() const
		{
			return theSB_;
		}

		const auto& PT() const
		{
			return thePT_;
		}

		const auto& FR() const
		{
			return theFR_;
		}

		const auto& AF() const
		{
			return theAF_;
		}

		void Perform();


		void LoadSB(const std::shared_ptr<Marine_FreeBoard>& theF)
		{
			theSB_ = theF;
		}

		void LoadPT(const std::shared_ptr<Marine_FreeBoard>& theF)
		{
			thePT_ = theF;
		}

		void LoadFR(const std::shared_ptr<Marine_FreeBoard>& theF)
		{
			theFR_ = theF;
		}

		void LoadAF(const std::shared_ptr<Marine_FreeBoard>& theF)
		{
			theAF_ = theF;
		}

		//- Macros
		
	};
}

#endif // !_Marine_FbWlLaunch_Header
