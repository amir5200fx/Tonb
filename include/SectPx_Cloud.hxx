#pragma once
#ifndef _SectPx_Cloud_Header
#define _SectPx_Cloud_Header

#include <SectPx_Parent.hxx>
#include <Pnt2d.hxx>

#include <vector>

namespace tnbLib
{

	class SectPx_Cloud
		: public SectPx_Parent
	{

	public:

		struct Profile
		{
			std::vector<Pnt2d> Coords;

			friend class boost::serialization::access;

			template<class Archive>
			void serialize(Archive &ar, const unsigned int file_version)
			{
				ar & Coords;
			}
		};

	protected:

		/*Protected Data*/

		std::shared_ptr<Profile> theProfile_;


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_Parent>(*this);
			ar & theProfile_;
		}

		TnbSectPx_EXPORT void AllocateMemory();

	protected:

		template<class... _Types>
		SectPx_Cloud(_Types&&... _Args)
			: SectPx_Parent(_Args...)
		{
			AllocateMemory();
		}

		virtual void Update() const
		{}

	public:

		TnbSectPx_EXPORT Standard_Boolean IsCloud() const override;

		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;

		virtual Standard_Boolean IsComplete() const = 0;

		const auto& GetProfile() const
		{
			Update();
			return theProfile_;
		}

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Cloud);

#endif // !_SectPx_Cloud_Header
