#pragma once
#ifndef _SectPx_SegmentController_Header
#define _SectPx_SegmentController_Header

#include <SectPx_Controller.hxx>
#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_CPtsMap;

	class SectPx_SegmentController
		: public SectPx_Controller
	{

		/*Private Data*/

		std::shared_ptr<SectPx_CPtsMap> theCPts_;


		//- private functions and operators

		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

	protected:

	public:

		static TnbSectPx_EXPORT const char* typeName_;


		//- default constructor

		SectPx_SegmentController()
		{}

		//- constructors

		TnbSectPx_EXPORT SectPx_SegmentController(const Standard_Integer theIndex);

		TnbSectPx_EXPORT SectPx_SegmentController(const Standard_Integer theIndex, const word& theName);


		//- functions and operators

		const auto& CPts() const
		{
			return theCPts_;
		}

		TnbSectPx_EXPORT void SetCPts
		(
			const std::shared_ptr<SectPx_CPtsMap>& theCPts
		);

		TnbSectPx_EXPORT word RegObjTypeName() const override;

		

		TnbSectPx_EXPORT Standard_Boolean IsOnSegment() const override;


		//- override virtual functions from parent abstract class 

		TnbSectPx_EXPORT Standard_Integer NbChildMaps() const override;

		TnbSectPx_EXPORT Standard_Boolean HasChildMap() const override;

		TnbSectPx_EXPORT Standard_Boolean HasChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>>
			RetrieveChildren() const override;

		TnbSectPx_EXPORT std::shared_ptr<SectPx_Parent> 
			ChildMap
			(
				const Standard_Integer theIndex
			) const override;

		TnbSectPx_EXPORT void RemoveThisFromChildren() const override;

		TnbSectPx_EXPORT void AddThisToChildren() const override;

		TnbSectPx_EXPORT void RemoveThisFromChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		TnbSectPx_EXPORT void AddThisToChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;
	};
}


BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_SegmentController);

#endif // !_SectPx_SegmentController_Header
