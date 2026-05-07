#pragma once
#ifndef _Cad_CharLength_Header
#define _Cad_CharLength_Header

#include <Cad_CharLength_Info.hxx>
#include <Cad_Module.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Global_Done.hxx>
#include <Global_Handle.hxx>

class Geom_Surface;

namespace tnbLib
{

	class Cad_CharLength
		: public Global_Done
	{

		/*Private Data*/

		Handle(Geom_Surface) thePatch_;

		std::shared_ptr<Entity2d_Box> theDomain_;
		std::shared_ptr<Cad_CharLength_Info> theInfo_;

		// outputs [6/7/2022 Amir]

		Standard_Real theLenU_;
		Standard_Real theLenV_;

		
		// private functions and operators [6/7/2022 Amir]

		TnbCad_EXPORT Standard_Real CalcCharLengthU() const;
		TnbCad_EXPORT Standard_Real CalcCharLengthV() const;

	public:

		static TnbCad_EXPORT const std::shared_ptr<Cad_CharLength_Info> DEFAULT_INFO;

		// default constructor [6/7/2022 Amir]

		Cad_CharLength()
			: theLenU_(0)
			, theLenV_(0)
			, theInfo_(DEFAULT_INFO)
		{}

		// constructors [6/7/2022 Amir]

		Cad_CharLength
		(
			const Handle(Geom_Surface)& thePatch, 
			const std::shared_ptr<Entity2d_Box>& theDomain
		)
			: thePatch_(thePatch)
			, theDomain_(theDomain)
			, theInfo_(DEFAULT_INFO)
		{}


		// public functions and operators [6/7/2022 Amir]

		const auto& Patch() const
		{
			return thePatch_;
		}

		const auto& Domain() const
		{
			return theDomain_;
		}

		const auto& AlgInfo() const
		{
			return theInfo_;
		}

		auto LengthU() const
		{
			return theLenU_;
		}

		auto LengthV() const
		{
			return theLenV_;
		}

		TnbCad_EXPORT void Perform();

		void SetSurface(const Handle(Geom_Surface)& thePatch)
		{
			thePatch_ = thePatch;
		}

		void SetDomain(const std::shared_ptr<Entity2d_Box>& theDomain)
		{
			theDomain_ = theDomain;
		}

		void OverrideInfo(const std::shared_ptr<Cad_CharLength_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}
	};
}

#endif // !_Cad_CharLength_Header
