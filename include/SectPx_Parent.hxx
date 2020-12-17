#pragma once
#ifndef _SectPx_Parent_Header
#define _SectPx_Parent_Header

#include <SectPx_RegObj.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Par;
	class SectPx_Child;

	class SectPx_Parent
		: public SectPx_RegObj
	{

		/*Private Data*/


		/*private functions and operators*/

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar & boost::serialization::base_object<SectPx_RegObj>(*this);
		}

	protected:

		template<class... _Types>
		SectPx_Parent(_Types&&... _Args)
			: SectPx_RegObj(_Args...)
		{}

	public:

		TnbSectPx_EXPORT virtual Standard_Integer NbChildren() const;

		TnbSectPx_EXPORT virtual Standard_Integer NbChildMaps() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsPnt() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsDatum() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsGeoMap() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsFieldFun() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsController() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsCPtsMap() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsCloud() const;

		TnbSectPx_EXPORT virtual Standard_Boolean IsExtrProfile() const;

		TnbSectPx_EXPORT Standard_Boolean IsParent() const override;

		TnbSectPx_EXPORT virtual Standard_Boolean HasChildren() const;

		TnbSectPx_EXPORT virtual Standard_Boolean HasChildMap() const;

		TnbSectPx_EXPORT virtual std::shared_ptr<SectPx_Parent> ChildMap(const Standard_Integer theIndex) const;

		virtual Standard_Boolean HasChild(const std::shared_ptr<SectPx_Child>& thePar) const = 0;

		virtual void RemoveThisFromChildren() const = 0;

		virtual void AddThisToChildren() const = 0;

		virtual void AddThisToChild(const std::shared_ptr<SectPx_Child>& thePar) const = 0;

		virtual void RemoveThisFromChild(const std::shared_ptr<SectPx_Child>& thePar) const = 0;

		TnbSectPx_EXPORT virtual std::vector<std::shared_ptr<SectPx_Child>> RetrieveChildren() const;

		TnbSectPx_EXPORT void Print(Ostream& out) const;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Parent);

#endif // !_SectPx_Parent_Header
