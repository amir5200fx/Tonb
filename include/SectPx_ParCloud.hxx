#pragma once
#ifndef _SectPx_ParCloud_Header
#define _SectPx_ParCloud_Header

#include <SectPx_Child.hxx>
#include <SectPx_ParType.hxx>
#include <OSstream.hxx>

#include <vector>

namespace tnbLib
{

	class SectPx_ParCloud
		: public SectPx_Child
	{

		/*Private Data*/

	protected:

		template<class... _Types>
		SectPx_ParCloud(_Types&&... _Args)
			: SectPx_Child(_Args...)
		{}

	public:

		typedef std::vector<Standard_Real> realValues;

		sectPxLib::regObjType RegObjType() const override;

		virtual sectPxLib::parType ParType() const = 0;

		virtual Standard_Boolean IsFixed() const;

		virtual Standard_Boolean IsFree() const;

		virtual Standard_Boolean IsConstant() const;

		virtual Standard_Boolean IsComplete() const = 0;

		virtual Standard_Boolean InCycle() const = 0;

		virtual realValues Values() const = 0;

		realValues operator()() const;

	};
}

#include <SectPx_ParCloudI.hxx>

#endif // !_SectPx_ParCloud_Header

