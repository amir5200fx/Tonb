#pragma once
#ifndef _SectPx_CPtsMap_Header
#define _SectPx_CPtsMap_Header

#include <SectPx_Parent.hxx>
#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;
	class SectPx_Segment;
	class SectPx_Pole;

	class SectPx_CPtsMap
		: public SectPx_Parent
	{

		/*Private Data*/

		std::shared_ptr<SectPx_Segment> theSegment_;

		Standard_Boolean theSense_;

		std::shared_ptr<SectPx_Pole> theP0_;
		std::shared_ptr<SectPx_Pole> theP1_;


		//- private functions and operators

		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

	protected:

		template<class... _Types>
		SectPx_CPtsMap(_Types&&... _Args)
			: SectPx_Parent(_Args...)
		{}

	public:

		const auto & Segment() const
		{
			return theSegment_;
		}

		const auto& Pole0() const
		{
			return theP0_;
		}

		const auto& Pole1() const
		{
			return theP1_;
		}

		auto Sense() const
		{
			return theSense_;
		}

		TnbSectPx_EXPORT void SetSegment
		(
			const std::shared_ptr<SectPx_Segment>& theSegment,
			const Standard_Boolean theSense = Standard_True
		);

		TnbSectPx_EXPORT void Reverse();

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		TnbSectPx_EXPORT Standard_Boolean IsCPtsMap() const override;

		TnbSectPx_EXPORT virtual Standard_Boolean IsOnePar() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsMultiPar() const;

		virtual Standard_Boolean IsComplete() const = 0;

		virtual Standard_Integer NbPts() const = 0;

		virtual std::vector<Pnt2d> Pts() const = 0;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_CPtsMap);

#endif // !_SectPx_CPtsMap_Header
