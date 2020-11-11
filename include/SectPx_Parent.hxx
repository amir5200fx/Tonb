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

		virtual Standard_Integer NbChildren() const;

		virtual Standard_Integer NbChildMaps() const;

		virtual Standard_Boolean IsPnt() const;

		virtual Standard_Boolean IsDatum() const;

		virtual Standard_Boolean IsGeoMap() const;

		virtual Standard_Boolean IsFieldFun() const;

		virtual Standard_Boolean IsController() const;

		virtual Standard_Boolean IsCPtsMap() const;

		virtual Standard_Boolean IsCloud() const;

		Standard_Boolean IsParent() const override;

		virtual Standard_Boolean HasChildren() const;

		virtual Standard_Boolean HasChildMap() const;

		virtual std::shared_ptr<SectPx_Parent> ChildMap(const Standard_Integer theIndex) const;

		virtual Standard_Boolean HasChild(const std::shared_ptr<SectPx_Child>& thePar) const = 0;

		virtual void RemoveThisFromChildren() const = 0;

		virtual void AddThisToChildren() const = 0;

		virtual void AddThisToChild(const std::shared_ptr<SectPx_Child>& thePar) const = 0;

		virtual void RemoveThisFromChild(const std::shared_ptr<SectPx_Child>& thePar) const = 0;

		virtual std::vector<std::shared_ptr<SectPx_Child>> RetrieveChildren() const;

		void Print(Ostream& out) const;

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Parent);

#endif // !_SectPx_Parent_Header
