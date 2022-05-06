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


		private:

			//- private functions and operators

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


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive &ar, const unsigned int file_version)
		{
			ar & boost::serialization::base_object<SectPx_Parent>(*this);
			ar & theProfile_;
		}

		TnbSectPx_EXPORT void AllocateMemory();

	protected:

		// default constructor [4/27/2022 Amir]

		SectPx_Cloud()
		{
			AllocateMemory();
		}

		// constructors [4/27/2022 Amir]

		explicit SectPx_Cloud(const Standard_Integer theIndex)
		{
			AllocateMemory();
		}

		SectPx_Cloud
		(
			const Standard_Integer theIndex,
			const word& theName
		)
		{
			AllocateMemory();
		}


		// protected functions and operators [4/27/2022 Amir]

		virtual void Update() const
		{}

	public:


		// override functions and operators [4/27/2022 Amir]

		TnbSectPx_EXPORT Standard_Boolean IsCloud() const override;
		TnbSectPx_EXPORT Standard_Boolean IsFrameRegObj() const override;
		TnbSectPx_EXPORT sectPxLib::regObjType RegObjType() const override;


		// public funcctions and operators [4/27/2022 Amir]

		virtual Standard_Boolean IsComplete() const = 0;

		const auto& GetProfile() const
		{
			Update();
			return theProfile_;
		}

		TnbSectPx_EXPORT Profile& ProfileRef();

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::SectPx_Cloud);

#endif // !_SectPx_Cloud_Header
