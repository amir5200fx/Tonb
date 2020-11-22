#pragma once
#ifndef _SectPx_ProfileQ_Header
#define _SectPx_ProfileQ_Header

#include <SectPx_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class SectPx_Pnt;
	class Pnt2d;

	namespace maker { class Profile; }

	class SectPx_ProfileQ
		: public SectPx_Entity
	{

		friend class maker::Profile;

		/*Private Data*/

		std::vector<std::shared_ptr<SectPx_Pnt>> theQ_;


		DECLARE_SAVE_LOAD_HEADER(TnbSectPx_EXPORT);

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

		TnbSectPx_EXPORT std::vector<Pnt2d> RetrievePnts() const;
	};

	namespace sectPxLib
	{
		typedef std::vector<std::shared_ptr<SectPx_ProfileQ>> profileList;
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::SectPx_ProfileQ);

#endif // !_SectPx_ProfileQ_Header
