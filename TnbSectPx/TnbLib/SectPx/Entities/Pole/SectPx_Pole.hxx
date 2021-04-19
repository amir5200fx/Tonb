#pragma once
#ifndef _SectPx_Pole_Header
#define _SectPx_Pole_Header

#include <SectPx_RegObj.hxx>
#include <SectPx_PoleType.hxx>
#include <SectPx_PoleAdaptor.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

namespace tnbLib
{
	// Forward Declarations
	class SectPx_Pnt;

	class SectPx_Pole
		: public SectPx_RegObj
		, public SectPx_PoleAdaptor
	{

		/*Private Data*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_RegObj>(*this);
			ar & boost::serialization::base_object<SectPx_PoleAdaptor>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_Pole(_Types&&... Args)
			: SectPx_RegObj(Args...)
		{}

	public:

		TnbSectPx_EXPORT virtual Standard_Boolean IsInterior() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsBoundary() const;

		virtual Pnt2d Coord() const = 0;

		virtual SectPx_PoleType Type() const = 0;

		virtual std::shared_ptr<SectPx_Pnt> Pnt() const = 0;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		TnbSectPx_EXPORT Standard_Boolean IsPole() const override;

		TnbSectPx_EXPORT Standard_Boolean IsFrameRegObj() const override;

		static Standard_Boolean
			IsLess
			(
				const std::shared_ptr<SectPx_Pole>& theP0,
				const std::shared_ptr<SectPx_Pole>& theP1
			)
		{
			Debug_Null_Pointer(theP0);
			Debug_Null_Pointer(theP1);
			return theP0->Index() < theP1->Index();
		}
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Pole);

#endif // !_SectPx_Pole_Header
