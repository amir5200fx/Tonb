#pragma once
#ifndef _ShapePx_ConicSection_Header
#define _ShapePx_ConicSection_Header

#include <Global_Done.hxx>
#include <ShapePx_Module.hxx>
#include <ShapePx_TopoSectPolesFwd.hxx>
#include <Pnt2d.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class ShapePx_TopoSection;

	class ShapePx_ConicSection
		: public Global_Done
	{

	public:

		enum class sectType
		{
			quadratic,
			quartic
		};

	private:

		/*Private Data*/

		std::shared_ptr<ShapePx_TopoSection> theSection_;

		Standard_Real theWeight_;
	
		sectType theType_;
		std::vector<Standard_Real> theWeightCoffs_;

	public:

		//- default constructor

		ShapePx_ConicSection()
			: theWeight_(1.0)
		{}


		//- constructors

		ShapePx_ConicSection
		(
			const std::shared_ptr<ShapePx_TopoSection>& theSection
		)
			: theSection_(theSection)
			, theWeight_(1.0)
		{}


		//- public functions and operators

		const auto& Section() const
		{
			return theSection_;
		}

		auto SectionType() const
		{
			return theType_;
		}

		const auto& WeightCoffs() const
		{
			return theWeightCoffs_;
		}

		auto BaseWeight() const
		{
			return theWeight_;
		}

		TnbShapePx_EXPORT virtual void Perform();

		void LoadSection
		(
			const std::shared_ptr<ShapePx_TopoSection>& theSection
		)
		{
			theSection_ = theSection;
		}

		void SetBaseWeight(const Standard_Real x)
		{
			theWeight_ = x;
		}


		static TnbShapePx_EXPORT std::shared_ptr<ShapePx_TopoSectPole> 
			NextPole(const std::shared_ptr<ShapePx_TopoSectPole>&);
		static TnbShapePx_EXPORT std::shared_ptr<ShapePx_TopoSectPole> 
			PreviousPole(const std::shared_ptr<ShapePx_TopoSectPole>&);

		static TnbShapePx_EXPORT std::vector<std::shared_ptr<ShapePx_TopoSectPole>> 
			RetrievePoles(const ShapePx_TopoSection&);
		static TnbShapePx_EXPORT std::shared_ptr<shapePxLib::TopoSect_Corner> 
			RetrieveCorner(const std::vector<std::shared_ptr<ShapePx_TopoSectPole>>&);

		static TnbShapePx_EXPORT std::tuple
			<
			std::shared_ptr<ShapePx_TopoSectPole>,
			std::shared_ptr<ShapePx_TopoSectPole>, 
			std::shared_ptr<ShapePx_TopoSectPole>
			> 
			RetrieveSuperTriangle(const ShapePx_TopoSection&);
	};
}

#endif // !_ShapePx_ConicSection_Header
