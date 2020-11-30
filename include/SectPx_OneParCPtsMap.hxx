#pragma once
#ifndef _SectPx_OneParCPtsMap_Header
#define _SectPx_OneParCPtsMap_Header

#include <SectPx_CPtsMap.hxx>
#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	class SectPx_OneParCPtsMap
		: public SectPx_CPtsMap
	{

		/*Private Data*/

		std::weak_ptr<SectPx_Par> thePar_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbSectPx_EXPORT);

	protected:


		template<class... _Types>
		SectPx_OneParCPtsMap(_Types&&... _Args)
			: SectPx_CPtsMap(_Args...)
		{}

	public:


		TnbSectPx_EXPORT virtual Standard_Boolean IsSingle() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsDistribution() const;

		TnbSectPx_EXPORT Standard_Boolean IsOnePar() const override;

		const auto& Par() const
		{
			return thePar_;
		}

		TnbSectPx_EXPORT void SetPar
		(
			const std::shared_ptr<SectPx_Par>& thePar
		);

		TnbSectPx_EXPORT Standard_Integer NbChildren() const override;

		TnbSectPx_EXPORT Standard_Boolean IsComplete() const override;

		TnbSectPx_EXPORT Standard_Boolean HasChildren() const override;

		TnbSectPx_EXPORT Standard_Boolean HasChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		TnbSectPx_EXPORT std::vector<std::shared_ptr<SectPx_Child>> RetrieveChildren() const override;

		TnbSectPx_EXPORT void RemoveThisFromChildren() const override;

		TnbSectPx_EXPORT void AddThisToChildren() const override;

		TnbSectPx_EXPORT void AddThisToChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;

		TnbSectPx_EXPORT void RemoveThisFromChild
		(
			const std::shared_ptr<SectPx_Child>& thePar
		) const override;
	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_OneParCPtsMap);

#endif // !_SectPx_OneParCPtsMap_Header
