#pragma once
#ifndef _SectPx_Par_Header
#define _SectPx_Par_Header

#include <SectPx_Child.hxx>
#include <SectPx_ParType.hxx>
#include <Ostream.hxx>

namespace tnbLib
{

	class SectPx_Par
		: public SectPx_Child
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_Par(_Types&&... _Args)
			: SectPx_Child(_Args...)
		{}

	public:

		sectPxLib::regObjType RegObjType() const override;

		virtual sectPxLib::parType ParType() const = 0;

		virtual Standard_Boolean IsFixed() const;

		virtual Standard_Boolean IsFree() const;

		virtual Standard_Boolean IsConstant() const;

		virtual Standard_Boolean IsComplete() const = 0;

		virtual Standard_Boolean InCycle() const = 0;

		virtual Standard_Real Value() const = 0;

		Standard_Real operator()() const;

		virtual void Print(Ostream& out) const = 0;


		/*friend std::shared_ptr<SectPx_Par> operator+(const std::shared_ptr<SectPx_Par>& p0, const std::shared_ptr<SectPx_Par>& p1);
		friend std::shared_ptr<SectPx_Par> operator-(const std::shared_ptr<SectPx_Par>& p0, const std::shared_ptr<SectPx_Par>& p1);
		friend std::shared_ptr<SectPx_Par> operator*(const std::shared_ptr<SectPx_Par>& p0, const std::shared_ptr<SectPx_Par>& p1);
		friend std::shared_ptr<SectPx_Par> operator/(const std::shared_ptr<SectPx_Par>& p0, const std::shared_ptr<SectPx_Par>& p1);*/

	};
}

#include <SectPx_ParI.hxx>

#endif // !_SectPx_Par_Header
