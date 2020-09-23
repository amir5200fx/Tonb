#pragma once
#ifndef _SectPx_ProfileQ_Header
#define _SectPx_ProfileQ_Header

#include <SectPx_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Pnt;
	class SectPx_ProfileMaker;
	class Pnt2d;

	class SectPx_ProfileQ
		: public SectPx_Entity
	{

		friend class SectPx_ProfileMaker;

		/*Private Data*/

		std::vector<std::shared_ptr<SectPx_Pnt>> theQ_;

		auto& ChangeQ()
		{
			return theQ_;
		}

	public:

		template<class... _Types>
		SectPx_ProfileQ(_Types&&... _Args)
			: SectPx_Entity(_Args...)
		{}

		auto NbQ() const
		{
			return (Standard_Integer)theQ_.size();
		}

		const auto& Q() const
		{
			return theQ_;
		}

		std::vector<Pnt2d> RetrievePnts() const;
	};

	namespace sectPxLib
	{
		typedef std::vector<std::shared_ptr<SectPx_ProfileQ>> profileList;
	}
}

#endif // !_SectPx_ProfileQ_Header
