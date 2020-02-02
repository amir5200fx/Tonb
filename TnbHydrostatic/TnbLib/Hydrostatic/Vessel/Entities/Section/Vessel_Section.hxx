#pragma once
#ifndef _Vessel_Section_Header
#define _Vessel_Section_Header

#include <Global_AccessMethod.hxx>
#include <Vessel_Entity.hxx>

#include <vector>

#include <gp_Ax2.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Wire;

	class Vessel_Section
		: public Vessel_Entity
	{

		typedef std::vector<std::shared_ptr<Pln_Wire>> wireList;

		/*Private Data*/

		gp_Ax2 theSystem_;

		std::shared_ptr<wireList> theOuter_;
		std::shared_ptr<wireList> theInner_;

	protected:

		Vessel_Section
		(
			const std::shared_ptr<wireList>& theOuter,
			const std::shared_ptr<wireList>& theInner,
			const gp_Ax2& theSystem
		)
			: theOuter_(theOuter)
			, theInner_(theInner)
			, theSystem_(theSystem)
		{}

		Vessel_Section
		(
			const Standard_Integer theIndex,
			const std::shared_ptr<wireList>& theOuter,
			const std::shared_ptr<wireList>& theInner,
			const gp_Ax2& theSystem
		)
			: Vessel_Entity(theIndex)
			, theOuter_(theOuter)
			, theInner_(theInner)
			, theSystem_(theSystem)
		{}

		Vessel_Section
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const std::shared_ptr<wireList>& theOuter,
			const std::shared_ptr<wireList>& theInner,
			const gp_Ax2& theSystem
		)
			: Vessel_Entity(theIndex, theName)
			, theOuter_(theOuter)
			, theInner_(theInner)
			, theSystem_(theSystem)
		{}


		gp_Ax2& ChangeSystem()
		{
			return theSystem_;
		}

	public:

		const gp_Ax2& System() const
		{
			return theSystem_;
		}

		Standard_Boolean HasOuter() const
		{
			return (Standard_Boolean)theOuter_;
		}

		Standard_Boolean HasInner() const
		{
			return (Standard_Boolean)theInner_;
		}
			 
		Standard_Integer NbOuters() const;

		Standard_Integer NbInners() const;

		//- Macros
		
	};
}

#endif // !_Vessel_Section_Header
