#pragma once
#ifndef _PtdModel_WingExpandedView_Header
#define _PtdModel_WingExpandedView_Header

#include <Standard_TypeDef.hxx>
#include <Global_Serialization.hxx>

#include <PtdModel_Module.hxx>

#include <vector>

namespace tnbLib
{

	class PtdModel_WingExpandedView
	{

		/*Private Data*/

		std::vector<Standard_Real> theX_;

		std::vector<Standard_Real> theTf_;
		std::vector<Standard_Real> theTb_;
		std::vector<Standard_Real> theYf_;
		std::vector<Standard_Real> theYb_;


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theX_;

			ar & theTf_;
			ar & theTb_;
			ar & theYf_;
			ar & theYb_;
		}

	public:


		//- default constructor

		PtdModel_WingExpandedView()
		{}

		//- constructors


		//- public functions and operators

		inline Standard_Integer NbSpans() const;

		const auto& X() const
		{
			return theX_;
		}

		const auto& Tf() const
		{
			return theTf_;
		}

		const auto& Tb() const
		{
			return theTb_;
		}

		const auto& Yf() const
		{
			return theYf_;
		}

		const auto& Yb() const
		{
			return theYb_;
		}

		inline void SetX(std::vector<Standard_Real>&&);

		inline void SetTf(std::vector<Standard_Real>&&);
		inline void SetTb(std::vector<Standard_Real>&&);
		inline void SetYf(std::vector<Standard_Real>&&);
		inline void SetYb(std::vector<Standard_Real>&&);

	};
}

#include <PtdModel_WingExpandedViewI.hxx>

#endif // !_PtdModel_WingExpandedView_Header
